#pragma once
#include<HardWare/Peripheral_UART.h>
#include<HardWare/Internet/Common.hpp>
#include<SoftHardWare/SystemClock.h>


#if __Enable_Uart&&__Enable_SystemClock

namespace HardWare{
    //WIFI模块
    //Type:[X]
    class ESP8266:public Peripheral_UART,protected DecoderContainer<char>{
        private:
        std::vector<Wifi::InfoPack> Wifi_List;
        Wifi::State State=Wifi::State::NONE;
        Wifi::Mode Mode=Wifi::Mode::SoftAP;
        Wifi::SendMode SendMode=Wifi::SendMode::Normal;
        Wifi::Connection Connection=Wifi::Connection::Single;
        bool IsServer=false;
        bool Wait();
        unsigned int pingTime=0;
        enum class InterruptCmd{
            None,
            PING,
            CWLAP,
        }Cmd;
        public:
        ESP8266(uint32_t Uartx);
        virtual ~ESP8266();
        #if __Enable_Debug
        std::function<void(std::string)> DisplayStart=Debug::StartBlock;
        std::function<void(std::string)> DisplayFunc=Debug::Info;
        std::function<void(void)> DisplayEnd=Debug::EndBlock;
        #else
        std::function<void(std::string)> DisplayStart=nullptr;
        std::function<void(std::string)> DisplayFunc=nullptr;
        std::function<void(void)> DisplayEnd=nullptr;
        #endif
        void Wifi_Reset();
        void Set_WIFI_Mode(Wifi::Mode mode);
        void Set_WIFI_Connection(Wifi::Connection connection);
        void Set_WIFI_SendMode(Wifi::SendMode sendMode);
        void Set_WIFI_Server(bool Enable,int Port_Param,int MaxConn=5);
        
        void Refresh_WIFIList();
        void Display_WIFIList();
        void Ref2Dis_WIFIList();
        void Connect_LastWIFI();
        void Connect_WIFI(u_char orderinlist,std::string Password);
        void Connect_WIFI(std::string SSID,std::string Password);
        void Connect_WIFI(std::string SSID);
        void DisConnect_WIFI();

        unsigned int ping(std::string IP);

        std::vector<std::pair<u_char,Socket::Connection>> SocketUserList;
        std::function<void(u_char,const char*,unsigned int)> SocketCallback=nullptr;
        void Socket_Start(std::string RemoteHost,int RemotePort,Socket::Type Type,unsigned int KeepAlive=0,u_char LinkID=0);
        void Socket_Start(std::string RemoteHost,int RemotePort,Socket::Type Type,std::string LocalIP,unsigned int KeepAlive=0,u_char LinkID=0);
        void Socket_End(u_char LinkID=0);
        void Socket_Send(const std::string Info,u_char LinkID=0);

    };
 
}


#endif
