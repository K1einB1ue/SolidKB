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

enum class DebugLevel{
    Warn,
    Error,
    Log,
};

extern std::function<void(std::string,DebugLevel)> DebugCallback;

extern void Debug(std::string DebugInfo,DebugLevel Level=DebugLevel::Error);


