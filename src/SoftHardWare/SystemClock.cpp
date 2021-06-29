#include<SoftHardWare/SystemClock.h>
#include<AbstractDependency/_AbstractHardWare.h>

void SystemClock::Clock(Clock_Speed speed){
    Override::ClockPrototypes[speed]();
}

void SystemClock::Delay(uint32_t us){
    Override::Delay_Prototype(us);
}
