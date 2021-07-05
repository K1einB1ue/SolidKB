#include<AbstractDependency/__AbstractDependency.h>
std::function<void(std::string,DebugLevel)> DebugCallback=nullptr;

void Debug(std::string DebugInfo,DebugLevel Level){
    if(DebugCallback){
        DebugCallback(DebugInfo,Level);
    }
    while(1); 
};