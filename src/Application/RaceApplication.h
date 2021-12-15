#pragma once
#include<SolidKernel.h>

enum class Direction {
    West,East,North,South
};


class RoadNode{
    public: 
    static std::stack<Direction> DirectionsBack;
    RoadNode(){}
    std::map<u_char,Direction> m_directions;
    std::map<Direction,RoadNode*> m_roadnodes;
    std::set<u_char> RoomToSeek;

    RoadNode* LearnRoad(u_char RoomID,Direction direction){
        RoadNode* ret;
        if(!(m_roadnodes.count(direction)>0)){
            ret = new RoadNode();
            std::pair<Direction,RoadNode*> *temp=new std::pair<Direction,RoadNode*>(direction,ret);
            m_roadnodes.insert(*temp);
        }else{
            ret = m_roadnodes[direction];
        }if(!(m_directions.count(RoomID)>0)){
            std::pair<u_char,Direction> *temp=new std::pair<u_char,Direction>(RoomID,direction);
            ret->RoomToSeek.insert(RoomID);
            m_directions.insert(*temp);
        }
        return ret;
    }

    RoadNode* UpdateRoad(Direction currentDirection){
        for(auto seek : RoomToSeek){
            this->LearnRoad(seek,currentDirection)->RoomToSeek.insert(seek);
        }
        RoomToSeek.clear();
        return this->m_roadnodes[currentDirection];
    }

    RoadNode& MoveRoad(Direction direction){
        if(direction==DirectionsBack.top()){
            DirectionsBack.pop();
        }else{
            switch(direction){
                case Direction::West:DirectionsBack.push(Direction::East);
                case Direction::North:DirectionsBack.push(Direction::South);
                case Direction::South:DirectionsBack.push(Direction::North);
                case Direction::East:DirectionsBack.push(Direction::West);
            }
        }
        return *m_roadnodes[direction];
    }
};

std::stack<Direction> RoadNode::DirectionsBack;

class RaceApplication{
    private:

    Peripheral_Encoder *EncoderR,*EncoderL;
    HardWare::Computer *COM;
    DecoderContainer<char> *Com_Decoder;
    HardWare::TB6612FNG *TB6612FNG_M;
    //HardWare::SSD1306 *SSD1306_M;
    HardWare::HC_Modules::HC_12 *HC_12_M;
    Peripheral_UART *OpenMV_Uart;
    DecoderContainer<char> *OpenMV_Decoder;

    RoadNode *CurrentRoadNode;
    Direction CurrentDirection;
    std::map<u_char,bool> FiguredRoom;


    volatile bool Enable=true;
    float kp=0.01,ki=0,kd=0;
    int offset=0;
    float dt=0.001;
    float previous_error=0;
    float integral = 0;
    float PID(float setpoint,float measuredval){
        auto error = setpoint - measuredval;
        integral = integral + error*dt;
        auto derivative = (error-previous_error)/dt;
        auto output = kp*error+ki*integral+kd*derivative;
        previous_error=error;
        return output;
    }

    public:

    RaceApplication()=default;
    ~RaceApplication()=default;

