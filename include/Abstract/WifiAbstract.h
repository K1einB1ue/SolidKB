#pragma once
#include<AbstractDependency/__AbstractDependency.h>

namespace Wifi{
    enum class Mode:u_char{
        SoftAP,
        Station,
        SoftAP_Station
    };

    enum class State:u_char{
        NONE,
        OK,
        ERROR,
    };

    enum class ECN:u_char{
        OPEN,
        WEP,
        WPA_PSK,
        WPA2_PSK,
        WPA_WPA2_PSK,
        WPA2_ENTERPRISE,
        WPA3_PSK,
        WPA2_WPA3_PSK,
        WAPI_PSK
    };

    enum class Connection:u_char{
        Multi,
        Single
    };

    enum class SendMode:u_char{
        Normal,
        PassthroughReciving,
        Passthrough,
    };

    struct InfoPack{
        Wifi::ECN ECN;           //加密方式
        std::string SSID;       //WIFI名
        int RSSI;               //信号强度
        std::string MAC;        //MAC地址
        int Channel;            //信道号
    };
}


namespace Socket{
    enum class Type:u_char{
        TCP,
        TCPv6,
    };


    extern std::string SocketEndFlag;
}