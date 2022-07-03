#ifndef __IOTOP_USERSPACE_H
#define __IOTOP_USERSPACE_H
// the key for the output summary
//

#include <argp.h>
#include <string>
#include <tuple>
#include <functional>
#include <vector>

#include "iotop.skel.h"
#include "bcc.hpp"

using namespace std;



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


typedef  tuple<struct info_t, struct value_t, float> _Item;

struct iotop_options_t{
    int interval;
    char *sort_field;
};

error_t iotop_parse_option(int ,char *,struct argp_state *);

class IotopController:public Controller
{
public:
    IotopController(struct iotop_options_t opt);
    void Run();
    ~IotopController();




private:
    struct skel_iotop *_skel;
    int _map_fd;
    struct iotop_options_t _opt;

private:
    function<bool(_Item, _Item)> _compare;
    vector<_Item> _account;
};


#endif
