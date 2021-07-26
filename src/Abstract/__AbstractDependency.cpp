#include<AbstractDependency/__AbstractDependency.h>


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

void Debug::EndBlockTitle(std::string Title){
    if(DebugCallback&&Indent){
        Indent--;
        RefreshIndent();
        DebugQueue.push("\n"+IndentStr+"["+Title+"]");
        DebugCall();
        IndentStack.pop();
    }
}


void Debug::EndOK(){
    Debug::EndBlockTitle("OK");
}

void Debug::EndFAIL(){
    Debug::EndBlockTitle("FAIL");
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


bool std::strcmp(const char* INstr,unsigned int IN_size,const char* Match,unsigned int Match_size){
    if(IN_size<Match_size){
        return false;
    }
    for(unsigned int i=0;i<Match_size;i++){
        if(INstr[i]!=Match[i]){
            return false;
        }
    }
    return true;
}

bool std::strcmp(const char* INstr,unsigned int IN_size,unsigned int StartPos,const char* Match,unsigned int Match_size){
    if(IN_size+StartPos<Match_size){
        return false;
    }
    for(unsigned int i=0;i<Match_size;i++){
        if(INstr[i+StartPos]!=Match[i]){
            return false;
        }
    }
    return true;
}

int std::Getint(const char* INstr,unsigned int *ptr){
    std::string temp;
    while(!(INstr[*ptr]>='0'&&INstr[*ptr]<='9')){
        if(INstr[*ptr]=='-'){
            if(INstr[(*ptr)+1]>='0'&&INstr[(*ptr)+1]<='9'){
                break;
            }
        }
        (*ptr)++;
    }
    temp+=INstr[(*ptr)++];
    while(INstr[*ptr]>='0'&&INstr[*ptr]<='9'){
        temp+=INstr[(*ptr)++];
    }
    return std::stoi(temp);
}

std::string std::Getstring(const char* INstr,char formatchar,unsigned int *ptr){
    std::string temp;
    while(INstr[(*ptr)++]!=formatchar);
    while(INstr[*ptr]!=formatchar){
        temp+=INstr[(*ptr)++];
    }
    return temp;
}