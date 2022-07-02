#include "iotop.hpp"
#include "bpf/libbpf.h"
#include "iotop.skel.h"
#include <bpf/bpf.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 REQ_OP_READ		= 0,
 write sectors to the device 
	REQ_OP_WRITE		= 1,
	 flush the volatile write cache 
	REQ_OP_FLUSH		= 2,
	 discard sectors 
	REQ_OP_DISCARD		= 3,
	 securely erase sectors 
	REQ_OP_SECURE_ERASE	= 5,
	 write the zero filled sector many times
	REQ_OP_WRITE_ZEROES	= 9,
	 Open a zone 
	REQ_OP_ZONE_OPEN	= 10
	 Close a zone 
	REQ_OP_ZONE_CLOSE	= 11,
	 Transition a zone to full 
	REQ_OP_ZONE_FINISH	= 12,
	 write data at the current zone write pointer 
	REQ_OP_ZONE_APPEND	= 13,
	 reset a zone write pointer 
	REQ_OP_ZONE_RESET	= 15
	 reset all the zone present on the device 
	REQ_OP_ZONE_RESET_ALL	= 17,

	 Driver private requests
	REQ_OP_DRV_IN		= 34,
	REQ_OP_DRV_OUT		= 35,
 */






int controller_iotop()
{
    struct skel_iotop *skel = skel_iotop__open();
    if (skel_iotop__load(skel) != 0) {
        return -1;
    }
    if (skel_iotop__attach(skel) !=0) {
        return -2;
    }

    
    int map_fd = bpf_map__fd(skel->maps.summary_map);
    for (; ; ) {
        system("clear");
        fprintf(stdout, "%-6s\t%-12s\t%4s\t%3s %3s  %-4s  %-4s\t%-4s\t%-6s\n", "PID", "COMM","R/W","MAJ", "MIN" ,"DISK", "I/O", "KBytes", "AVGms");
        struct value_t val;
        struct info_t info_cur = {}, info_next = {};

        while (bpf_map_get_next_key(map_fd,&info_cur, &info_next) == 0) {
            bpf_map_lookup_elem(map_fd, &info_cur, &val);
            float avg_ms = (float(val.us)/1000) / val.io;
            fprintf(stdout, "%-6u\t%-12s\t0x%-2x\t%3u %3u  %4s  %-4u\t%-4lu\t%-6.2f\n", info_cur.pid, info_cur.com_name, 
                    info_cur.rwflags,info_cur.major, info_cur.minor,info_cur.disk_name, val.io,val.bytes/1024, avg_ms);
            info_cur= info_next;
        }
        sleep(1);
    }


 cleanup:
    fprintf(stderr, "stop controller, begin do some clean work");
    return 0;
}
