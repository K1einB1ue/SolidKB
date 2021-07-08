#pragma once
#include<AbstractDependency/___AbstractConfig.h>


#if __Enable_PIN
    #include<SoftHardWare/PIN.h>
#endif

#if __Enable_I2C_Component
    #include<SoftHardWare/I2C_Component.h>
    #include<HardWare/SSD1306.h>
    #include<HardWare/MPU6050.h>
    #if __Enable_DCMI
        #include<HardWare/Peripheral_DCMI.h>
        #include<HardWare/OV7725.h>
    #endif
#endif

#if __Enable_Uart
    #include<HardWare/Peripheral_UART.h>
    #include<HardWare/Computer.h>
    #ifdef __Enable_SystemClock
        #include<HardWare/ESP8266.h>
    #endif
    #include<HardWare/SYN6288.h>
#endif

#if __Enable_SystemClock
    #include<SoftHardWare/SystemClock.h>
#endif
