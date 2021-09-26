#include<Kernel/HardWare/WireProtocol/SPI_Component.h>
#include<Kernel/HardWare/SystemClock.h>
//https://www.cnblogs.com/chenshuyi/p/3605427.html

#if __Enable_PIN
     
SPI_Component::SPI_Component(SPI_PIN_Pack):
    MOSI(MOSI_GPIOx,MOSI_PINx,PIN_Mode::FastPullUp),    //上拉是不必要的,上拉可以信号更稳定,驱动能力加强.
    MISO(MISO_GPIOx,MISO_PINx,PIN_Mode::FastPullUp),    //上拉是不必要的,上拉可以信号更稳定,驱动能力加强.
    SCK(SCK_GPIOx,SCK_PINx,PIN_Mode::FastPullUp),       //上拉是不必要的,上拉可以信号更稳定,驱动能力加强.
    CS(CS_GPIOx,CS_PINx,PIN_Mode::FastPullUp){          //最好上拉,防止误操作.
    MOSI.F_WriteMode();
    MISO.F_ReadMode();
    SCK.F_WriteMode();
    CS.F_WriteMode();
    MOSI=0;
    CS=1;
}

SPI_Component::SPI_Component(SPI_PIN_Pack,bool __NoNeedPullUp__): 
    MOSI(MOSI_GPIOx,MOSI_PINx,PIN_Mode::Fast),          //上拉是不必要的,上拉可以信号更稳定,驱动能力加强.
    MISO(MISO_GPIOx,MISO_PINx,PIN_Mode::Fast),          //上拉是不必要的,上拉可以信号更稳定,驱动能力加强.
    SCK(SCK_GPIOx,SCK_PINx,PIN_Mode::Fast),             //上拉是不必要的,上拉可以信号更稳定,驱动能力加强.
    CS(CS_GPIOx,CS_PINx,PIN_Mode::FastPullUp){          //最好上拉,防止误操作.
    MOSI.F_WriteMode();
    MISO.F_ReadMode();
    SCK.F_WriteMode();
    CS.F_WriteMode();
    MOSI=0;
    CS=1;
}
    
SPI_Component::~SPI_Component(){}

void      SPI_Component::Fast_SPI_Start_Mode0(){
    SCK = 0;
    CS = CS_Acitve;
}

void      SPI_Component::Fast_SPI_Start_Mode1(){
    SCK = 0;
    CS = CS_Acitve;
}

void      SPI_Component::Fast_SPI_Start_Mode2(){
    SCK = 1;
    CS = CS_Acitve;
}

void      SPI_Component::Fast_SPI_Start_Mode3(){
    SCK = 1;
    CS = CS_Acitve;
}

void      SPI_Component::Fast_SPI_W_Mode0(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 0;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 1;
    }
    SCK = 0;
    MOSI= 0;
}

void      SPI_Component::Fast_SPI_W_Mode1(u_char txd){
    SCK = 0;
    for(u_char i=0;i<7;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
    MOSI=0;
}

void      SPI_Component::Fast_SPI_W_Mode2(u_char txd){
    SCK=0;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
    MOSI=0;
}

void      SPI_Component::Fast_SPI_W_Mode3(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
    SCK =1;
    MOSI=0;
}

u_char    SPI_Component::Fast_SPI_R_Mode0(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 0;
    }
    return rxd;
}

u_char    SPI_Component::Fast_SPI_R_Mode1(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 0;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 1;
    }
    return rxd;
}

u_char    SPI_Component::Fast_SPI_R_Mode2(){
    u_char rxd=0;
    SCK = 1;
    for(u_char i=0;i<8;i++){ 
	    SCK = 0;
	    rxd <<= 1;
	    SCK = 1;
        if(MISO) rxd++;
    }
	return (rxd);
}

u_char    SPI_Component::Fast_SPI_R_Mode3(){
    u_char rxd=0;
    SCK = 0;
    for(u_char i=0;i<7;i++){
	    SCK = 1;
	    rxd <<= 1;
	    if(MISO) rxd++;
	    SCK = 0;
    }
    SCK = 1;
    rxd <<= 1;
    if(MISO) rxd++;
	return (rxd);
}

void      SPI_Component::End(){
    CS = !CS_Acitve;
}

void      SPI_Component::__SPI_Mode(bool CPOL,bool CPHA){
    if(!CPOL){      
        if(!CPHA){
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Mode0(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Mode0();};
            this->Start=[&](){this->Fast_SPI_Start_Mode0();};
        }
        else{
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Mode1(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Mode1();};
            this->Start=[&](){this->Fast_SPI_Start_Mode1();};
        }
    }else{
        if(!CPHA){
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Mode2(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Mode2();};
            this->Start=[&](){this->Fast_SPI_Start_Mode2();};
        }
        else{
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Mode3(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Mode3();};
            this->Start=[&](){this->Fast_SPI_Start_Mode3();};
        }      
    }
}

void      SPI_Component::__SPI_CS_Active(bool CS){
    this->CS_Acitve=CS;
}

u_char    SPI_Component::Read_Reg(u_char reg){
    this->Start();
    this->Send_Byte(reg|BIT7);
    u_char temp = this->Read_Byte();
    this->End();
    return temp;
}

void        SPI_Component::Read_Reg(u_char reg,u_char count,u_char *dest){
    u_char ptr=0;
    this->Start();
    this->Send_Byte(reg|BIT7);
    while(ptr<count){
        dest[ptr]=this->Read_Byte();
        ptr++;
    }
    this->End();
}

void        SPI_Component::Send_Reg(u_char reg,u_char txd){
    this->Start();
    this->Send_Byte(reg);
    this->Send_Byte(txd);
    this->End();
}

void        SPI_Component::Send_Reg(u_char reg,u_char count,u_char *sour){
    u_char ptr=0;
    this->Start();
    this->Send_Byte(reg);
    while(ptr<count){
        this->Send_Byte(sour[ptr]);
        ptr++;
    }
    this->End();
}
#endif