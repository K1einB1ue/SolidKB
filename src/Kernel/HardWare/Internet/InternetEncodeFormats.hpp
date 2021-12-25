#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"


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





#define IEF InternetEncodeFormats

namespace InternetEncodeFormats{

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

        namespace Sections{

            namespace FixedHeads{
                union CONNECT{
                    public:
                    CONNECT():ReversedBlock(0),Type((u_char)MsgType::CONNECT){}
                    struct{
                        u_char ReversedBlock:4;
                        u_char Type         :4;
                    };
                    u_char Byte;
                    operator char(){
                        return this->Byte;
                    }
                };

                union PUBLISH{
                    public:
                    PUBLISH():Retained(0),Qos(0),Tag(0),Type((u_char)MsgType::PUBLISH){}
                    struct{
                        u_char Retained     :1;
                        //Qos为Qos1或Qos2时需要添加额外的,建立连接开始记数的MessageID
                        u_char Qos          :2;
                        u_char Tag          :1;
                        u_char Type         :4;
                    };
                    u_char Byte;
                    operator char(){
                        return this->Byte;
                    }
                };

                union SUBSCRIBE{
                    public:
                    SUBSCRIBE():ReversedBlock(2),Type((u_char)MsgType::SUBSCRIBE){}
                    struct{
                        u_char ReversedBlock:4;
                        u_char Type         :4;
                    };
                    u_char Byte;
                    operator char(){
                        return this->Byte;
                    }
                };

                union PINGREQ{
                    public:
                    PINGREQ():ReversedBlock(0),Type((u_char)MsgType::PINGREQ){}
                    struct{
                        u_char ReversedBlock:4;
                        u_char Type         :4;
                    };
                    u_char Byte;
                    operator char(){
                        return this->Byte;
                    }
                };


            }
            namespace VariableHeads{
                union LenHead{
                    public:
                    LenHead():Length(0),Continue(0){}
                    struct{
                        u_char Length       :7;
                        u_char Continue     :1;
                    };
                    u_char Byte;
                    operator char(){
                        return this->Byte;
                    }
                };
                namespace CONNECT{
                    union ProtocolHead{
                        public:
                        ProtocolHead():ProtocolLevel(4),T_L('T'),T_H('T'),Q('Q'),M('M'),LSB(0x04),MSB(0){}
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
                        ConnectionHead():Reserved(0),CleanSession(1),WillFlag(0),WillQos(0),WillRetain(0),PasswordFlag(1),UserNameFlag(1){}
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
                        KeepAliveHead():LSB(0x64),MSB(0){}
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
            
            }         
        }

        class MqttPacks{
            private:
            static std::string BuildLenPack(unsigned int Size){
                Sections::VariableHeads::LenHead lenHead;
                std::string ret;
                while(Size){
                    unsigned int Rem;
                    Rem=Size%0x7F;
                    Size/=0x7F;
                    lenHead.Length=Rem;
                    lenHead.Continue=Size?1:0;
                    ret+=lenHead;
                }
                return ret;
            }

            public:
            static const std::string ConnectionPack(const std::string& ClientID,const std::string& UserName,const std::string& UserPassword){
                Sections::FixedHeads::CONNECT mqttHead;
                unsigned int Size=0;

                Sections::VariableHeads::CONNECT::ProtocolHead protocolHead;
                Size+=sizeof(protocolHead);

                Sections::VariableHeads::CONNECT::ConnectionHead connectionHead;
                connectionHead.UserNameFlag=1;
                connectionHead.PasswordFlag=1;
                connectionHead.WillRetain=0;
                connectionHead.WillQos=0;
                connectionHead.WillFlag=0;
                connectionHead.CleanSession=1;
                connectionHead.Reserved=0;
                Size+=sizeof(connectionHead);

                Sections::VariableHeads::CONNECT::KeepAliveHead keepAliveHead;
                keepAliveHead.SetSecond(100);
                Size+=sizeof(keepAliveHead);

                //Connection用户负载
                std::string clientIDlenPack=std::Streamlize(ClientID.size(),2);
                std::string userIDlenPack=std::Streamlize(UserName.size(),2);
                std::string userPasswordlenPack=std::Streamlize(UserPassword.size(),2);
                Size+=6;
                Size+=ClientID.size();
                Size+=UserName.size();
                Size+=UserPassword.size();

            
                std::string sendPack;
                sendPack+=mqttHead;
                sendPack+=BuildLenPack(Size);
                sendPack+=protocolHead;
                sendPack+=connectionHead;
                sendPack+=keepAliveHead;
                sendPack+=clientIDlenPack;
                sendPack+=ClientID;
                sendPack+=userIDlenPack;
                sendPack+=UserName;
                sendPack+=userPasswordlenPack;
                sendPack+=UserPassword;

                return sendPack;
            }

            static const std::string PublishPack(const std::string& Topic,const std::string Message,MsgQos Qos,bool Retained){
                Sections::FixedHeads::PUBLISH mqttHead;
                unsigned int Size=0;

                mqttHead.Qos=(u_char)Qos;
                mqttHead.Retained=Retained;

                Sections::VariableHeads::LenHead lenHead;
                std::string lenPack;

                std::string topiclenPack=std::Streamlize(Topic.size(),2);
                Size+=2;
                Size+=Topic.size();
                Size+=Message.size();

                std::string sendPack;
                sendPack+=mqttHead;
                sendPack+=BuildLenPack(Size);
                sendPack+=topiclenPack;
                sendPack+=Topic;
                sendPack+=Message;

                return sendPack;
            }

            static const std::string PingReqPack(){
                std::string sendPack;
                Sections::FixedHeads::PINGREQ mqttHead;
                sendPack+=mqttHead;
                sendPack+=(char)0;
                return sendPack;
            }

            static const std::string SubscribePack(const std::string& Topic,MsgQos Qos,u_int32_t MessageID){
                unsigned int Size=0;
                std::string sendPack;
                Sections::FixedHeads::SUBSCRIBE mqttHead;
                
                std::string msgIdPack=std::Streamlize(MessageID,2);
                std::string topiclenPack=std::Streamlize(Topic.size(),2);
                Size+=5;
                Size+=Topic.size();
                
                sendPack+=mqttHead;
                sendPack+=BuildLenPack(Size);
                sendPack+=msgIdPack;
                sendPack+=topiclenPack;
                sendPack+=Topic;
                sendPack+=(char)Qos;

                return sendPack;
            }
        };
    }

}
