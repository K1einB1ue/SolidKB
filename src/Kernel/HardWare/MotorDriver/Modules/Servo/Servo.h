#pragma once
#include"../../Common.hpp"

#if __Enable_PWM&&__Enable_SystemClock

namespace HardWare{
    class Servo{
        private:
        PWM Servo_PWM;
        public:
        Servo(uint32_t PWMx);
        
        void Servo_Euler_Degree(double Degree);
    };
}

#endif