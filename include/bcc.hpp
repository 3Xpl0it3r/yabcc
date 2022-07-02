#ifndef __BCC_USERSPACE_H
#define __BCC_USERSPACE_H

class Controller
{
public:
    virtual unsigned int Run() = 0;
    virtual void Stop() = 0;
};




#endif
