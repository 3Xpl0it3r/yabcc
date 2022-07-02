#ifndef __IOTOP_BPF_H
#define __IOTOP_BPF_H
// those struct blow are exposted to userspace
//
// the key for the output summary
struct info_t {
    __u32 pid;
    __u32 rwflags;
    __u32 major;
    __u32 minor;
    char com_name[16];
    char disk_name[8];
};

// the value of the output summary
struct value_t {
    __u32 io;
    __u64 us;
    __u64 bytes;
};


#endif
