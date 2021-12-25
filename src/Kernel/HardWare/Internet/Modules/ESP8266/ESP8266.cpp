#include"./ESP8266.h"

#if __Enable_Uart&&__Enable_SystemClock

namespace HardWare{

    ESP8266::ESP8266(uint32_t Uartx):Peripheral_UART(Uartx,115200){
        this->Set_Container_Size(200);
        this->End("\r\n",2);
        this->End_Clear(true);
        this->End_Decoder([&](char* Data,unsigned int Size){
            std::stack<char> Analyze;
            if(std::strcmp(Data,Size,"OK",2)){
                this->State=Wifi::State::OK;
                return;
            }else if(std::strcmp(Data,Size,"ERROR",5)){
                this->State=Wifi::State::ERROR;
                return;
            }
            
            if(Data[0]=='+'){    
                Wifi::InfoPack temp;    
                unsigned int ptr;   
                if(std::strcmp(Data,Size,1,"IPD",3)){
                    unsigned int ptr=4;
                    if(this->Connection==Wifi::Connection::Multi){
                        std::FindFirst(Data,Size,',',&ptr);
                        int Link_ID = std::Getint(Data,&ptr);
                        int Len = std::Getint(Data,&ptr);
                        std::FindFirst(Data,Size,',',&ptr);
                        if(SocketCallback){
                            this->SocketCallback(Link_ID,Data+ptr,Len);
                        }
                        return;
                    }else if(this->Connection==Wifi::Connection::Single){
                        std::FindFirst(Data,Size,',',&ptr);
                        int Len = std::Getint(Data,&ptr);
                        std::FindFirst(Data,Size,',',&ptr);
                        if(SocketCallback){
                            this->SocketCallback(0,Data+ptr,Len);
                        }
                        return;
                    }
                }else if(std::strcmp(Data,Size,1,"CIPSTA",6)){
                    unsigned int ptr;
                    if(std::strcmp(Data,Size,8,"ip",2)){
                        ptr=10;
                        this->IPaddr=std::Getstring(Data,'\"',&ptr);
                        return;
                    }
                }
                switch (this->Cmd) {
                case InterruptCmd::CWLAP:
                    ptr=8;                   
                    temp.ECN=(Wifi::ECN)std::Getint(Data,&ptr);
                    temp.SSID=std::Getstring(Data,'\"',&ptr);
                    temp.RSSI=std::Getint(Data,&ptr);
                    temp.MAC=std::Getstring(Data,'\"',&ptr);
                    temp.Channel=std::Getint(Data,&ptr);
                    this->Wifi_List.push_back(temp);           
                    break;
                case InterruptCmd::PING:
                    ptr=1;
                    this->pingTime=std::Getint(Data,&ptr);
                    break;
                case InterruptCmd::None:
                default:break;
                }         
            }
        });
        this->BindCallback([&](char chr){
            if(this->SendMode!=Wifi::SendMode::Passthrough){
                this->StreamIn(chr);
            }else if(this->StreamCallback){
                this->StreamCallback(chr);
            }
        });

        
    }
    /** @brief  复位Wifi
     * @retval None.
     */
    void ESP8266::Wifi_Reset(){
        this->Send("AT+RST\r\n");
        Debug_StartBlock("Wifi Reset");
        if(this->Wait()){ 
            Debug_Info("Reset Success");
            SystemClock::Delay(300000);
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    bool ESP8266::Wait(){
        this->State=Wifi::State::NONE;
        unsigned int i;
        for(i=0;i<4000;i++){
            SystemClock::Delay(1000);
            if(this->State!=Wifi::State::NONE){
                break;
            }
        }
        this->Cmd=InterruptCmd::None;
        if(i>=4000){
            Debug_Warning("TimeOut!");
            return false;
        }else{
            if(this->State==Wifi::State::OK){
                return true;
            }else{
                Debug_Warning("ERROR");
                return false;
            }
        }
    }

    /** @brief  设置Wifi模式
     * @param  mode Station:作为一个客户端. SoftAP:作为一个服务器. SoftAP_Station:同时.
     * @retval None.
     */
    void ESP8266::Set_WIFI_Mode(Wifi::Mode mode){
        Debug_StartBlock("Wifi Mode");
        switch (mode){
        case Wifi::Mode::Station:
            this->Send("AT+CWMODE=1\r\n");
            this->Mode=Wifi::Mode::Station;   
            break;
        case Wifi::Mode::SoftAP:
            this->Send("AT+CWMODE=2\r\n");
            this->Mode=Wifi::Mode::SoftAP;
            break;
        case Wifi::Mode::SoftAP_Station:
            this->Send("AT+CWMODE=3\r\n");
            this->Mode=Wifi::Mode::SoftAP_Station;
            break;
        default:
            break;
        }       
        if(this->Wait()){ 
            Debug_Info("Change to "+std::to_string((u_char)mode));
            this->Mode=mode;
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    /** @brief  设置Wifi连接模式
     * @param  connection Multi:多连接. Single:单连接.
     * @retval None.
     */
    void ESP8266::Set_WIFI_Connection(Wifi::Connection connection){
        Debug_StartBlock("Wifi Connection");
        switch (connection){
        case Wifi::Connection::Multi:
            if(this->SendMode!=Wifi::SendMode::Normal){
                this->Set_WIFI_SendMode(Wifi::SendMode::Normal);
            }
            this->Send("AT+CIPMUX=1\r\n");
            break;
        case Wifi::Connection::Single:
            this->Send("AT+CIPMUX=0\r\n");
            break;
        default:
            break;
        }
        if(this->Wait()){ 
            Debug_Info("Change to "+std::to_string((u_char)connection));
            this->Connection=connection;
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    /** @brief  设置Wifi发送模式
     * @param  sendMode Normal:标准(有包文). PassthroughReciving:透传接受(只有接受模式是透传的). Passthrough:透传.
     * @retval None.
     */
    void ESP8266::Set_WIFI_SendMode(Wifi::SendMode sendMode){
        Debug_InterruptSend("Wifi SendMode:"+std::to_string((u_char)SendMode)+" to "+std::to_string((u_char)sendMode));
        switch (sendMode){
        case Wifi::SendMode::Normal:
            switch (this->SendMode){
            case Wifi::SendMode::Normal:
                return;
            case Wifi::SendMode::PassthroughReciving:
                this->Send("AT+CIPMODE=0\r\n");
                break;
            case Wifi::SendMode::Passthrough:
                this->Set_WIFI_SendMode(Wifi::SendMode::PassthroughReciving);
                this->Set_WIFI_SendMode(Wifi::SendMode::Normal);
                return;
            }
            break;
        case Wifi::SendMode::PassthroughReciving:
            switch (this->SendMode){
            case Wifi::SendMode::Normal:
                if(this->Connection!=Wifi::Connection::Single){
                    Debug_Warning("Should be Set_WIFI_Connection(Wifi::Connection::Single)");
                }
                this->Send("AT+CIPMODE=1\r\n");
                break;
            case Wifi::SendMode::PassthroughReciving:
                return;
            case Wifi::SendMode::Passthrough:
                SystemClock::Delay(40000);
                this->Send("+++");
                SystemClock::Delay(1000000);
                break;
            }
            break;
        case Wifi::SendMode::Passthrough:
            switch (this->SendMode){
            case Wifi::SendMode::Normal:
                this->Set_WIFI_SendMode(Wifi::SendMode::PassthroughReciving);
                this->Set_WIFI_SendMode(Wifi::SendMode::Passthrough);
                return;
            case Wifi::SendMode::PassthroughReciving:
                this->Send("AT+CIPSEND\r\n");
                break;
            case Wifi::SendMode::Passthrough:
                return;
            }
            break;
        }
        if(this->Wait()){ 
            Debug_Info("Change to "+std::to_string((u_char)sendMode));
            this->SendMode=sendMode;
        }
    }

    void ESP8266::TryExitPassThrough(){
        SystemClock::Delay(40000);
        this->Send("+++");
        SystemClock::Delay(1000000);
        return;
    }

    void ESP8266::Set_WIFI_Server(bool Enable,int Port_Param,int MaxConn){
        Debug_StartBlock("Wifi Client MaxNum");
        this->Send("AT+CIPSERVERMAXCONN="+std::to_string(MaxConn)+"\r\n");
        if(this->Wait()){ 
            Debug_Info("Change to "+std::to_string(MaxConn));
            Debug_EndOK();
        }else{           
            Debug_EndFAIL();
            return;
        }
        Debug_StartBlock("Wifi Server");
        if(Enable){
            if(this->Connection!=Wifi::Connection::Multi){
                this->Set_WIFI_Connection(Wifi::Connection::Multi);
            }
        }
        this->Send("AT+CIPSERVER="+std::to_string(Enable)+","+std::to_string(Port_Param)+"\r\n");
        if(this->Wait()){ 
            Debug_Info("Change to "+std::to_string(Enable));
            this->IsServer=Enable;
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    void ESP8266::Display_THISAddr(){
        Debug_StartBlock("Wifi THIS IPAddr");
        this->Send("AT+CIPSTA?\r\n");
        if(this->Wait()){ 
            Debug_Info("IPv4:"+this->IPaddr);
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    void ESP8266::Refresh_WIFIList(){
        this->Cmd=InterruptCmd::CWLAP;
        this->Wifi_List.clear();
        this->Send("AT+CWLAP\r\n");
        Debug_StartBlock("Wifi List");
        if(this->Wait()){        
            Debug_Info("Refreshed num="+std::to_string(this->Wifi_List.size()));
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
        SystemClock::Delay(2000000);
    }


    

    

    void ESP8266::Display_WIFIList(){
        if(!this->DisplayFunc){
            return;
        }
        if(this->DisplayStart){
            this->DisplayStart("Wifi List");
        }
        for(unsigned int i=0; i<this->Wifi_List.size();i++){
            this->DisplayFunc(
                "ENC="+std::to_string((u_char)this->Wifi_List[i].ECN)+
                ",SSID="+this->Wifi_List[i].SSID+
                ",RSSI="+std::to_string(this->Wifi_List[i].RSSI)+
                ",MAC="+this->Wifi_List[i].MAC+
                ",Channel="+std::to_string(this->Wifi_List[i].Channel)
            );
        }
        if(this->DisplayEnd){
            this->DisplayEnd();
        }
    }

    void ESP8266::Ref2Dis_WIFIList(){
        this->Refresh_WIFIList();
        this->Display_WIFIList();
    }

    void ESP8266::Connect_LastWIFI(){  
        this->Send("AT+CWJAP\r\n");
        Debug_StartBlock("Wifi Connect LastWIFI");
        if(this->Wait()){        
            Debug_Info("Connected");
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    void ESP8266::Connect_WIFI(std::string SSID,std::string Password){
        this->Send("AT+CWJAP=\""+SSID+"\",\""+Password+"\"\r\n");
        Debug_StartBlock("Wifi Connect "+ SSID);
        if(this->Wait()){
            Debug_Info("Connected");
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }  
    }

    void ESP8266::Connect_WIFI(u_char orderinlist,std::string Password){
        orderinlist++;
        if(orderinlist<=this->Wifi_List.size()){
            this->Send("AT+CWJAP="+this->Wifi_List[orderinlist].SSID+","+Password+","+this->Wifi_List[orderinlist].MAC+"\r\n");
            Debug_StartBlock("Wifi Connect "+ this->Wifi_List[orderinlist].SSID);
            if(this->Wait()){
                Debug_Info("Connected");
                Debug_EndOK();
            }else{
                Debug_EndFAIL();
            }
        }else{
            Debug_StartBlock("Wifi Connect Miss");
                Debug_Warning("NULL Connection!");
            Debug_EndFAIL();
        }
    }
    void ESP8266::Connect_WIFI(std::string SSID){
        this->Connect_WIFI(SSID,"");
    }
    unsigned int ESP8266::ping(std::string IP){
        this->Cmd=InterruptCmd::PING;
        this->Send("AT+PING=\""+IP+"\"\r\n");
        Debug_StartBlock("PING");
        if(this->Wait()){
            Debug_Info(std::to_string(this->pingTime)+"ms");
            Debug_EndOK();
            return this->pingTime;
        }else{
            Debug_EndFAIL();
            return 0;
        }
    }

    void ESP8266::DisConnect_WIFI(){

    }

    ESP8266::~ESP8266(){}

    void ESP8266::Socket_Start(std::string RemoteHost,int RemotePort,Socket::Type Type,unsigned int KeepAlive,u_char LinkID){
        if(this->Connection==Wifi::Connection::Single){
            switch (Type){
            case Socket::Type::TCP:
                this->Send("AT+CIPSTART=\"TCP\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+"\r\n");
                break;
            case Socket::Type::TCPv6:
                this->Send("AT+CIPSTART=\"TCPv6\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+"\r\n");
                break;
            default:
                break;
            }
            
        }else if(this->Connection==Wifi::Connection::Multi){
            switch (Type){
            case Socket::Type::TCP:
                this->Send("AT+CIPSTART="+std::to_string(LinkID)+",\"TCP\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+"\r\n");
                break;
            case Socket::Type::TCPv6:
                this->Send("AT+CIPSTART="+std::to_string(LinkID)+",\"TCPv6\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+"\r\n");
                break;
            default:
                break;
            }
        }
        Debug_StartBlock("Wifi Socket Connection");
        if(this->Wait()){        
            Debug_Info("Connect To IP:"+RemoteHost+" Port:"+std::to_string(RemotePort));
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
        
    }

    void ESP8266::Socket_Start(std::string RemoteHost,int RemotePort,Socket::Type Type,std::string LocalIP,unsigned int KeepAlive,u_char LinkID){
        if(this->Connection==Wifi::Connection::Single){
            switch (Type){
            case Socket::Type::TCP:
                this->Send("AT+CIPSTART=\"TCP\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+",\""+LocalIP+"\"\r\n");
                break;
            case Socket::Type::TCPv6:
                this->Send("AT+CIPSTART=\"TCPv6\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+",\""+LocalIP+"\"\r\n");
                break;
            default:
                break;
            }
            
        }else if(this->Connection==Wifi::Connection::Multi){
            switch (Type){
            case Socket::Type::TCP:
                this->Send("AT+CIPSTART="+std::to_string(LinkID)+",\"TCP\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+",\""+LocalIP+"\"\r\n");
                break;
            case Socket::Type::TCPv6:
                this->Send("AT+CIPSTART="+std::to_string(LinkID)+",\"TCPv6\",\""+RemoteHost+"\","+std::to_string(RemotePort)+","+std::to_string(KeepAlive)+",\""+LocalIP+"\"\r\n");
                break;
            default:
                break;
            }
        }
        Debug_StartBlock("Wifi Socket Connection");
        if(this->Wait()){        
            Debug_Info("Connect To IP:"+RemoteHost+" Port:"+std::to_string(RemotePort));
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    void ESP8266::Socket_End(u_char LinkID){
        Debug_StartBlock("Wifi Socket Disconnection");
        if(this->Connection==Wifi::Connection::Single){
            this->Send("AT+CIPCLOSE\r\n");
        }else if(this->Connection==Wifi::Connection::Multi){
            this->Send("AT+CIPCLOSE="+std::to_string(LinkID)+"\r\n");
        }
        if(this->Wait()){        
            Debug_Info("Disconnected");
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
    }

    void ESP8266::Socket_Send(const std::string Info,u_char LinkID){
        if(this->Connection==Wifi::Connection::Single&&this->SendMode!=Wifi::SendMode::Passthrough){
            this->Send("AT+CIPSEND="+std::to_string(Info.size())+"\r\n");
        }else if(this->Connection==Wifi::Connection::Multi){
            this->Send("AT+CIPSEND="+std::to_string(LinkID)+","+std::to_string(Info.size())+"\r\n");
        }else if(this->SendMode==Wifi::SendMode::Passthrough){
            this->Send(Info);
            //Debug_InterruptSend("Wifi Passthrough Send!");
            return;
        }
        Debug_StartBlock("Wifi Socket Send");
        if(this->Wait()){        
            Debug_Info("Send");
            this->Send(Info);
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
        
        
    }
}


    /*
    ESP8266_M->Wifi_Reset();
    ESP8266_M->Set_WIFI_Mode(Wifi::Mode::SoftAP);
    ESP8266_M->Set_WIFI_SendMode(Wifi::SendMode::Normal);
    ESP8266_M->Set_WIFI_Connection(Wifi::Connection::Multi);
    ESP8266_M->Set_WIFI_Server(true,5000,5);


    ESP8266_M->BindCallback([](char* Str,unsigned int Size){
        bool Flag0=false,Flag1=false;
        std::string LenStr,InfoStr;
        int DotCnt=0,Len=0;
        if(Size<=10){
            return;
        }

        for(unsigned int i=0;i<Size;i++){
            if(Str[i]==','&&!Flag0){
                DotCnt++;
                if(DotCnt==2){
                    Flag0=true;
                }  
            }else if(Flag0){
                if(Str[i]==':'&&!Flag1){
                    Flag1=true;
                    Len=std::stoi(LenStr);
                }else if(!Flag1){
                    LenStr+=Str[i];
                }else if(Flag1){
                    if(Len){
                        Len--;
                        InfoStr+=Str[i];
                    }else{
                        Decoder(InfoStr);
                        return;
                    }
                }
            }
        }
    });
    */


#endif