    void Init(){
        SystemClock::Clock(Clock_Speed::HighSpeed); //配置为高速的系统时钟(目前也只实现了高速).

        COM = new HardWare::Computer(0,115200);     //PA9,PA10
        Debug_BindCallback([&](std::string Info,unsigned int *InterruptCnt){
            COM->Send(Info,InterruptCnt);           //发送Debug信息
        });
        
        Com_Decoder=new DecoderContainer<char>();
        Com_Decoder->Set_Container_Size(20);
        Com_Decoder->End("\r\n",2);
        Com_Decoder->End_Clear(true);
        
        Com_Decoder->End_Decoder([&](char* Data,unsigned int Size){
            if(std::strcmp(Data,Size,"D",1)){
                this->HC_12_M->BluetoothSend("D\r\n");
            }else if(std::strcmp(Data,Size,"E",1)){
                this->HC_12_M->BluetoothSend("E\r\n");
            }
        });
        
        COM->BindCallback([&](char ch){
            Com_Decoder->StreamIn(ch);
        });

        

        Debug_StartDebug("EncoderR");
        EncoderR = new Peripheral_Encoder(0);
        Debug_EndDebug();

        Debug_StartDebug("EncoderL");
        EncoderL = new Peripheral_Encoder(2);
        Debug_EndDebug();

        Debug_StartDebug("TB6612FNG_M");
        TB6612FNG_M = new HardWare::TB6612FNG(0,0,0,1,2,2,2,3,0,1);
        Debug_EndDebug();

        Debug_StartDebug("HC_12_M");
        {
            HC_12_M = new HardWare::HC_Modules::HC_12(2,0,7);

            HC_12_M->BluetoothDecoder.Set_Container_Size(50);
            HC_12_M->BluetoothDecoder.End_Clear(true);
            HC_12_M->BluetoothDecoder.End("\r\n",2);
            HC_12_M->BluetoothDecoder.End_Decoder([&](char* Data,unsigned int Size){
                if(std::strcmp(Data,Size,"D",1)){
                    this->Enable=false;
                }else if(std::strcmp(Data,Size,"E",1)){
                    this->Enable=true;
                    this->TB6612FNG_M->Motor_Speed(0.5,0.5);
                }

            });
            HC_12_M->StartAT();
            HC_12_M->SetFUx(HC::FUx::FU4);
            HC_12_M->SetChannel(64);
            HC_12_M->SetPower(7);
            HC_12_M->EndAT();
        }
        Debug_EndDebug();


        Debug_StartDebug("OpenMV_Uart");
        {
            OpenMV_Uart = new Peripheral_UART(1,115200);
            OpenMV_Decoder = new DecoderContainer<char>();
            OpenMV_Decoder->Set_Container_Size(20);
            OpenMV_Decoder->End("\r\n",2);
            OpenMV_Decoder->End_Clear(true);
            OpenMV_Decoder->End_Decoder([&](char* Data,unsigned int Size){
                if(std::strcmp(Data,Size,"offset",6)){
                    unsigned int ptr=6;
                    this->offset = std::Getint(Data,&ptr);
                    Debug_InterruptSend(std::to_string(this->offset));
                }else if(std::strcmp(Data,Size,"dt",2)){
                    unsigned int ptr=2;
                    this->dt += std::Getint(Data,&ptr)/1000.0;
                    Debug_InterruptSend(std::fto_string(this->dt));
                    if(this->Enable&&this->dt>=0.02){
                        float output = this->PID(0,this->offset);
                        this->TB6612FNG_M->Motor_Speed(0.5-output,0.5+output);
                        Debug_InterruptSend(std::fto_string(output));
                    }
                }else if(std::strcmp(Data,Size,"VL",2)){
                    unsigned int ptr=2;
                    u_char RoomID = std::Getint(Data,&ptr);
                }else if(std::strcmp(Data,Size,"VR",2)){
                    unsigned int ptr=2;
                    u_char RoomID = std::Getint(Data,&ptr);
                }else if(std::strcmp(Data,Size,"missoffset",10)){
                    this->offset=0.0;
                }else if(std::strcmp(Data,Size,"cross",5)){
                    this->Enable=false;
                    Debug_InterruptSend("crossed");
                }
            });

            OpenMV_Uart->BindCallback([&](char chr){
                OpenMV_Decoder->StreamIn(chr);
            });
        }
        Debug_EndDebug();


        CurrentRoadNode = new RoadNode();
        CurrentDirection=Direction::South;
        FiguredRoom.insert({{1,false},{2,false},{3,false},{4,false},{5,false},{6,false},{7,false},{8,false}});
        CurrentRoadNode->RoomToSeek.insert({1,2,3,4,5,6,7,8});
        
        auto tempnode = CurrentRoadNode->UpdateRoad(CurrentDirection);
        tempnode->LearnRoad(1,Direction::East);
        tempnode->LearnRoad(2,Direction::West);
        tempnode->UpdateRoad(CurrentDirection);

    }

    

    void Run(){
        while(1){
        }
    }


    void MoveAhead(){
        this->Enable=false;
        this->TB6612FNG_M->Motor_Speed(0.5,0.5);
        SystemClock::Delay(500000);
        this->Enable=true;
    }

    
};