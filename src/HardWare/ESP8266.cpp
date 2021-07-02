#include<HardWare/ESP8266.h>
#include<AbstractDependency/_AbstractHardWare.h>

namespace HardWare{

    ESP8266::ESP8266(uint32_t Uartx):Uart(Uartx,115200){
        this->Enable();

        this->NonReciveSend("AT+RST\r\n");
        SystemClock::Delay(500000);
        
        this->NonReciveSend("AT+CWMODE=2\r\n");
        SystemClock::Delay(500000);

        this->NonReciveSend("AT+CIPMUX=1\r\n");
        SystemClock::Delay(500000);

        this->NonReciveSend("AT+CIPSERVER=1,8080\r\n");
        SystemClock::Delay(500000);
        this->Open();

    }

}