#include"./Application.h"
#include"./SampleApplication.h"
#include"./MPU6050_TestApp.h"

Application DevelopApp;         //开发用程序 未启用
SampleApplication Sample;

//硬件Entry
void Kernel_Init(){
    Sample.Init();
}

//程序Entry
void Kernel_Run(){
    Sample.Run();
}

void Kernel_Exit(){

}