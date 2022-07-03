#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <tuple>
#include <algorithm>

#include <bpf/bpf.h>
#include "iotop.skel.h"

#include "iotop.hpp"
// #include "u_helper.hpp"

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

using namespace std;

IotopController::IotopController(struct iotop_options_t opt)
{
    _opt = opt;
    this->_skel = skel_iotop__open();

    if (skel_iotop__load(_skel) != 0) {
        cout << "load iotop bpf program failed" << endl;
        exit(-1);
    }
    if (skel_iotop__attach(_skel) !=0) {
        cout << "attach iotop bpf program failed" << endl;
    }
    _map_fd = bpf_map__fd(_skel->maps.summary_map);

    if (_opt.sort_field == NULL) {
        _compare = [](_Item item1, _Item item2) -> bool {
            struct info_t key1 = (struct info_t) get<0>(item1);
            struct info_t key2 = (struct info_t) get<0>(item2);
            return key1.pid > key2.pid;
        };
        return;
    }

    if (strcmp(_opt.sort_field, "io") == 0) {
        _compare = [](_Item item1, _Item item2) -> bool {
            struct value_t v1 = (struct value_t) get<1>(item1);
            struct value_t v2 = (struct value_t) get<1>(item2);
            return v1.io > v2.io;
        };
    } else if (strcmp(_opt.sort_field, "byte") == 0) {
        _compare = [](_Item item1, _Item item2) -> bool {
            struct value_t v1 = (struct value_t) get<1>(item1);
            struct value_t v2 = (struct value_t) get<1>(item2);
            return v1.bytes > v2.bytes;
        };
    } else if (strcmp(_opt.sort_field, "cost") == 0) {
        _compare = [](_Item item1, _Item item2) -> bool {
            float v1 = get<2>(item1);
            float v2 = get<2>(item2);
            return v1 > v2;
        };
    } 

}

/*
void print_aligned(Position pos, string s, int length, bool is_end)
{
    int spaces = 0;
    switch (pos) {
        case CENTER: spaces = (length - s.size()) / 2; break;
        case RIGHT:  spaces = length - s.size(); break;
        default: break;
    }

    if (spaces > 0)  cout << string(spaces, ' '); 
    cout << s;
    if (is_end) cout << endl;
}

*/

void IotopController::Run()
{
    /*
    const std::map<string, int> fields = {
        {"PID", 4}, {"COMM", 4}, {"R/W", 4}, {"MAJ", 4}, {"MIN", 4}, {"DISK", 6}, 
        {"I/O", 4}, {"Kbytes", 8}, {"AVGms", 6},
    };
    */

    for (; ; ) {

        fprintf(stdout, "%-6s\t%-12s\t%4s\t%3s %3s  %-4s  %-4s\t%-4s\t%-6s\n", 
                "PID", "COMM","R/W","MAJ", "MIN" ,"DISK", "I/O", "KBytes", "AVGms");


        
        /*
        for (auto const &field  : fields) {
            print_aligned(CENTER, field.first, field.second, false);
        }
        */
        struct info_t info_cur = {}, info_next = {};

        while (bpf_map_get_next_key(_map_fd,&info_cur, &info_next) == 0) {
            struct value_t val;
            if (bpf_map_lookup_elem(_map_fd, &info_cur, &val) == 0)
            {
                float avg_ms = (float(val.us)/1000) / val.io;
                _account.push_back({info_cur, val, avg_ms});
            }
            info_cur= info_next;
        }
        sort(_account.begin(), _account.end(), _compare);
        for (auto item : _account) {
            struct info_t info = get<0>(item);
            struct value_t value = get<1>(item);
            float avg_ms = get<2>(item);
            fprintf(stdout, "%-6u\t%-12s\t%-2x\t%3u %3u  %4s  %-4u\t%-4llu\t%-6.2f\n", info.pid, info.com_name, 
                    info.rwflags,info.major, info.minor,info.disk_name, value.io,value.bytes/1024, avg_ms);
        }
        _account.clear();

        sleep(1);
        system("clear");
    }

}



IotopController::~IotopController()
{
    close(_map_fd);
    skel_iotop__detach(_skel);
    skel_iotop__destroy(_skel);
}

