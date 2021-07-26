#pragma once
#include<AbstractDependency/Standard.h>

namespace std{
    bool strcmp(const char* IN,unsigned int IN_size,const char* Match,unsigned int Match_size);
    bool strcmp(const char* IN,unsigned int IN_size,unsigned int StartPos,const char* Match,unsigned int Match_size);
    int Getint(const char* INstr,unsigned int *ptr);
    std::string Getstring(const char* INstr,char formatchar,unsigned int *ptr);
}