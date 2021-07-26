#pragma once
#include<AbstractDependency/Standard.h>

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