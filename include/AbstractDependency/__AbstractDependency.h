#pragma once
#include<AbstractDependency/___AbstractConfig.h>
#include<stdint.h>
#include<vector>
#include<list>
#include<string>
#include<functional>
#include<map>
#include<math.h>
#include<memory>
#include<stack>
#include<queue>
#include<stdlib.h>
#include<stdarg.h>




__attribute__((optimize("O0"))) void Nullfunc(char index);
__attribute__((optimize("O0"))) void nop();

//禁止在高循环中StartBlock!
//中断中只允许使用InterruptSend!
namespace Debug{
    extern std::function<void(std::string,unsigned int *ptr)> DebugCallback;
    void InterruptSend(std::string Info);
    void InterruptSend(char Info);
    void Error(std::string Info);
    void Warning(std::string Info);
    void Info(std::string Info);
    void StartDebug(std::string Title);
    void EndDebug();
    void StartBlock(std::string Title);
    void EndBlock();
    void EndBlockTitle(std::string Title);
    void EndOK();
    void EndFAIL();
};


namespace std{
    bool strcmp(const char* IN,unsigned int IN_size,const char* Match,unsigned int Match_size);
    bool strcmp(const char* IN,unsigned int IN_size,unsigned int StartPos,const char* Match,unsigned int Match_size);
    int Getint(const char* INstr,unsigned int *ptr);
    std::string Getstring(const char* INstr,char formatchar,unsigned int *ptr);
}

