#include"./Application.h"
#include"./MPU6050_TestApp.h"

Application DevelopApp;
TestProgram::MPU6050 MPU6050_App;

//硬件Entry
void Kernel_Init(){
    //DevelopApp.Init();
    MPU6050_App.Init();
}

//程序Entry
void Kernel_Run(){
    //DevelopApp.Run();
    MPU6050_App.Run();
}

void Kernel_Exit(){

}