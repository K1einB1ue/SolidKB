#pragma once
#include"./Marco.h"
#include"./Standard.h"

#if __Enable_Debug

__attribute__((optimize("O0"))) void nop();

//禁止在高循环中StartBlock!
//中断中只允许使用InterruptSend!

namespace Debug{
    void BindCallback(std::function<void(std::string,unsigned int *ptr)> Callback);
    void InterruptSend(std::string Info);
    void InterruptSend(char Info);
    void InterruptSend(char* str,uint32_t size);
    //用于输出一些在绑定回调函数之前执行的代码,如构造函数.
    void StaticSend(std::string Info);
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

#endif