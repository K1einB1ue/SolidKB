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
#include<stdlib.h>
#include<stdarg.h>


namespace Debug{
    extern std::function<void(std::string)> DebugCallback;
    extern void InterruptSend(std::string Info);
    extern void Error(std::string Info);
    extern void Warning(std::string Info);
    extern void Info(std::string Info);
    extern void StartDebug(std::string Title);
    extern void EndDebug();
    extern void StartBlock(std::string Title);
    extern void EndBlock(std::string Title);
};

