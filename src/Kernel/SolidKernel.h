#pragma once
#include"./AbstractDependency/AbstractConfig.h"

#include"./HardWare/Peripheral/Peripheral_PIN.h"

#include"./HardWare/WireProtocol/I2C_Component.h"
#include"./HardWare/WireProtocol/SPI_Component.h"
#include"./HardWare/WireProtocol/SCCB_Component.h"
    
#include"./HardWare/Peripheral/Peripheral_PWM.h"

#if __Enable_DCMI
    #include"./HardWare/Peripheral/Peripheral_DCMI.h"
#endif

#if __Enable_Uart
    #include"./HardWare/Peripheral/Peripheral_UART.h"
#endif

#if __Enable_SystemClock
    #include"./HardWare/Peripheral/SystemClock.h"
#endif

#if __Enable_Encoder
    #include"./HardWare/Peripheral/Peripheral_Encoder.h"
#endif


#include"./HardWare/MotorDriver/Modules.h"
#include"./HardWare/Internet/Modules.h"
#include"./HardWare/Bluetooth/Modules.h"
#include"./HardWare/Sensor/Modules.h"
#include"./HardWare/UserInterface/Modules.h"

#define Kernel_Init Kernel_Init

#if __Enable_Core
    #define Kernel_Run(x) Kernel_Run_##x
#else
    #define Kernel_Run Kernel_Run
#endif

#define Kernel_Exit Kernel_Exit