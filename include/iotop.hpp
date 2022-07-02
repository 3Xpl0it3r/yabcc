#ifndef __IOTOP_USERSPACE_H
#define __IOTOP_USERSPACE_H
// the key for the output summary
//


#include "bcc.hpp"
struct info_t {
    unsigned int pid;
    unsigned int rwflags;
    unsigned int major;
    unsigned int minor;
    char com_name[16];
    char disk_name[8];
};


// the value of the output summary
struct value_t {
    unsigned int io;
    unsigned long us;
    unsigned long bytes;
};


int controller_iotop();


#endif
