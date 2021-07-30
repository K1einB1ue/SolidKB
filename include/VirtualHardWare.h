#pragma once
#include<AbstractDependency/___AbstractConfig.h>


#if __Enable_PIN
    #include<HardWare/Peripheral_PIN.h>
#endif

#if __Enable_PWM
    #include<HardWare/Peripheral_PWM.h>
#endif

#if __Enable_PIN&&__Enable_PWM
    #include<HardWare/TB6612FNG.h>
#endif

#if __Enable_TIM
    #include<HardWare/Peripheral_TIM.h>
#endif

#if __Enable_I2C_Component
    #include<SoftHardWare/I2C_Component.h>
    #include<SoftHardWare/SPI_Component.h>
    #include<SoftHardWare/SCCB_Component.h>
    #include<HardWare/SSD1306.h>
    #include<HardWare/MPU6050.h>
    #include<HardWare/AD7705.h>
    #include<HardWare/TOF10120.h>
    #include<HardWare/ADXL345.h>
    #if __Enable_DCMI
        #include<HardWare/Peripheral_DCMI.h>
        #include<HardWare/OV7725.h>
    #endif
#endif

#if __Enable_Uart
    #include<HardWare/Peripheral_UART.h>
    #include<HardWare/TOF10120.h>
    #include<HardWare/Computer.h>
    #ifdef __Enable_SystemClock
        #include<HardWare/ESP8266.h>
        #ifdef __Enable_PIN
            #include<HardWare/HC/HC_Modules.h>
        #endif
    #endif
    #include<HardWare/SYN6288.h>
#endif

#if __Enable_SystemClock
    #include<SoftHardWare/SystemClock.h>
#endif

#if __Enable_Encoder
    #include<HardWare/Peripheral_Encoder.h>
#endif


