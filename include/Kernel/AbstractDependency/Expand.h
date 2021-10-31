#pragma once
#include"./Standard.h"

namespace std{
    bool strcmp(const char* IN,unsigned int IN_size,const char* Match,unsigned int Match_size);
    bool strcmp(const char* IN,unsigned int IN_size,unsigned int StartPos,const char* Match,unsigned int Match_size);
    unsigned int FindFirst(const char* INstr,unsigned int IN_size,char Find,unsigned int *ptr); 
    unsigned int FindFirst(const char* INstr,unsigned int IN_size,char Find,unsigned int StartPos);
    unsigned int Find(const char* INstr,unsigned int IN_size,char Find,unsigned int StartPos,unsigned int Depth); 
    unsigned int Find(const char* INstr,unsigned int IN_size,char Find,unsigned int *ptr,unsigned int Depth);
    int Getint(const char* INstr,unsigned int *ptr);
    string Getstring(const char* INstr,char formatchar,unsigned int *ptr);
    string fto_string(float value);
}