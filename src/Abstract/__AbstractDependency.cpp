#include<AbstractDependency/__AbstractDependency.h>

std::function<void(std::string)> Debug::DebugCallback=nullptr;
std::stack<std::string> IndentStack;

static u_char Indent=0;
static std::string IndentStr="",InterruptIndentStr="";
void RefreshIndent(){
    IndentStr.resize(Indent*2);
    InterruptIndentStr.resize(Indent*2);
    char* tmp = const_cast<char*>(IndentStr.c_str());
    char* temp =const_cast<char*>(InterruptIndentStr.c_str());
    for(u_char i=0;i<IndentStr.size();i++){
        tmp[i]=' ';
        temp[i]='-';
    }
}

void Debug::Error(std::string Info){
    if(DebugCallback&&Indent){
        DebugCallback("\n"+IndentStr+"|<Error>"+Info);
    }
    while(1); 
}

void Debug::Warning(std::string Info){
    if(DebugCallback&&Indent){
        DebugCallback("\n"+IndentStr+"|<Warning>"+Info);
    }
}

void Debug::Info(std::string Info){
    if(DebugCallback&&Indent){
        DebugCallback("\n"+IndentStr+"|<Info>"+Info);
    }
}

void Debug::StartDebug(std::string Title){
    if(DebugCallback){
        IndentStack.push(Title);
        DebugCallback("\n"+IndentStr+"<"+Title+">");
        Indent++;
        RefreshIndent();
    }
}
void Debug::EndDebug(){
    if(DebugCallback){
        Indent--;
        RefreshIndent();
        DebugCallback("\n"+IndentStr+"<"+IndentStack.top()+">");
        IndentStack.pop();
    }
}

void Debug::StartBlock(std::string Title){
    if(DebugCallback&&Indent){
        IndentStack.push(Title);
        DebugCallback("\n"+IndentStr+"<"+Title+">");
        Indent++;
        RefreshIndent();
    }
}

void Debug::EndBlock(){
    if(DebugCallback&&Indent){
        Indent--;
        RefreshIndent();
        DebugCallback("\n"+IndentStr+"<"+IndentStack.top()+">");
        IndentStack.pop();
    }
}
void Debug::InterruptSend(std::string Info){
    if(DebugCallback){
        DebugCallback("\n-"+InterruptIndentStr+"<Interrupt>"+Info);
    }
}