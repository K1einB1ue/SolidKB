#include<Kernel/HardWare/MotorDriver/Modules/Servo.h>

namespace HardWare{
    Servo::Servo(uint32_t PWMx):Servo_PWM(PWMx,20*SystemClock::PWM_Frequency,1000){}
        
    void Servo::Servo_Euler_Degree(double Degree){
        if(Degree>180.0){
            Servo_PWM=0.2;
        }else if(Degree<0){
            Servo_PWM=0.1;
        }else{
            Servo_PWM=(Degree/1800.0)+0.1;
        }
    }
}