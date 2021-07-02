#pragma once
#include<AbstractDependency/__AbstractDependency.h>


namespace IO{
    extern std::function<void(int chr)> PUT;
    extern std::function<void(u_char*)> GET;
}

class IOAbstract{
    void SetIO();
    virtual void SetIO_PUT();
    virtual void SetIO_GET();
};

