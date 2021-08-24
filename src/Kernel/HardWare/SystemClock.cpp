#include<Kernel/HardWare/SystemClock.h>
#include<AbstractDependency/_AbstractHardWare.h>

Clock_Speed SystemClock::clockSpeed=Clock_Speed::None;
#if __Enable_PWM
uint32_t SystemClock::PWM_Frequency=0;
#endif

void SystemClock::Clock(Clock_Speed speed){
    Override::ClockPrototypes[speed]();
    clockSpeed=speed;
}

void SystemClock::Delay(uint32_t us){
    Override::Delay_Prototype(us);
}
