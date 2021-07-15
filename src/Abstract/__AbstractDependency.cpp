#include<AbstractDependency/__AbstractDependency.h>

void Nullfunc(char index){
    (void*)index;
}

std::function<void(std::string,unsigned int*)> Debug::DebugCallback=nullptr;
std::stack<std::string> IndentStack;

std::queue<std::string> DebugQueue;
unsigned int Interruptnum=0;

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

static void DebugCall(){
    while(!DebugQueue.empty()){
        if(Debug::DebugCallback){
            if(!Interruptnum){
                std::string temp = DebugQueue.front();
                Debug::DebugCallback(temp,&Interruptnum);
                DebugQueue.pop();
                Interruptnum=0;
            }else{
                return;
            }
        }
    }
}

void Debug::Error(std::string Info){
    if(DebugCallback&&Indent){
        DebugQueue.push("\n"+IndentStr+"|<Error>"+Info);
        DebugCall();
    }
    while(1); 
}

void Debug::Warning(std::string Info){
    if(DebugCallback&&Indent){
        DebugQueue.push("\n"+IndentStr+"|<Warning>"+Info);
        DebugCall();
    }
}

void Debug::Info(std::string Info){
    if(DebugCallback&&Indent){
        DebugQueue.push("\n"+IndentStr+"|<Info>"+Info);
        DebugCall();
    }
}

void Debug::StartDebug(std::string Title){
    if(DebugCallback){
        IndentStack.push(Title);
        DebugQueue.push("\n"+IndentStr+"<"+Title+">");
        DebugCall();
        Indent++;
        RefreshIndent();
    }
}
void Debug::EndDebug(){
    if(DebugCallback){
        Indent--;
        RefreshIndent();
        DebugQueue.push("\n"+IndentStr+"<"+IndentStack.top()+">");
        DebugCall();
        IndentStack.pop();
    }
}

void Debug::StartBlock(std::string Title){
    if(DebugCallback&&Indent){
        IndentStack.push(Title);
        DebugQueue.push("\n"+IndentStr+"<"+Title+">");
        DebugCall();
        Indent++;
        RefreshIndent();
    }
}

void Debug::EndBlock(){
    if(DebugCallback&&Indent){
        Indent--;
        RefreshIndent();
        DebugQueue.push("\n"+IndentStr+"<"+IndentStack.top()+">");
        DebugCall();
        IndentStack.pop();
    }
}
void Debug::InterruptSend(std::string Info){
    if(DebugCallback){
        DebugQueue.push("\n-"+InterruptIndentStr+"<Interrupt>"+Info);
        DebugCall();
    }
}

void Debug::InterruptSend(char Info){
    static std::string temp;
    temp.clear();
    temp+=Info;
    if(DebugCallback){
        DebugQueue.push("\n-"+InterruptIndentStr+"<Interrupt>"+temp);
        DebugCall();
    }
}