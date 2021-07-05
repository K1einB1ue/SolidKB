#include<Abstract/IOAbstract.h>



IOAbstract::IOAbstract(){}
IOAbstract::~IOAbstract(){}
void IOAbstract::Pre_Send(){}
void IOAbstract::Pre_Recv(){}
void IOAbstract::Send_char(u_char chr){}
void IOAbstract::Recv_char(u_char* chr_ptr){}

int IOAbstract::Printf(const char *fmt,...){
    va_list args;
    unsigned int n;
    char buffer[1024];
    Pre_Send();
    va_start(args,fmt);
    n = vsprintf(buffer,fmt,args);
    va_end(args);

    for(uint i = 0;i < n;i ++){
        Send_char(buffer[i]);
    }

    return n;
}

int IOAbstract::Scanf(const char *fmt,...){
    int i = 0;
    u_char c;
    va_list args;
    char buffer[1024];
        
    Pre_Recv();

    while(1){
        Recv_char(&c);
        if((c == 0x0d) || (c == 0x0a)){
            buffer[i] ='\0';
            break;
        }else{
            buffer[i++] = c;
        }
    }

    va_start(args,fmt);
    i = vsscanf(buffer,fmt,args);
    va_end(args);

    return i;
}