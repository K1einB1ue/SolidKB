#pragma once
#include<AbstractDependency/__AbstractDependency.h>

enum class Clock_Speed{
    LowSpeed,
    MidSpeed,
    HighSpeed,
};

class SystemClock{
    public:
    static void Clock(Clock_Speed speed);
    static void Delay(uint32_t us);
};
