#include"./SPI_Component.h"
#include"../Peripheral/SystemClock.h"
//https://www.cnblogs.com/chenshuyi/p/3605427.html
//TODO:如果频率过高会产生SPI无法响应部分设备的问题!如ADS1256需要50ns的时间
#if __Enable_PIN
     


SPI_Component::SPI_Component(SPI_PIN_Pack,SPI_type type,const SPI_Detail &detail): 
    MOSI(),
    MISO(),
    SCK(SCK_GPIOx,SCK_PINx,PIN_Mode::Fast,"SCK"), 
    CS(CS_GPIOx,CS_PINx,PIN_Mode::FastPullUp,"CS"){
    CS.F_WriteMode();
    SCK.F_WriteMode();
    switch (type){
    case SPI_type::I:
        MISO.Construct(MISO_GPIOx,MISO_PINx,PIN_Mode::Fast,"MISO");
        MISO.F_ReadMode();
        break;
    case SPI_type::O:
        MOSI.Construct(MOSI_GPIOx,MOSI_PINx,PIN_Mode::Fast,"MOSI");
        MOSI.F_WriteMode();
        MOSI=0;
        break;
    case SPI_type::IO:
        MISO.Construct(MISO_GPIOx,MISO_PINx,PIN_Mode::Fast,"MISO");
        MISO.F_ReadMode();
        MOSI.Construct(MOSI_GPIOx,MOSI_PINx,PIN_Mode::Fast,"MOSI");
        MOSI.F_WriteMode();
        MOSI=0;
    default:
        break;
    }
    __SPI_Mode(detail.CPOL,detail.CPHA);
    __SPI_CS_Active(detail.CS_Active);
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
}//complete

void      SPI_Component::Fast_SPI_W_Mode1(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
}//complete

void      SPI_Component::Fast_SPI_W_Mode2(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
    SCK = 1;
}//complete

void      SPI_Component::Fast_SPI_W_Mode3(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 0;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 1;
    }
}//complete

u_char    SPI_Component::Fast_SPI_R_Mode0(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(MISO) rxd++;
        rxd <<= 1;
        SCK = 0;
    }
    return rxd;
}//complete

u_char    SPI_Component::Fast_SPI_R_Mode1(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(MISO) rxd++;
        rxd <<= 1;
        SCK = 0;
    }
    return rxd;
}//complete

u_char    SPI_Component::Fast_SPI_R_Mode2(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){ 
	    SCK = 0;
        if(MISO) rxd++;
	    rxd <<= 1;
	    SCK = 1;
    }
	return (rxd);
}//complete

u_char    SPI_Component::Fast_SPI_R_Mode3(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 0;
	    if(MISO) rxd++;
	    rxd <<= 1;
	    SCK = 1;
    }
	return (rxd);
}//complete

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
        this->SCK=0;
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
        this->SCK=1;     
    }
}

void      SPI_Component::__SPI_CS_Active(bool CS){
    this->CS_Acitve=CS;
    this->CS=!this->CS_Acitve;
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

void        SPI_Component::Send_Len(u_char len,u_char *buf){
    u_char ptr=0;
    this->Start();
    while(ptr<len){
        this->Send_Byte(buf[ptr]);
        ptr++;
    }
    this->End();
}

void        SPI_Component::Send_Single(u_char txd){
    this->Start();
    this->Send_Byte(txd);
    this->End();
}
#endif