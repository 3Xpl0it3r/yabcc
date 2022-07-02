#ifndef __HELPER_FUNCTION_BPF_H
#define __HELPER_FUNCTION_BPF_H


#define TP_BPF_PROG(A, B) SEC("tp/"#A"/"#B) int STRING_JOIN(tp_bpf_prog_, STRING_JOIN(A, B))
#define KPROBE_BPF_PROG(A) SEC("kprobe/"#A) int kprobe_bpf_prog_##A
#define KRETPROBE_BPF_PROG(A) SEC("kretprobe/"#A) int ketprobe_bpf_prog_##A
#define UPROBE_BPF_PROG(A) SEC("uprobe/"#A) int uprobe_bpf_prog__#A
#define URETPROBE_BPF_PROG(A) SEC("uretprobe/"#A) int uretprobe_bpf_prog__#A


unsigned long long load_byte(void *ctx, unsigned long long off) asm("llvm.bpf.load.byte");
unsigned long long load_half(void *ctx, unsigned long long off) asm("llvm.bpf.load.half");
unsigned long long load_word(void *ctx, unsigned long long off) asm("llvm.bpf.load.word");




#endif
