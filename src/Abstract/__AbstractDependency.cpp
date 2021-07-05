#include<AbstractDependency/__AbstractDependency.h>

std::function<void(std::string)> Debug::DebugCallback=nullptr;

void Debug::Error(std::string Info){
    if(DebugCallback){
        DebugCallback("\nError:"+Info);
    }
    while(1); 
}

void Debug::Warning(std::string Info){
    if(DebugCallback){
        DebugCallback("\nWarning:"+Info);
    }
}

void Debug::Info(std::string Info){
    if(DebugCallback){
        DebugCallback("\nInfo:"+Info);
    }
}