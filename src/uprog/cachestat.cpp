#include "cachestat.skel.h"
#include <sstream>
#include <cstdlib>
#include <string>
extern "C"
{
#include "bpf/bpf.h"
}
#include "cachestat.hpp"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>


CacheState::CacheState()
{
    // load bpf
    this->_skel = skel_cachestat__open();
    skel_cachestat__load(this->_skel);
    skel_cachestat__attach(this->_skel);
    
    // get fd _map
    this->_map_fd = bpf_map__fd(this->_skel->maps.count_map);
    // get ksymc maps
}


vector<string>split(const string &s, char delim)
{
    vector<string> elems;
    istringstream iss(s);
    do{
        string subs;
        iss >> subs;
        elems.push_back(subs);
    } while (iss);
    return elems;
}

void CacheState::Run()
{
    printf("%8s %8s %8s %8s %12s %10s\n", "HITS", "MISSES", "DIRTIES",
		"HITRATIO", "BUFFERS_MB", "CACHED_MB");
    int key_total = 0, key_missing = 1, key_mbd = 2;
    for (; ; ) {
        sleep(1);
        unsigned long long  buffers, cached;
        long long int total = 0, misses = 0, mbd = 0, hits = 0;

        if (0==1) {
            bpf_map_lookup_elem(_map_fd, &key_total, &total);
            bpf_map_lookup_elem(_map_fd, &key_missing, &misses);
            bpf_map_lookup_elem(_map_fd, &key_mbd, &mbd);
        } else {
            total = __atomic_exchange_n(&_skel->bss->total, 0, __ATOMIC_RELAXED);
            misses = __atomic_exchange_n(&_skel->bss->misses, 0, __ATOMIC_RELAXED);
            mbd = __atomic_exchange_n(&_skel->bss->mbd, 0, __ATOMIC_RELAXED);
        }
        if (total < 0) total = 0;
        if (misses < 0) misses = 0;
        hits = total - misses;
        if (hits < 0) {
            misses = total;
            hits = 0;
        }
        float ratio = total > 0 ? hits * 1.0 / total : 0.0;
        if (get_mem_info(&buffers, &cached)) {
            return;
        }
        printf("%8lld %8lld %8llu %7.2f%% %12llu %10llu\n",
			hits, misses, mbd, 100 * ratio,
			buffers / 1024, cached / 1024);
        
    }
}

int CacheState::get_mem_info(unsigned long long *buffers, unsigned long long *cached)
{
    string line;
    FILE *fp = fopen("/proc/meminfo", "r");
    
    int ret = fscanf(fp, "MemTotal: %*u kB\nMemFree: %*u kB\nMemAvailable: %*u kB\nBuffers: %llu kB\n"
            "Cached: %llu kB\n", buffers, cached);
    if (ret != 2) {
        return -1;
    }

    return 0;
}


CacheState::~CacheState()
{
    skel_cachestat__detach(_skel);
    skel_cachestat__destroy(_skel);
}

