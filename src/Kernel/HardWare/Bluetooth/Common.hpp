#pragma once
#include"../Peripheral/Peripheral_UART.h"
#include"../Peripheral/Peripheral_PIN.h"
#include"../Peripheral/SystemClock.h"

namespace HC{
    
    enum class State:u_char{
        NONE,
        OK,
        ERROR,
    };

    enum class FUx:u_char{
        None,
        FU1,
        FU2,
        FU3,
        FU4
    };

    enum class ROLE:u_char{
        None,
        Master,
        Slave
    };

}