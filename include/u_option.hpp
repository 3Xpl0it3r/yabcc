#ifndef __OPTIONS_USERSPACE_H
#define __OPTIONS_USERSPACE_H

#include "bcc.hpp"
#include "cachestat.hpp"
#include "iotop.hpp"

extern "C"
{
#include <argp.h>
}
enum OptionKind {
    IOTOP, 
    CACHESTAT,
    UNKNOWN,
};

class Options 
{
public:
    Options(char *tool);
    Controller *NewForController();
    OptionKind Kind();

    ~Options();

public:
    int m_opt_interval;
    union options{
        struct cachestate_option_t cachestat;
        struct iotop_options_t iotop;
    } m_opt_options;
    

private:

    OptionKind _kind;
};



#endif

