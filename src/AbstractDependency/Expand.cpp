#include<AbstractDependency/Expand.h>

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