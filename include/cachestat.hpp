#ifndef __CACHE_STAT_USERSPACE_H
#define __CACHE_STAT_USERSPACE_H

#include <map>
#include <string>

#include "cachestat.skel.h"
#include "bcc.hpp"

using namespace std;


struct cachestate_option_t {
    bool show_time;
};

struct key_u_t {
    unsigned long long ip;
};

void cachestate_controller_run(void);

class CacheStateController: public Controller
{
public:
    CacheStateController(struct cachestate_option_t opt);
    void Run();
    ~CacheStateController();

private:
    // get mem infor
    int get_mem_info(unsigned long long *, unsigned long long*);


private:
    struct cachestate_option_t _opt;
    struct skel_cachestat *_skel;
    map<unsigned long long, string> _ksym_maps;
    int _map_fd;
};



#endif
