#include<Kernel/HardWare/WireProtocol/SPI_Component.h>
//https://www.cnblogs.com/chenshuyi/p/3605427.html

#if __Enable_PIN
     
SPI_Component::SPI_Component(
    uint32_t MOSI_GPIOx,uint32_t MOSI_PINx,
    uint32_t MISO_GPIOx,uint32_t MISO_PINx,
    uint32_t SCK_GPIOx,uint32_t SCK_PINx,
    uint32_t CS_GPIOx,uint32_t CS_PINx):
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
    
SPI_Component::~SPI_Component(){}

u_char    SPI_Component::SOFT_SPI_RW_Mode0(u_char txd){
    u_char rxd=0;
    SCK = 0;
    CS = CS_Acitve;
    for(u_char i=0;i<8;i++){
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 1;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 0;
    }
    CS = !CS_Acitve;
    return (rxd);
}

u_char    SPI_Component::SOFT_SPI_RW_Mode1(u_char txd){
    u_char rxd=0;
    SCK = 0;
    CS = CS_Acitve;
    SCK = 1;
    for(u_char i=0;i<8;i++){
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 1;
    }
    CS = !CS_Acitve;
    return (rxd);
}

u_char    SPI_Component::SOFT_SPI_RW_Mode2(u_char txd){
    u_char rxd=0;
    SCK = 1;
    CS = CS_Acitve;
    for(u_char i=0;i<8;i++){ 
	    if(txd&0x80)  MOSI = 1;
	    else MOSI = 0;
	    txd <<= 1;
	    SCK = 0;
	    rxd <<= 1;
	    if(MISO) rxd++;
	    SCK = 1;
    }
    CS = !CS_Acitve;
	return (rxd);
}

u_char    SPI_Component::SOFT_SPI_RW_Mode3(u_char txd){
    u_char rxd=0;
    SCK = 1;
    CS = CS_Acitve;
    SCK = 0;
    for(u_char i=0;i<8;i++){
	    if(txd&0x80)  MOSI = 1;
	    else MOSI = 0;
	    txd <<= 1;
	    SCK = 1;
	    rxd <<= 1;
	    if(MISO) rxd++;
	    SCK = 0;
    }
    CS = !CS_Acitve;
	return (rxd);
}

void      SPI_Component::SOFT_SPI_W_Mode0(u_char txd){
    SCK = 0;
    CS = CS_Acitve;
    for(u_char i=0;i<8;i++){
        SCK = 0;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 1;
    }
    CS = !CS_Acitve;
}

void      SPI_Component::SOFT_SPI_W_Mode1(u_char txd){
    SCK = 0;
    CS = CS_Acitve;
    SCK = 1;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
    CS = !CS_Acitve;
}

void      SPI_Component::SOFT_SPI_W_Mode2(u_char txd){
    SCK = 1;
    CS = CS_Acitve;
    for(u_char i=0;i<8;i++){
        SCK = 1;
	    if(txd&0x80)  MOSI = 1;
	    else MOSI = 0;
	    txd <<= 1;
	    SCK = 0;  
    }
    CS = !CS_Acitve; 
}

void      SPI_Component::SOFT_SPI_W_Mode3(u_char txd){
    SCK = 1;
    CS = CS_Acitve;
    SCK = 0;
    for(u_char i=0;i<8;i++){
        SCK = 0;
	    if(txd&0x80)  MOSI = 1;
	    else MOSI = 0;
	    txd <<= 1;
	    SCK = 1;
    }
    CS = !CS_Acitve;
}

u_char    SPI_Component::SOFT_SPI_R_Mode0(){
    u_char rxd=0;
    SCK = 0;
    CS = CS_Acitve;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 0;
    }
    CS = !CS_Acitve;
    return (rxd);
}

u_char    SPI_Component::SOFT_SPI_R_Mode1(){
    u_char rxd=0;
    SCK = 0;
    CS = CS_Acitve;
    SCK = 1;
    for(u_char i=0;i<8;i++){
        SCK = 0;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 1;
    }
    CS = !CS_Acitve;
    return (rxd);
}

u_char    SPI_Component::SOFT_SPI_R_Mode2(){
    u_char rxd=0;
    SCK = 1;
    CS = CS_Acitve;
    for(u_char i=0;i<8;i++){ 
	    SCK = 0;
	    rxd <<= 1;
	    if(MISO) rxd++;
	    SCK = 1;
    }
    CS = !CS_Acitve;
	return (rxd);
}

u_char    SPI_Component::SOFT_SPI_R_Mode3(){
    u_char rxd=0;
    SCK = 1;
    CS = CS_Acitve;
    SCK = 0;
    for(u_char i=0;i<8;i++){
	    SCK = 1;
	    rxd <<= 1;
	    if(MISO) rxd++;
	    SCK = 0;
    }
    CS = !CS_Acitve;
	return (rxd);
}

void      SPI_Component::Fast_SPI_Start_Mode0(){
    SCK = 0;
    CS = CS_Acitve;
}

void      SPI_Component::Fast_SPI_Start_Mode1(){
    SCK = 0;
    CS = CS_Acitve;
    SCK = 1;
}

void      SPI_Component::Fast_SPI_Start_Mode2(){
    SCK = 1;
    CS = CS_Acitve;
}

