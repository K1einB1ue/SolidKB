#pragma once
#include<AbstractDependency/___AbstractConfig.h>


#if __Enable_PIN
    #include<SoftHardWare/PIN.h>
#endif

#if __Enable_I2C_Component
    #include<SoftHardWare/I2C_Component.h>
    #include<HardWare/SSD1306.h>
#endif

#if __Enable_Uart
    #include<HardWare/Uart.h>
    #ifdef __Enable_SystemClock
        #include<HardWare/ESP8266.h>
        #include<HardWare/SYN6288.h>
    #endif
#endif

#if __Enable_SystemClock
    #include<SoftHardWare/SystemClock.h>
#endif
