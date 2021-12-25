#include"./Modules.h"

namespace Client{

    template<>
    MqttClient* MqttClientBuilder<HardWare::ESP8266>::Build(){
        MqttClient* client = new MqttClient();
        this->m_target->StreamCallback=[&](char chr){
            client->StreamIn(chr);
        };
        client->BindInterface([&](std::string arg){
            this->m_target->Socket_Send(arg);
            //Debug_InterruptSend(std::Hexlize(arg));
        });
        return client;
    }

    template<>
    void MqttClientBuilder<HardWare::ESP8266>::BrokerConnect(const std::string& IPaddress){
        this->m_target->TryExitPassThrough();
        this->m_target->Wifi_Reset();
        this->m_target->Set_WIFI_Mode(Wifi::Mode::SoftAP_Station);
        this->m_target->Set_WIFI_Connection(Wifi::Connection::Single);
        this->m_target->Set_WIFI_SendMode(Wifi::SendMode::Normal);
        this->m_target->Ref2Dis_WIFIList();
        if(this->m_internetInit){
            this->m_internetInit();
        }
        this->m_target->ping(IPaddress);
        this->m_target->Socket_Start(IPaddress,1883,Socket::Type::TCP);
        this->m_target->Set_WIFI_SendMode(Wifi::SendMode::Passthrough);
    }


}