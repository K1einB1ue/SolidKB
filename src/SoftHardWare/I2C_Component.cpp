#include<SoftHardWare/I2C_Component.h>
#include<SoftHardWare/SystemClock.h>
#include<AbstractDependency/_AbstractHardWare.h>


I2C_Component::I2C_Component(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx):SDA(SDA_GPIOx,SDA_PINx,PIN_Mode::FastPullUp),SCL(SCL_GPIOx,SCL_PINx,PIN_Mode::FastPullUp){
    SDA.F_WriteMode();
    SCL.F_WriteMode();
    SDA=1;
    SCL=1;
}


void    I2C_Component::Start(){
    SDA.F_WriteMode();
    SDA=1;SystemClock::Delay(1);  
    SCL=1;SystemClock::Delay(1);
    SDA=0;SystemClock::Delay(1);
    SCL=0;SystemClock::Delay(1);
}

void    I2C_Component::Stop(){
    SDA.F_WriteMode();
    SCL=1;SystemClock::Delay(1);   
    SDA=0;SystemClock::Delay(1); 
    SDA=1;SystemClock::Delay(1);  
}

void    I2C_Component::Send_Byte(u_char txd){ 
	SDA.F_WriteMode();     
    for(u_char t=0;t<8;t++) {  
        SCL=0;SystemClock::Delay(1);
        if(txd&0x80){
            SDA=1;SystemClock::Delay(1);
        }else{
            SDA=0;SystemClock::Delay(1);
        }     
		SCL=1;SystemClock::Delay(1);      
		SCL=0;SystemClock::Delay(1);
        txd<<=1;
    }	
}

u_char  I2C_Component::Read_Byte(bool ack){
    u_char receive=0;
	SDA.F_ReadMode();
    for(u_char i=0;i<8;i++) {
        SCL=0; 
        SystemClock::Delay(2);
		SCL=1;
        receive<<=1;
        if(SDA)receive++;   
		SystemClock::Delay(1);
    }					 
    if (!ack)
        NAck();
    else
        Ack();
    return receive;
}

bool    I2C_Component::Wait_Ack(){
    u_char ucErrTime=0;
	SDA.F_ReadMode(); 
	SDA=1;SystemClock::Delay(1);	   
	SCL=1;SystemClock::Delay(1);
	while(SDA) {
		ucErrTime++;
		if(ucErrTime>250)
		{
			Stop();
			return true;
		}
	}
	SCL=0;//时钟输出0 	   
	return false;
}




void    I2C_Component::Ack(){  
    SCL=0;
	SDA.F_WriteMode();  
	SDA=0;
	SystemClock::Delay(2);
	SCL=1;
	SystemClock::Delay(2);
	SCL=0;
}

void    I2C_Component::NAck(){
    SCL=0;
	SDA.F_WriteMode();  
	SDA=1;
	SystemClock::Delay(2);
	SCL=1;
	SystemClock::Delay(2);
	SCL=0;
}





void    I2C_Component::Fast_Ack(){
    SCL=1;SystemClock::Delay(1);
    SCL=0;SystemClock::Delay(1);
}

I2C_Component::~I2C_Component(){}
