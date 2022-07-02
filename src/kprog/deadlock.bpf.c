#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include "helper.bpf.h"



#if defined(bpf_target_x86)
KPROBE_BPF_PROG(__x64_sys_clone)
#elif defined(bpf_target_ia32)
KPROBE_BPF_PROG(__ia32_sys_clone)
#endif
    (struct pt_regs *reg)
{
    return 0;
}





