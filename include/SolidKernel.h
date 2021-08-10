#pragma once
#include<AbstractDependency/___AbstractConfig.h>

#include<HardWare/Peripheral_PIN.h>

#include<SoftHardWare/I2C_Component.h>
#include<SoftHardWare/SPI_Component.h>
#include<SoftHardWare/SCCB_Component.h>
    
#include<HardWare/Peripheral_PWM.h>

#if __Enable_DCMI
    #include<HardWare/Peripheral_DCMI.h>
#endif

#if __Enable_Uart
    #include<HardWare/Peripheral_UART.h>
#endif

#if __Enable_SystemClock
    #include<SoftHardWare/SystemClock.h>
#endif

#if __Enable_Encoder
    #include<HardWare/Peripheral_Encoder.h>
#endif

#include<HardWare/MotorDriver/Modules.h>
#include<HardWare/Internet/Modules.h>
#include<HardWare/Bluetooth/Modules.h>
#include<HardWare/Sensor/Modules.h>
#include<HardWare/UserInterface/Modules.h>






#define Kernel_Init Kernel_Init

#define Kernel_Run Kernel_Run

#define Kernel_Exit Kernel_Exit