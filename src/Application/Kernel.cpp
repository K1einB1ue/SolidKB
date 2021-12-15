#include"./Application.h"
// #include"./SampleApplication.h"
// #include"./MPU6050_TestApp.h"
// #include"./RaceApplication.h"

Application DevelopApp;         //开发用程序
//SampleApplication Sample;
//TestProgram::MPU6050 test;
//RaceApplication RaceApp;

//硬件Entry
void Kernel_Init(){
    DevelopApp.Init();
    //RaceApp.Init();
    //Sample.Init();
    //test.Init();
}

//程序Entry
void Kernel_Run(){
    DevelopApp.Run();
    //RaceApp.Run();
    //Sample.Run();
    //test.Run();
}

void Kernel_Exit(){

}