void      SPI_Component::Fast_SPI_Start_Mode3(){
    SCK = 1;
    CS = CS_Acitve;
    SCK = 0;
}

void      SPI_Component::Fast_SPI_W_Type0(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 0;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 1;
    }
}

void      SPI_Component::Fast_SPI_W_Type1(u_char txd){
    for(u_char i=0;i<8;i++){
        SCK = 1;
        if(txd&0x80) MOSI = 1;
        else MOSI = 0;
        txd <<= 1;
        SCK = 0;
    }
}

u_char    SPI_Component::Fast_SPI_R_Type0(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 1;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 0;
    }
    return rxd;
}

u_char    SPI_Component::Fast_SPI_R_Type1(){
    u_char rxd=0;
    for(u_char i=0;i<8;i++){
        SCK = 0;
        rxd <<= 1;
        if(MISO) rxd++;
        SCK = 1;
    }
    return rxd;
}

void      SPI_Component::End(){
    CS = !CS_Acitve;
}

void      SPI_Component::__SPI_Mode(bool CPOL,bool CPHA){
    if(!CPOL){      
        if(!CPHA){
            this->SOFT_SPI_R_Func=[&](){return this->SOFT_SPI_R_Mode0();};
            this->SOFT_SPI_W_Func=[&](u_char txd){this->SOFT_SPI_W_Mode0(txd);};
            this->SOFT_SPI_RW_Func=[&](u_char txd){return this->SOFT_SPI_RW_Mode0(txd);};
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Type0(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Type0();};
            this->Start=[&](){this->Fast_SPI_Start_Mode0();};
        }
        else{
            this->SOFT_SPI_R_Func=[&](){return this->SOFT_SPI_R_Mode1();};
            this->SOFT_SPI_W_Func=[&](u_char txd){this->SOFT_SPI_W_Mode1(txd);};
            this->SOFT_SPI_RW_Func=[&](u_char txd){return this->SOFT_SPI_RW_Mode1(txd);};
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Type1(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Type1();};
            this->Start=[&](){this->Fast_SPI_Start_Mode1();};
        }
    }else{
        if(!CPHA){
            this->SOFT_SPI_R_Func=[&](){return this->SOFT_SPI_R_Mode2();};
            this->SOFT_SPI_W_Func=[&](u_char txd){this->SOFT_SPI_W_Mode2(txd);};
            this->SOFT_SPI_RW_Func=[&](u_char txd){return this->SOFT_SPI_RW_Mode2(txd);};
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Type1(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Type1();};
            this->Start=[&](){this->Fast_SPI_Start_Mode2();};
        }
        else{
            this->SOFT_SPI_R_Func=[&](){return this->SOFT_SPI_R_Mode3();};
            this->SOFT_SPI_W_Func=[&](u_char txd){this->SOFT_SPI_W_Mode3(txd);};
            this->SOFT_SPI_RW_Func=[&](u_char txd){return this->SOFT_SPI_RW_Mode3(txd);};
            this->Send_Byte=[&](u_char txd){this->Fast_SPI_W_Type0(txd);};
            this->Read_Byte=[&](){return this->Fast_SPI_R_Type0();};
            this->Start=[&](){this->Fast_SPI_Start_Mode3();};
        }      
    }
}

void      SPI_Component::__SPI_CS_Active(bool CS){
    this->CS_Acitve=CS;
}

u_char    SPI_Component::SOFT_SPI_RW(u_char txd){
    if(this->SOFT_SPI_RW_Func){
        return this->SOFT_SPI_RW_Func(txd);
    }else{
        Debug_Warning("SPI_Mode Not define! Fallback to mode0!");
        __SPI_Mode(0,0);
        return this->SOFT_SPI_RW_Func(txd);
    }
}

void      SPI_Component::SOFT_SPI_W(u_char txd){
    if(this->SOFT_SPI_W_Func){
        this->SOFT_SPI_W_Func(txd);
    }else{
        Debug_Warning("SPI_Mode Not define! Fallback to mode0!");
        __SPI_Mode(0,0);
        this->SOFT_SPI_W_Func(txd);
    }
}

u_char    SPI_Component::SOFT_SPI_R(){
    if(this->SOFT_SPI_R_Func){
        return this->SOFT_SPI_R_Func();
    }else{
        Debug_Warning("SPI_Mode Not define! Fallback to mode0!");
        __SPI_Mode(0,0);
        return this->SOFT_SPI_R_Func();
    }
}

u_char    SPI_Component::Read_Reg(u_char reg){
    this->SOFT_SPI_W(reg);
    return this->SOFT_SPI_R();
}

u_char    SPI_Component::Read_Reg(u_char reg,u_char spare){
    this->SOFT_SPI_RW(reg);
    return this->SOFT_SPI_RW(spare);
}

void      SPI_Component::Send_Reg(u_char reg,u_char txd){
    this->SOFT_SPI_RW(reg);
    this->SOFT_SPI_RW(txd);
}


void     SPI_Component::PreRead_Reg(u_char reg){
    this->SOFT_SPI_W(reg);
}

u_char   SPI_Component::ConRead_Reg(u_char reg){
    return this->SOFT_SPI_RW(reg);
}

u_char   SPI_Component::EndRead_Reg(){
    return this->SOFT_SPI_R();
}

#endif