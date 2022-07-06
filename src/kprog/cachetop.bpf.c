#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include "helper.bpf.h"

KPROBE_BPF_PROG(add_to_page_cache_lru)(struct pt_regs *reg)
{
    return 0;
}

KPROBE_BPF_PROG(mark_page_accessed)(struct pt_regs *reg)
{
    return 0;
}


KPROBE_BPF_PROG(mark_buffer_dirty)(struct pt_regs *reg)
{
    return 0;
}

KPROBE_BPF_PROG(account_page_dirtied)(struct pt_regs *reg)
{
    return 0;
}



char _license[] SEC("license") = "GPL";
