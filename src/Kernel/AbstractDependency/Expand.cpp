#include"./Expand.h"

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

unsigned int std::FindFirst(const char* INstr,unsigned int IN_size,char Find,unsigned int *ptr){
    while(INstr[*ptr]!=Find&&((*ptr)<=IN_size)){
        (*ptr)++;
    }
    return *ptr;
}

unsigned int std::FindFirst(const char* INstr,unsigned int IN_size,char Find,unsigned int StartPos){
    while(INstr[StartPos]!=Find&&StartPos<=IN_size){
        StartPos++;
    }
    return StartPos;
}

unsigned int std::Find(const char* INstr,unsigned int IN_size,char Find,unsigned int StartPos,unsigned int Depth){
    bool flag = false;
    while(StartPos<=IN_size&&Depth!=0){
        if(flag){
            StartPos++;
        }else{
            flag=true;
        }
        FindFirst(INstr,IN_size,Find,&StartPos);
        Depth--;
    }
    return StartPos;
}

unsigned int std::Find(const char* INstr,unsigned int IN_size,char Find,unsigned int *ptr,unsigned int Depth){
    bool flag = false;
    while((*ptr)<=IN_size&&Depth!=0){
        if(flag){
            (*ptr)++;
        }else{
            flag=true;
        }
        FindFirst(INstr,IN_size,Find,ptr);
        Depth--;
    }
    return *ptr;
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

//TODO:对于多线程支持不友好.且不同架构可能会有不同的表现,取决于GCC的sprintf实现!!!
std::string std::fto_string(float value){
    static char buffer[100];
    int temp1, temp2;
    temp1 = (int)(value*1000)%1000;
    temp2 = (int)(value);
    if (value < 0){
        sprintf(buffer, "-%d.%03d",-temp2,-temp1);
    }else{
        sprintf(buffer, "%d.%03d",temp2,temp1);
    }
    return buffer;
};

char HexTable[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
std::string std::Hexlize(const std::string& str){
    std::string ret;
    for(unsigned int i=0;i<str.size();i++){
        if(i!=0){
            ret+=' ';
        }
        ret+=HexTable[str[i]/16];
        ret+=HexTable[str[i]%16];
    }
    return ret;
}

std::string std::Hexlize(const char chr){
    std::string ret;
    ret+=HexTable[chr/16];
    ret+=HexTable[chr%16];
    return ret;
}

std::string std::Streamlize(u_int32_t value,u_char format_size){
    std::string ret;
    while(value&&format_size--){
        ret+=value%0xFF;
        value/=0xFF;
    }
    while(format_size--){
        ret+=(char)0;
    }
    std::reverse(ret.begin(),ret.end());
    return ret;
}

u_int32_t std::Valuelize(const std::string& str,u_int32_t start,u_int32_t end){
    u_int32_t value=0;
    for(;start<end;start++){
        value<<=8;
        value|=str[start];
    }
    return value;
}