#ifndef __BCC_USERSPACE_H
#define __BCC_USERSPACE_H


#include <argp.h>
#include <bits/types/error_t.h>
class Controller
{
public:
    virtual void Run() = 0;
};


#endif
