#include<Abstract/IOAbstract.h>

std::function<void(int chr)> PUT=nullptr;
std::function<void(u_char*)> GET=nullptr;


void IOAbstract::SetIO(){
    this->SetIO_GET();
    this->SetIO_PUT();
}

void IOAbstract::SetIO_PUT(){}

void IOAbstract::SetIO_GET(){}

int fputc(int ch,FILE *f){
    if(PUT){
        PUT(ch);
        return ch;
    }
    return -1;
}

int fgetc(FILE *f)
{
    u_char ch;
    if(GET){
        GET(&ch);
        return ch;
    }
    return -1;
}