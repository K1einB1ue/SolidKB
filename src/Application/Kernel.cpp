#include"./Application.h"

Application DevelopApp;


//硬件Entry
void Kernel_Init(){
    DevelopApp.Init();

}

//程序Entry
void Kernel_Run(){
    DevelopApp.Run();

}

void Kernel_Exit(){

}