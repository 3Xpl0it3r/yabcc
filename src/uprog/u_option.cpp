
#include "u_option.hpp"
#include "bcc.hpp"
#include "cachestat.hpp"
#include "iotop.hpp"
#include <argp.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <strings.h>


Options::Options(char *tool)
{
    if (strncasecmp(tool, "Iotop", strlen(tool)) == 0) 
        _kind = IOTOP;
    else if (strncasecmp(tool, "cachestat", strlen(tool)) == 0) 
        _kind = CACHESTAT;
    else 
        _kind = UNKNOWN;
}



Controller *Options::NewForController()
{
    switch (_kind) {
    case CACHESTAT:
        return new CacheStateController(m_opt_options.cachestat);
    case IOTOP:
        return new IotopController(m_opt_options.iotop);
    default:
        return nullptr;
    }
}


OptionKind Options::Kind()
{
    return _kind;
}


