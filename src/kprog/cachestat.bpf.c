#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "helper.bpf.h"
#include "cachestat.bpf.h"

extern int LINUX_KERNEL_VERSION __kconfig;

__s64 total = 0;    /* total cache accesses without counting dirties */
__s64 misses = 0;   /* total of add to lru because of read misses */
__s64 mbd = 0;      /* total of mark_buffer_dirty events */


#define KEY_TOTAL 0
#define KEY_MISSING 1
#define KEY_MBD 2

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 3);
    __type(key, __u32);
    __type(value, __s64);
} count_map SEC(".maps");


static __always_inline void do_count(struct pt_regs *reg)
{
    struct key_t key = {};
    __builtin_memset(&key, 0, sizeof(key));
    key.ip = PT_REGS_IP(reg);
    __u64 *kc;
    kc = bpf_map_lookup_elem(&count_map, &key);
    if (kc)  __sync_fetch_and_add(kc, 1); 
    else {
        __u64 tmp_c =1;
        bpf_map_update_elem(&count_map, &key, &tmp_c, BPF_ANY);
    }
}

// 如果页面缓存不命中，调用add_to_page_cache_lru函数将新申请的页面缓存添加到页面缓存和LUR队列里面
KPROBE_BPF_PROG(add_to_page_cache_lru)(struct pt_regs *reg)
{
    if (0==1) {
        __u32 key = KEY_MISSING;
        __s64 *value;
        value = bpf_map_lookup_elem(&count_map, &key);
        if (value) {
            __sync_fetch_and_add(value, 1);
        }else {
            __s64 v = 1;
            bpf_map_update_elem(&count_map, &key, &v, BPF_ANY);
        }
    } else { 
        __sync_fetch_and_add(&misses, 1);
    }
    return 0;
}


// 当一个页面被访问时,都会调用这个函数来修改对应的PG_active和PG_reference
KPROBE_BPF_PROG(mark_page_accessed)(struct pt_regs *reg)
{
    if (0==1) {
        __u32 key = KEY_TOTAL;
        __s64 *value;

        value = bpf_map_lookup_elem(&count_map, &key);
        if (value) {
            __sync_fetch_and_add(value, 1);
        } else {
            __s64 v=1;
            bpf_map_update_elem(&count_map, &key, &v, BPF_ANY);
        }
    } else {

        __sync_fetch_and_add(&total, 1);
    }
    return 0;
}

// 脏页数增时候，会调用account_page_dirtied
#if LINUX_KERNEL_VERSION > KERNEL_VERSION(5, 15, 40)
KPROBE_BPF_PROG(folio_account_dirtied)
#else
KPROBE_BPF_PROG(account_page_dirtied)
#endif
    (struct pt_regs *reg)
{
    if (0==1) {
        __u32 key = KEY_MISSING;
        __s64 *value;
        value = bpf_map_lookup_elem(&count_map, &key);
        if (value) {
            __sync_fetch_and_add(value, -1);
        } else {
            __s64 v = 1;
            bpf_map_update_elem(&count_map, &key, &v, BPF_ANY);
        }
        
    } else 
        __sync_fetch_and_add(&misses, -1);
    return 0;
}


// 
KPROBE_BPF_PROG(mark_buffer_dirty)(struct pt_regs *reg)
{
    if (0==1) {
        __u32 t_key = KEY_TOTAL, m_key = KEY_MBD;
        __s64 *t_value, *m_value;
        t_value = bpf_map_lookup_elem(&count_map, &t_key);
        if (t_value) {
            __sync_fetch_and_add(t_value, -1);
        } else {
            __s64 v = -1;
            bpf_map_update_elem(&count_map, &t_key, &v, BPF_ANY);
        }
        m_value = bpf_map_lookup_elem(&count_map, &m_key);
        if (m_value) {
            __sync_fetch_and_add(m_value, 1);
        } else {
            __s64 v = 1;
            bpf_map_update_elem(&count_map, &m_key, &v, BPF_ANY);
        }
    } else {
        __sync_fetch_and_add(&total, -1);
        __sync_fetch_and_add(&mbd, 1);
    }
    return 0;
}
char _license[] SEC("license") = "GPL";
