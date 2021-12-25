#pragma once

#include"./Modules/ESP8266/ESP8266.h"
#include"./Modules/W5500/W5500.h"


namespace Client{
    //TODO:考虑后期更新更好的接口,以将所有的选项接口暴露出来.
    class MqttClient{
        private:
        class MqttSentenceGetter{
            private:
            bool getLen=false;
            u_int16_t length=0;
            u_char times=0;
            std::function<void(std::string)> m_callback=nullptr;
            std::string m_sentence;
            
            public:
            MqttSentenceGetter(){}

            void BindCallback(std::function<void(std::string)> callback){
                this->m_callback=callback;
            }

            void StreamIn(char index){
                if(!getLen){
                    length<<=8;
                    length|=index;
                    if(times++==1){
                        getLen=true;
                    }
                }else if(length){
                    m_sentence+=index;
                    length--;
                }else{
                    if(m_callback){
                        m_callback(this->m_sentence);
                        this->m_callback=nullptr;
                    }
                    this->getLen=false;
                    this->length=0;
                    this->times=0;
                    this->m_sentence.clear();
                }
            }
        };

        bool m_workingFlag=false;

        public:
        std::function<void(std::string)> streamInterface=nullptr;
        u_int16_t MsgID;

        void StreamIn(char index){
            MqttSentenceGetter getter;
            if(!m_workingFlag){
                switch(index){
                    case 0x20:
                        getter.BindCallback([&](auto args){
                            Debug_InterruptSend("MQTT CONNECTED!");
                            this->m_workingFlag=false;
                        });
                    break;
                    case 0x90:
                        getter.BindCallback([&](auto args){
                            MsgID = std::Valuelize(args,0,2);
                            u_char Qos = std::Valuelize(args,2,3);
                            Debug_InterruptSend("MQTT SUBSCRIBED!");
                            this->m_workingFlag=false;
                        });
                    default:return;
                }
                m_workingFlag=true;
                return;
            }else{
                getter.StreamIn(index);
            }
        }

        MqttClient(){}

        

        void BindInterface(std::function<void(std::string)> interface){
            this->streamInterface=interface;
        }

        void Publish(const std::string&Topic, const std::string& Message,IEF::Mqtt::MsgQos Qos=IEF::Mqtt::MsgQos::Type0,bool Retained=false){
            this->streamInterface(IEF::Mqtt::MqttPacks::PublishPack(Topic,Message,Qos,Retained));
        }

        void Connect(const std::string& ClientID,const std::string& UserName,const std::string& UserPassword){
            this->streamInterface(IEF::Mqtt::MqttPacks::ConnectionPack(ClientID,UserName,UserPassword));
        }

        void Subscribe(const std::string& Topic,IEF::Mqtt::MsgQos Qos){
            this->streamInterface(IEF::Mqtt::MqttPacks::SubscribePack(Topic,Qos,MsgID+1));
        }

        void KeepAlive(){
            this->streamInterface(IEF::Mqtt::MqttPacks::PingReqPack());
        }

    };


        



    template<typename T>
    class MqttClientBuilder{
        T* m_target;
        MqttClient* m_client;
        std::function<void(void)> m_internetInit=nullptr;
        public:
        MqttClientBuilder(){}

        MqttClient* Build();
        void BrokerConnect(const std::string& IPaddress);
        void BindInternetInit(T* target,std::function<void(void)> initAction){
            this->m_target=target;
            this->m_internetInit=initAction;
        }
    };

    class HttpClient{
        public:
        std::function<void(std::string)> streamInterface=nullptr;
        void StreamIn(char index){}
    };



}