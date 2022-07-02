#ifndef __CACHE_STAT_USERSPACE_H
#define __CACHE_STAT_USERSPACE_H

#include <map>
#include <string>

#include "cachestat.skel.h"

using namespace std;

struct key_u_t {
    unsigned long long ip;
};

void cachestate_controller_run(void);

class CacheState
{
public:
    CacheState();
    void Run();
    void Stop();
    ~CacheState();

private:
    // get mem infor
    int get_mem_info(unsigned long long *, unsigned long long*);


private:
    struct skel_cachestat *_skel;

    map<unsigned long long, string> _ksym_maps;


    int _map_fd;
};

#endif
