#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"

enum class Clock_Speed{
    None,
    LowSpeed,
    MidSpeed,
    HighSpeed,
};

class SystemClock{ 
    public:
    static Clock_Speed clockSpeed;
    #if __Enable_PWM
        static uint32_t PWM_Frequency;
    #endif
    static void Clock(Clock_Speed speed);
    static void Delay(uint32_t us);
};
