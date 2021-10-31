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

    enum class Connection:u_char{
        Closed,
        Connect,
    };
}


namespace Mqtt{

    enum class Enum_Type:u_char{
        Reserved0       =0, //保留
        CONNECT         =1, //C->S  客户端请求连接服务端
        CNNNACK         =2, //S->C  连接报文确认
        PUBLISH         =3, //S--C  发布消息
        PUBACK          =4, //S--C  QoS 1 消息发布收到确认
        PUBREC          =5, //S--C  发布收到(保证交付第一步)
        PUBREL          =6, //S--C  发布释放(保证交付第二步)
        PUBCOMP         =7, //S--C  QoS 2 消息发布到确认
        SUBSCRIBE       =8, //C->S  客户端订阅请求   
        SUBACK          =9, //S->C  订阅请求报文确认
        UNSUBSCRIBE     =10,//C->S  客户端取消订阅请求
        UNSUBACK        =11,//S->C  取消订阅报文确认
        PINGREQ         =12,//C->S  心跳请求
        PINGRESP        =13,//S->C  心跳响应
        DISCONNECT      =14,//C->S  客户端断开连接
        Reserved15      =15,//保留
    };

    enum class Enum_Qos:u_char{
        Type0           =0, //最多分发一次  
        Type1           =1, //至少分发一次
        Type2           =2, //只分发一次
        Reserved        =3, //保留
    };

    union MqttLenPack{
        public:
        MqttLenPack():Continue(0),Length(0){}
        MqttLenPack(u_char Continue,u_char Length):Continue(Continue),Length(Length){}
        struct{
            u_char Continue     :1;
            u_char Length       :7;
        };
        u_char Byte;
    };

    union MqttHead{
        public:
        MqttHead(u_char Type,u_char Tag,u_char Qos):Type(Type),Tag(Tag),Qos(Qos),Reserved(0){}
        struct{
            u_char Type         :4;
            u_char Tag          :1;
            u_char Qos          :2;
            u_char Reserved     :1;
        };
        u_char Byte; 
    };

    //注意是UTF-8字符串.
    class MqttTansformer{
        private:
        std::string SendPack;
        bool Change=true;
        static std::string Protocol;
        public:
        Enum_Type Type=Enum_Type::Reserved0;
        Enum_Qos Qos=Enum_Qos::Reserved;
        u_char Tag=0;

        const std::string& MqttLize(const std::string& Info){
            this->SendPack.clear();
            MqttHead Head((u_char)Type,Tag,(u_char)Qos);
            //固定报头
            this->SendPack+=Head.Byte;
            MqttLenPack LenPack;
            unsigned int Size=Info.size();
            unsigned int Packnum=Size/0x7F;
            unsigned int Surplus=Size%0x7F;
            LenPack.Continue=1;
            LenPack.Length=0x7F;
            while(Packnum--){
                this->SendPack+=LenPack.Byte;
            }
            LenPack.Continue=0;
            LenPack.Length=Surplus;
            this->SendPack+=LenPack.Byte;
            //可变报头
            this->SendPack+='0';
            this->SendPack+=std::to_string(Protocol.size());
            this->SendPack+=Protocol;
            

            return this->SendPack;
        }
    };
    
}