#include "vmlinux.h"
#include "bpf/bpf_tracing.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>
#include "helper.bpf.h"
#include "iotop.bpf.h"


extern int LINUX_KERNEL_VERSION __kconfig;

#define TASK_COMM_LEN			16

__u32 filter_pid = 0;


// for saving process info by request
struct who_t {
    __u32 pid;
    char name[TASK_COMM_LEN];
};

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 4096);
    __type(key, struct request *);
    __type(value, struct who_t);
} who_req_map SEC(".maps");


// for saving the timestamp and __data_len of each request
struct startup_t {
    __u64 ts;
    __u64 data_len;
};

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 4096);
    __type(key, struct request *);
    __type(value, struct startup_t);
} startup_req_map SEC(".maps");


struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 1024);
    __type(key, struct info_t);
    __type(value, struct value_t);
} summary_map SEC(".maps");




// this kprobe is used to get pid and common
KPROBE_BPF_PROG(blk_account_io_start)(struct pt_regs *reg)
{
    struct request *req = (struct request *)PT_REGS_PARM1(reg);
    if (req == NULL)  
        return 0;


    struct who_t who = {};
    __builtin_memset(&who, 0, sizeof(who));
    if (bpf_get_current_comm(&who.name, sizeof(who.name)) == 0) {
        who.pid = bpf_get_current_pid_tgid() >> 32;
        if (filter_pid != 0 && filter_pid != who.pid)
            return 0; 
        bpf_map_update_elem(&who_req_map, &req, &who, BPF_ANY);
    }
    return 0;
}


/*
 * blk_mq_start_request - Start processing a request
 * @rq: Pointer to request to be started
 * Function used by device drivers to notify the block layer that a request
 * is going to be processed now, so blk layer can do proper initializations
 * such as starting the timeout timer.
 */
KPROBE_BPF_PROG(blk_mq_start_request)(struct pt_regs *reg)
{
    struct request *req = (struct request *)PT_REGS_PARM1(reg);
    if (req == NULL)  
        return 0;
    struct startup_t startup = {
        .ts = bpf_ktime_get_ns(),
        .data_len = 0,
    };


    if (LINUX_KERNEL_VERSION >= KERNEL_VERSION(4, 18, 0)) {
        startup.data_len = BPF_CORE_READ(req, __data_len);
    } else {
        bpf_probe_read_kernel(&startup.data_len, sizeof(req->__data_len), __builtin_preserve_access_index(&req->__data_len));
    }
    bpf_printk("debug len %llu ", startup.data_len);
    bpf_map_update_elem(&startup_req_map, &req, &startup, BPF_ANY);

    return 0;
}


/*
 * Account IO completion.  flush_rq isn't accounted as a normal IO on queueing nor completion.
 * Accounting the containing request is enough.
 */

KPROBE_BPF_PROG(blk_account_io_done)(struct pt_regs *reg)
{
    struct request *req = (struct request *)PT_REGS_PARM1(reg);
    if (req == NULL) return 0;
    struct startup_t *start_p;
    struct who_t *who_p;

    start_p = bpf_map_lookup_elem(&startup_req_map, &req);
    if (!start_p) {
        return 0;
    }

    __u32 pid;
    who_p = bpf_map_lookup_elem(&who_req_map, &req);
    pid = who_p != NULL ? who_p->pid : 0;

    if (filter_pid != 0 && filter_pid != pid) {
        bpf_map_delete_elem(&startup_req_map, &req);
        if (who_p != NULL) {
            bpf_map_delete_elem(&who_req_map, &req);
        }
        return 0;
    }


    __u64 delta_ns = (bpf_ktime_get_ns() - start_p->ts) / 1000;

    //steup info 
    struct info_t info ;
    __builtin_memset(&info, 0, sizeof(info));

    info.pid = pid;
    if (LINUX_KERNEL_VERSION > KERNEL_VERSION(4 , 18, 0)) {
        info.major = BPF_CORE_READ(req, rq_disk, major);
        info.minor = BPF_CORE_READ(req, rq_disk, first_minor);
        BPF_CORE_READ_STR_INTO(&info.disk_name, req, rq_disk, disk_name);
        info.rwflags = BPF_CORE_READ(req, cmd_flags);
    } else {
        struct gendisk *_rq_disk;
        if (bpf_probe_read_kernel(&_rq_disk, sizeof(_rq_disk), __builtin_preserve_access_index(&req->rq_disk)) == 0){
            bpf_probe_read_kernel(&info.major, sizeof(info.major), __builtin_preserve_access_index(&_rq_disk->major));
            bpf_probe_read_kernel(&info.minor, sizeof(info.minor), __builtin_preserve_access_index(&_rq_disk->first_minor));
            bpf_probe_read_kernel(&info.disk_name, sizeof(info.disk_name), __builtin_preserve_access_index(&_rq_disk->disk_name));
        }
    }
    info.rwflags &= ((1 << 8) -1);

    bpf_probe_read_str(info.com_name, sizeof(info.com_name), who_p->name);
    if (who_p) {
        char name[16];
        __builtin_memset(name, 0, 16);
        __builtin_memcpy(&name, who_p->name, sizeof(name));
    }
    
    if (info.pid == 0) {
        struct info_t zero = {};
        __builtin_memset(&zero, 0, sizeof(zero));
        bpf_map_update_elem(&summary_map, &info, &zero, BPF_ANY);
    }


    struct value_t *val_p;
    val_p = bpf_map_lookup_elem(&summary_map, &info);

    if (val_p) {
        __sync_fetch_and_add(&val_p->bytes, start_p->data_len);
        __sync_fetch_and_add(&val_p->us, delta_ns);
        __sync_fetch_and_add(&val_p->io, 1);
    } else {
        struct value_t tmp_v = { };
        __builtin_memset(&tmp_v, 0, sizeof(tmp_v));
        tmp_v.io = 1;
        tmp_v.us = delta_ns;
        tmp_v.bytes = start_p->data_len;
        bpf_map_update_elem(&summary_map, &info, &tmp_v, BPF_ANY);
    }


    bpf_map_delete_elem(&who_req_map, &req);
    bpf_map_delete_elem(&startup_req_map, &req);
    
    return 0;
}


char _license[] SEC("license") = "GPL";
