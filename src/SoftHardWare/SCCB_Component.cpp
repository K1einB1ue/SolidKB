#include<SoftHardWare/SCCB_Component.h>
#include<SoftHardWare/SystemClock.h>
#include<AbstractDependency/_AbstractHardWare.h>


SCCB_Component::SCCB_Component(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx):SCL(SCL_GPIOx,SCL_PINx,PIN_Mode::Fast),SDA(SDA_GPIOx,SDA_PINx,PIN_Mode::Fast){
    SDA=1;
    SCL=1;
    SDA.F_WriteMode();
}

SCCB_Component::~SCCB_Component(){}

void    SCCB_Component::Start(){
    SDA=1;
    SCL=1;
    SystemClock::Delay(50);
    SDA=0;
    SystemClock::Delay(50);
    SCL=0;
}
void    SCCB_Component::Stop(){
    SDA=0;
    SystemClock::Delay(50);
    SCL=1;
    SystemClock::Delay(50);
    SDA=1;
    SystemClock::Delay(50);
}

bool    SCCB_Component::Send_Byte(u_char txd){	 
    bool res=false;
	for(unsigned int j=0;j<8;j++) //循环8次发送数据
	{
		if(txd&0x80)SDA=1;	
		else SDA=0;
		txd<<=1;
		SystemClock::Delay(50);
		SCL=1;	
		SystemClock::Delay(50);
		SCL=0;		   
	}			 
	SDA.F_ReadMode();		//设置SDA为输入 
	SystemClock::Delay(50);
	SCL=1;			//接收第九位,以判断是否发送成功
	SystemClock::Delay(50);
	if(SDA)res=true;  //SDA=1发送失败，返回1
    else res=false;
	SCL=0;		 
	SDA.F_WriteMode();		//设置SDA为输出    
}

u_char  SCCB_Component::Read_Byte(){
    u_char temp=0,j;    
	SDA.F_ReadMode();		//设置SDA为输入  
	for(j=8;j>0;j--) 	//循环8次接收数据
	{		     	  
		SystemClock::Delay(50);
		SCL=1;
		temp=temp<<1;
		if(SDA)temp++;   
		SystemClock::Delay(50);
		SCL=0;
	}	
	SDA.F_WriteMode();		//设置SDA为输出    
	return temp;
}

void    SCCB_Component::NAck(){
    SystemClock::Delay(50);
	SDA=1;	
	SCL=1;	
	SystemClock::Delay(50);
	SCL=0;	
	SystemClock::Delay(50);
	SDA=0;	
	SystemClock::Delay(50);
}

bool    SCCB_Component::Send_Reg(u_char add,u_char reg,u_char txd){
    bool res=false;
	this->Start();					//启动SCCB传输
	if(this->Send_Byte(add))res=true;	//写器件ID	  
  	if(this->Send_Byte(reg))res=true;		//写寄存器地址	  
  	if(this->Send_Byte(txd))res=true; 	//写数据	 
  	this->Stop();	  
  	return	res;
}

u_char  SCCB_Component::Read_Reg(u_char add,u_char reg){
    u_char val=0;
	Start(); 				//启动SCCB传输
	Send_Byte(add);		//写器件ID	   
  	Send_Byte(reg);			//写寄存器地址	  	  
	Stop();      
	//设置寄存器地址后，才是读
	Start();
	Send_Byte(add|0X01);	//发送读命令	  
  	val=Read_Byte();		 	//读取数据
  	NAck();
  	Stop();
  	return val;
}