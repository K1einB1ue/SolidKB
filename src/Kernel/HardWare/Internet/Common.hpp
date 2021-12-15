#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"
#include"../Peripheral/Peripheral_UART.h"
#include"../Peripheral/SystemClock.h"

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


namespace Client{
    class MqttClient{
        std::function<void(std::string)> streamInterface=nullptr;
        MqttClient(std::function<void(std::string)> interface){
            this->streamInterface=interface;
        }
    };
}


namespace EncodeFormats{

    namespace Mqtt{

        enum class MsgType:u_char{
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

        enum class MsgQos:u_char{
            Type0           =0, //最多分发一次  
            Type1           =1, //至少分发一次
            Type2           =2, //只分发一次
            Reserved        =3, //保留
        };


        //Mqtt报文组成: FixedHead->LenHead->VariableHead

        namespace Heads{

            union MqttHead{
                public:
                MqttHead():Type(0),Tag(0),Qos(0),Reserved(0){}
                struct{
                    u_char Reserved     :1;
                    u_char Qos          :2;
                    u_char Tag          :1;
                    u_char Type         :4;
                };
                u_char Byte; 
                operator char(){
                    return this->Byte;
                }
            };

            union LenHead{
                public:
                LenHead():Continue(0),Length(0){}
                struct{
                    u_char Length       :7;
                    u_char Continue     :1;
                };
                u_char Byte;
                operator char(){
                    return this->Byte;
                }
            };

            union VariableHead{
                public:
                VariableHead():MSB(0),LSB(0x04),M('M'),Q('Q'),T_H('T'),T_L('T'),ProtocolLevel(4){}
                struct{
                    u_char ProtocolLevel;
                    u_char T_H;
                    u_char T_L;
                    u_char Q;
                    u_char M;
                    u_char LSB;
                    u_char MSB;
                };
                const char str[7];
                operator const std::string(){
                    std::string ret;
                    for(int i=6;i>=0;i--){
                        ret+=str[i];
                    }
                    return ret;
                }
            };

            union ConnectionHead{
                public:
                ConnectionHead():UserNameFlag(1),PasswordFlag(1),WillRetain(0),WillQos(0),CleanSession(1),Reserved(0){}
                struct{
                    u_char Reserved     :1;
                    u_char CleanSession :1;
                    u_char WillFlag     :1;
                    u_char WillQos      :2;
                    u_char WillRetain   :1;
                    u_char PasswordFlag :1;
                    u_char UserNameFlag :1;
                };
                u_char Byte;

                operator char(){
                    return this->Byte;
                }
            };

            union KeepAliveHead{
                public:
                //默认为100s
                KeepAliveHead():MSB(0),LSB(0x64){}
                struct{
                    u_char LSB;
                    u_char MSB;
                };
                u_int16_t Bytes;
                void SetSecond(u_int16_t second){
                    this->Bytes=second;
                }
                operator std::string(){
                    std::string ret;
                    ret+=MSB;
                    ret+=LSB;
                    return ret;
                }
            };
        }

        class MqttPacks{

            public:
            static const std::string ConnectionPack(const std::string& ClientID,const std::string& UserID,const std::string& UserPassword){
                unsigned int Size=0;uint16_t size;
                std::string sendPack;
                

                //固定报头
                //MqttHead:标记Mqtt协议类型
                Heads::MqttHead mqttHead;
                mqttHead.Type=(u_char)MsgType::CONNECT;
                mqttHead.Tag=0;
                mqttHead.Qos=0;
                mqttHead.Reserved=0;
                //LenHead:记录协议字符串长度
                Heads::LenHead lenHead;
                std::string lenPack;

                //可变报头                      <--(需要开始记录长度)
                //VariableHead:MQTT协议标识
                Heads::VariableHead variableHead;
                Size+=sizeof(variableHead);
                //ConnectionHead:MQTT连接参数
                Heads::ConnectionHead connectionHead;
                connectionHead.UserNameFlag=1;
                connectionHead.PasswordFlag=1;
                connectionHead.WillRetain=0;
                connectionHead.WillQos=0;
                connectionHead.WillFlag=0;
                connectionHead.CleanSession=1;
                //connectionHead.Reserved=0;
                Size+=sizeof(connectionHead);
                //KeepAliveHead:保活包
                Heads::KeepAliveHead keepAliveHead;
                keepAliveHead.SetSecond(100);
                Size+=sizeof(keepAliveHead);
                //Connection用户负载
                std::string clientIDlenPack,userIDlenPack,userPasswordlenPack;

                size=ClientID.size();
                clientIDlenPack+=size/0xFF;
                clientIDlenPack+=size%0xFF;
                size = UserID.size();
                userIDlenPack+=size/0xFF;
                userIDlenPack+=size%0xFF;
                size = UserPassword.size();
                userPasswordlenPack+=size/0xFF;
                userPasswordlenPack+=size%0xFF;
                
                Size+=6;
                Size+=ClientID.size();
                Size+=UserID.size();
                Size+=UserPassword.size();

                
                
                while(Size){
                    unsigned int Rem;
                    Rem=Size%0x7F;
                    Size/=0x7F;
                    lenHead.Length=Rem;
                    lenHead.Continue=Size?1:0;
                    lenPack+=lenHead;
                }

                sendPack+=mqttHead;
                sendPack+=lenPack;
                sendPack+=variableHead;
                sendPack+=connectionHead;
                sendPack+=keepAliveHead;
                sendPack+=clientIDlenPack;
                sendPack+=ClientID;
                sendPack+=userIDlenPack;
                sendPack+=UserID;
                sendPack+=userPasswordlenPack;
                sendPack+=UserPassword;

                return sendPack;
            }

            static const std::string PublishPack(const std::string& Topic,const std::string Message,MsgQos Qos,bool Retained){
                unsigned int Size=0;uint16_t size;
                std::string sendPack;
                Heads::MqttHead mqttHead;
                mqttHead.Type=(u_char)MsgType::PUBLISH;
                mqttHead.Qos=(u_char)Qos;
                //在Publish包中Reserved为Retained标志位
                mqttHead.Reserved=Retained;

                Heads::LenHead lenHead;
                std::string lenPack;

                std::string topiclenPack;
                size = Topic.size();
                topiclenPack+=size/0xFF;
                topiclenPack+=size%0xFF;

                Size+=2;
                Size+=Topic.size();
                Size+=Message.size();

                while(Size){
                    unsigned int Rem;
                    Rem=Size%0x7F;
                    Size/=0x7F;
                    lenHead.Length=Rem;
                    lenHead.Continue=Size?1:0;
                    lenPack+=lenHead;
                }
                
                sendPack+=mqttHead;
                sendPack+=lenPack;
                sendPack+=topiclenPack;
                sendPack+=Topic;
                sendPack+=Message;

                return sendPack;
            }

            static const std::string PingReqPack(){
                std::string sendPack;
                //固定报头
                //FixedHead:标记Mqtt协议类型
                Heads::MqttHead mqttHead;
                mqttHead.Type=(u_char)MsgType::PINGREQ;
                sendPack+=mqttHead;
                return sendPack;
            }

            
        };
    }
    
    
}