#include"./OV7725.h"

#if __Enable_DCMI &&__Enable_PIN &&__Enable_SystemClock

#define OV7725_ADDR        		0X42
#define OV7725_MID				0X7FA2    
#define OV7725_PID				0X7721



/* OV7725寄存器宏定义 */
#define GAIN      0x00
#define BLUE      0x01
#define RED       0x02
#define RED       0x02
#define GREEN     0x03
#define BAVG      0x05
#define GAVG      0x06
#define RAVG      0x07
#define AECH      0x08
#define COM2      0x09
#define PID       0x0A
#define VER       0x0B
#define COM3      0x0C
#define COM4      0x0D
#define COM5      0x0E
#define COM6      0x0F
#define AEC       0x10
#define CLKRC     0x11
#define COM7      0x12
#define COM8      0x13
#define COM9      0x14
#define COM10     0x15
#define REG16     0x16
#define HSTART    0x17
#define HSIZE     0x18
#define VSTRT     0x19
#define VSIZE     0x1A
#define PSHFT     0x1B
#define MIDH      0x1C
#define MIDL      0x1D
#define LAEC      0x1F
#define COM11     0x20
#define BDBase    0x22
#define BDMStep   0x23
#define AEW       0x24
#define AEB       0x25
#define VPT       0x26
#define REG28     0x28
#define HOutSize  0x29
#define EXHCH     0x2A
#define EXHCL     0x2B
#define VOutSize  0x2C
#define ADVFL     0x2D
#define ADVFH     0x2E
#define YAVE      0x2F
#define LumHTh    0x30
#define LumLTh    0x31
#define HREF      0x32
#define DM_LNL    0x33
#define DM_LNH    0x34
#define ADoff_B   0x35
#define ADoff_R   0x36
#define ADoff_Gb  0x37
#define ADoff_Gr  0x38
#define Off_B     0x39
#define Off_R     0x3A
#define Off_Gb    0x3B
#define Off_Gr    0x3C
#define COM12     0x3D
#define COM13     0x3E
#define COM14     0x3F
#define COM16     0x41
#define TGT_B     0x42
#define TGT_R     0x43
#define TGT_Gb    0x44
#define TGT_Gr    0x45
#define LC_CTR    0x46
#define LC_XC     0x47
#define LC_YC     0x48
#define LC_COEF   0x49
#define LC_RADI   0x4A
#define LC_COEFB  0x4B 
#define LC_COEFR  0x4C
#define FixGain   0x4D
#define AREF1     0x4F
#define AREF6     0x54
#define UFix      0x60
#define VFix      0x61
#define AWBb_blk  0x62
#define AWB_Ctrl0 0x63
#define DSP_Ctrl1 0x64
#define DSP_Ctrl2 0x65
#define DSP_Ctrl3 0x66
#define DSP_Ctrl4 0x67
#define AWB_bias  0x68
#define AWBCtrl1  0x69
#define AWBCtrl2  0x6A
#define AWBCtrl3  0x6B
#define AWBCtrl4  0x6C
#define AWBCtrl5  0x6D
#define AWBCtrl6  0x6E
#define AWBCtrl7  0x6F
#define AWBCtrl8  0x70
#define AWBCtrl9  0x71
#define AWBCtrl10 0x72
#define AWBCtrl11 0x73
#define AWBCtrl12 0x74
#define AWBCtrl13 0x75
#define AWBCtrl14 0x76
#define AWBCtrl15 0x77
#define AWBCtrl16 0x78
#define AWBCtrl17 0x79
#define AWBCtrl18 0x7A
#define AWBCtrl19 0x7B
#define AWBCtrl20 0x7C
#define AWBCtrl21 0x7D 
#define GAM1      0x7E
#define GAM2      0x7F
#define GAM3      0x80
#define GAM4      0x81
#define GAM5      0x82
#define GAM6      0x83
#define GAM7      0x84
#define GAM8      0x85
#define GAM9      0x86
#define GAM10     0x87
#define GAM11     0x88
#define GAM12     0x89
#define GAM13     0x8A
#define GAM14     0x8B
#define GAM15     0x8C
#define SLOP      0x8D
#define DNSTh     0x8E
#define EDGE0     0x8F
#define EDGE1     0x90
#define DNSOff    0x91
#define EDGE2     0x92
#define EDGE3     0x93
#define MTX1      0x94
#define MTX2      0x95
#define MTX3      0x96
#define MTX4      0x97
#define MTX5      0x98
#define MTX6      0x99
#define MTX_Ctrl  0x9A
#define BRIGHT    0x9B
#define CNST      0x9C
#define UVADJ0    0x9E
#define UVADJ1    0x9F
#define SCAL0     0xA0
#define SCAL1     0xA1
#define SCAL2     0xA2
#define SDE       0xA6
#define USAT      0xA7
#define VSAT      0xA8
#define HUECOS    0xA9
#define HUESIN    0xAA
#define SIGN      0xAB
#define DSPAuto   0xAC

//初始化寄存器序列及其对应的值
const u_char ov7725_init_reg_tb1[][2]= 
{   
	/*输出窗口设置*/
	//Bit[7]:保留 Bit[6]:外置时钟启用 Bit[5:0]:内部时钟分频因数
	{CLKRC,     0x00}, 
	//Bit[7]:SCCB寄存器重置(0:不变|1:重置)
	//Bit[6]:分辨率选择(0:VGA|1:QVGA) 
	//Bit[5]:BT.656协议启用 
	//Bit[4]:传感器RAW
	//Bit[3:2]RGB输出格式
	//|00:GBR4:2:2
	//|01:RGB565
	//|10:RGB555
	//|11:RGB444
	//Bit[1:0]输出格式控制
	//|00:YUV
	//|01:处理后的RAW
	//|10:RGB
	//|11:RAW
	{COM7,      0x06}, //VGA RGB565
	//设置水平起始位置
	{HSTART,    0x3f},
	//设置水平尺寸
	{HSIZE,     0x50},
	//设置垂直起始位置
	{VSTRT,     0x03},
	//设置垂直尺寸
	{VSIZE,     0x78},

	//图片开始和尺寸控制(翻译不来)
	{HREF,      0x00},

	//水平输出大小
	{HOutSize,  0x50}, //输出尺寸
	//垂直输出大小
	{VOutSize,  0x78}, //输出尺寸
	
	/*DSP control*/
	//B通道目标值
	{TGT_B,     0x7f},
	//通道固定增益
	//Bit[7:6]:Gb通道固定增益
	//Bit[5:4]:Gr通道固定增益
	//Bit[3:2]:B通道固定增益
	//Bit[1:0]:R通道固定增益
	{FixGain,   0x09},
	//Bit[7]: AWB gain enable
	//Bit[6]: AWB calculate enable
	//Bit[5]: Reserved
	//Bit[4:0]: WBC threshold 2
	{AWB_Ctrl0, 0xe0},
	//Bit[7]: FIFO enable/disable selection
	//Bit[6]: UV adjust function ON/OFF selection
	//Bit[5]: SDE enable
	//Bit[4]: Color matrix ON/OFF selection
	//Bit[3]: Interpolation ON/OFF selection
	//Bit[2]: Gamma function ON/OFF selection
	//Bit[1]: Black defect auto correction ON/OFF
	//Bit[0]: White defect auto correction ON/OFF
	{DSP_Ctrl1, 0xff},
	//Bit[7:4]: Reserved
	//Bit[3]: Vertical DCW enable
	//Bit[2]: Horizontal DCW enable
	//Bit[1]: Vertical zoom out enable
	//Bit[0]: Horizontal zoom out enable
	{DSP_Ctrl2, 0x00},
	//Bit[7]: UV output sequence option
	//Bit[6]: Reserved
	//Bit[5]: DSP color bar ON/OFF selection
	//Bit[4]: Reserved
	//Bit[3]: FIFO power down ON/OFF selection
	//Bit[2]: Scaling module power down control 1
	//Bit[1]: Scaling module power down control 2
	//Bit[0]: Interpolation module power down control
	{DSP_Ctrl3,	0x00},
	//Bit[7:3]: Reserved
	//Bit[2]: AEC selection
	//|0: Before gamma
	//|1: After gamma
	//Bit[1:0]: Output selection
	//|00: YUV or RGB
	//|01: YUV or RGB
	//|10: RAW8
	//|11: RAW10
	{DSP_Ctrl4, 0x00},

	/*AGC AEC AWB*/
	{COM8,		0xf0},
	{COM4,		0x81}, /*Pll AEC CONFIG*/
	{COM6,		0xc5},
	{COM9,		0x11},
	{BDBase,	0x7F},
	{BDMStep,	0x03},
	{AEW,		0x40},
	{AEB,		0x30},
	{VPT,		0xa1},
	{EXHCL,		0x9e},
	{AWBCtrl3,  0xaa},
	{COM8,		0xff},
	
	/*matrix shapness brightness contrast*/
	{EDGE1,		0x08},
	{DNSOff,	0x01},
	{EDGE2,		0x03},
	{EDGE3,		0x00},
	{MTX1,		0xb0},
	{MTX2,		0x9d},
	{MTX3,		0x13},
	{MTX4,		0x16},
	{MTX5,		0x7b},
	{MTX6,		0x91},
	{MTX_Ctrl,  0x1e},
	{BRIGHT,	0x08},
	{CNST,		0x20},
	{UVADJ0,	0x81},
	{SDE, 		0X06},
	{USAT,		0x65},
	{VSAT,		0x65},
	{HUECOS,	0X80},
	{HUESIN, 	0X80},
	
    /*GAMMA config*/
	{GAM1,		0x0c},
	{GAM2,		0x16},
	{GAM3,		0x2a},
	{GAM4,		0x4e},
	{GAM5,		0x61},
	{GAM6,		0x6f},
	{GAM7,		0x7b},
	{GAM8,		0x86},
	{GAM9,		0x8e},
	{GAM10,		0x97},
	{GAM11,		0xa4},
	{GAM12,		0xaf},
	{GAM13,		0xc5},
	{GAM14,		0xd7},
	{GAM15,		0xe8},
	{SLOP,		0x20},

	
	{COM3,		0x40},  /*Horizontal mirror image*/
					    //注：datasheet默认0x10,即改变YUV为UVY格式。但是摄像头不是芯片而是模组时，
					    //要将0X10中的1变成0，即设置YUV格式。
	/*night mode auto frame rate control*/ 
	//{COM5,		0xf5},	/*在夜视环境下，自动降低帧率，保证低照度画面质量*/
	{COM5,		0x31},	/*夜视环境帧率不变*/

	//Bit[7]: Output negative data
	//Bit[6]: HREF changes to HSYNC
	//Bit[5]: PCLK output option
	//|0: Free running PCLK
	//|1: PCLK does not toggle during horizontal blank
	//Bit[4]: PCLK reverse
	//Bit[3]: HREF reverse
	//Bit[2]: VSYNC option
	//|0: VSYNC changes on falling edge of PCLK
	//|1: VSYNC changes on rising edge of PCLK
	//Bit[1]: VSYNC negative
	//Bit[0]: Output data range selection
	//|0: Full range
	//|1: Data from [10] to [F0] (8 MSBs)
	//{COM10,		0x02},  //VSYNC 高电平有效，为了兼容OV2640 DCMI的配置
	{COM10,		0x00},
	{COM2,      0x01},  //设置输出驱动能力最高
};



namespace HardWare{


bool OV7725::Send_Reg_WithDefaultAdress(u_char reg,u_char txd){
    return this->Send_Reg(OV7725_ADDR,reg,txd);
}

u_char OV7725::Read_Reg_WithDefaultAdress(u_char reg){
    return this->Read_Reg(OV7725_ADDR,reg);
}

OV7725::OV7725(
	uint32_t SDA_GPIOx,uint32_t SDA_PINx,
	uint32_t SCL_GPIOx,uint32_t SCL_PINx,
	uint32_t SGM_GPIOx,uint32_t SGM_PINx,
	uint32_t RST_GPIOx,uint32_t RST_PINx,
	uint32_t DCMIx,void* Dst,uint32_t Length):
	SCCB_Component(SDA_GPIOx,SDA_PINx,SCL_GPIOx,SCL_PINx),
	Peripheral_DCMI(DCMIx,Dst,Length),
	SGM(SGM_GPIOx,SGM_PINx,PIN_Mode::FastPullUp,"SGM"),
	RST(RST_GPIOx,RST_PINx,PIN_Mode::FastPullUp,"RST"){
	Debug_StartBlock("Init");	
	bool flag=false;
	SGM.F_WriteMode();
	RST.F_WriteMode();

	SGM=1;																					//拉高，使用OV7725模块板载12M晶振，拉低使用单片机PA8输出时钟
	SystemClock::Delay(100000);	

	RST=0;																					//复位OV7725
	SystemClock::Delay(100000);

	RST=1;																					//结束复位
	SystemClock::Delay(100000);

 	if(Send_Reg_WithDefaultAdress(COM7,0x80)){												//软复位OV7725
		Debug_Warning("RST Error");
		flag=true;
	}else{
		Debug_Info("RST Correct");
	}													
	SystemClock::Delay(100000); 

	uint16_t reg;
	reg	 =(Read_Reg_WithDefaultAdress(MIDH)<<8);
	reg	|=Read_Reg_WithDefaultAdress(MIDL);	
	if(reg!=OV7725_MID){
		Debug_Warning("MID="+std::to_string(reg)+" Normal=32674");
		flag=true;
	}else{
		Debug_Info("MID Read Correct");
	}
	reg	 =(Read_Reg_WithDefaultAdress(PID)<<8);
	reg	|=Read_Reg_WithDefaultAdress(VER);	
	if(reg!=OV7725_PID){
		flag=true;
        Debug_Warning(": PID="+std::to_string(reg)+" Normal=30497");
	}else{
		Debug_Info("PID Read Correct");
	}		
		
	for(uint32_t i=0;i<sizeof(ov7725_init_reg_tb1)/sizeof(ov7725_init_reg_tb1[0]);i++){				//初始化 OV7725,采用QVGA分辨率(320*240)  			
	   	Send_Reg_WithDefaultAdress(ov7725_init_reg_tb1[i][0],ov7725_init_reg_tb1[i][1]);
 	} 

	this->Work();
	Debug_Info("Work");
	
	if(flag){
		Debug_EndFAIL();
	}else{
		Debug_EndOK();
	}
}

void OV7725::Set_Light_Mode(Light_Mode mode){
	switch(mode)
	{
		case Light_Mode::Auto:	//Auto，自动模式
			Send_Reg_WithDefaultAdress(0x13, 0xff); //AWB on 
			Send_Reg_WithDefaultAdress(0x0e, 0x65);
			Send_Reg_WithDefaultAdress(0x2d, 0x00);
			Send_Reg_WithDefaultAdress(0x2e, 0x00);
			break;
		case Light_Mode::Sunny://sunny，晴天
			Send_Reg_WithDefaultAdress(0x13, 0xfd); //AWB off
			Send_Reg_WithDefaultAdress(0x01, 0x5a);
			Send_Reg_WithDefaultAdress(0x02, 0x5c);
			Send_Reg_WithDefaultAdress(0x0e, 0x65);
			Send_Reg_WithDefaultAdress(0x2d, 0x00);
			Send_Reg_WithDefaultAdress(0x2e, 0x00);
			break;	
		case Light_Mode::Cloudy:
			Send_Reg_WithDefaultAdress(0x13, 0xfd); //AWB off
			Send_Reg_WithDefaultAdress(0x01, 0x58);
			Send_Reg_WithDefaultAdress(0x02, 0x60);
			Send_Reg_WithDefaultAdress(0x0e, 0x65);
			Send_Reg_WithDefaultAdress(0x2d, 0x00);
			Send_Reg_WithDefaultAdress(0x2e, 0x00);
			break;	
		case Light_Mode::Office://office，办公室
			Send_Reg_WithDefaultAdress(0x13, 0xfd); //AWB off
			Send_Reg_WithDefaultAdress(0x01, 0x84);
			Send_Reg_WithDefaultAdress(0x02, 0x4c);
			Send_Reg_WithDefaultAdress(0x0e, 0x65);
			Send_Reg_WithDefaultAdress(0x2d, 0x00);
			Send_Reg_WithDefaultAdress(0x2e, 0x00);
			break;	
		case Light_Mode::Home://home，家里
			Send_Reg_WithDefaultAdress(0x13, 0xfd); //AWB off
			Send_Reg_WithDefaultAdress(0x01, 0x96);
			Send_Reg_WithDefaultAdress(0x02, 0x40);
			Send_Reg_WithDefaultAdress(0x0e, 0x65);
			Send_Reg_WithDefaultAdress(0x2d, 0x00);
			Send_Reg_WithDefaultAdress(0x2e, 0x00);
			break;	

		case Light_Mode::Night://night，夜晚
			Send_Reg_WithDefaultAdress(0x13, 0xff); //AWB on
			Send_Reg_WithDefaultAdress(0x0e, 0xe5);
			break;
	}
}		  
//色度设置
//sat:-4~+4
void OV7725::Set_Color_Saturation(int8_t sat){
 	if(sat>=-4 && sat<=4){	
		Send_Reg_WithDefaultAdress(USAT,(sat+4)<<4); 
		Send_Reg_WithDefaultAdress(VSAT,(sat+4)<<4);
	}
}
//亮度设置
//bright：-4~+4
void OV7725::Set_Brightness(int8_t bright){
	u_char bright_value=0,sign=0;
  	switch(bright){
		case 4:
			bright_value = 0x48;
			sign = 0x06;
			break;
		case 3:
			bright_value = 0x38;
			sign = 0x06;		
			break;	
		case 2:
			bright_value = 0x28;
			sign = 0x06;			
			break;	
		case 1:
			bright_value = 0x18;
			sign = 0x06;			
			break;
		case 0:
			bright_value = 0x08;
			sign = 0x06;			
			break;	
		case -1:
			bright_value = 0x08;
			sign = 0x0e;		
			break;		
		case -2:
			bright_value = 0x18;
			sign = 0x0e;		
			break;	
		case -3:
			bright_value = 0x28;
			sign = 0x0e;		
			break;	
		case -4:
			bright_value = 0x38;
			sign = 0x0e;		
			break;	
	}
	Send_Reg_WithDefaultAdress(BRIGHT, bright_value);
	Send_Reg_WithDefaultAdress(SIGN, sign);
}
//对比度设置
//contrast：-4~+4
void OV7725::Set_Contrast(int8_t contrast){
	if(contrast >= -4 && contrast <=4){
		Send_Reg_WithDefaultAdress(CNST,(0x30-(4-contrast)*4));
	}
}
//特效设置
//0:普通模式    
//1,负片
//2,黑白   
//3,偏红色
//4,偏绿色
//5,偏蓝色
//6,复古	    
void OV7725::Set_Special_Effects(u_char eft){
	switch(eft){
		case 0://正常
			Send_Reg_WithDefaultAdress(0xa6, 0x06);//TSLB设置
			Send_Reg_WithDefaultAdress(0x60, 0x80);//MANV,手动V值
			Send_Reg_WithDefaultAdress(0x61, 0x80);//MANU,手动U值
		break;
		case 1://负片
			Send_Reg_WithDefaultAdress(0xa6, 0x46);
		break;
		case 2://黑白
			Send_Reg_WithDefaultAdress(0xa6, 0x26);
			Send_Reg_WithDefaultAdress(0x60, 0x80);
			Send_Reg_WithDefaultAdress(0x61, 0x80);
		break;		
		case 3://偏红
			Send_Reg_WithDefaultAdress(0xa6, 0x1e);
			Send_Reg_WithDefaultAdress(0x60, 0x80);
			Send_Reg_WithDefaultAdress(0x61, 0xc0);		
		break;
		case 4://偏绿
			Send_Reg_WithDefaultAdress(0xa6, 0x1e);
			Send_Reg_WithDefaultAdress(0x60, 0x60);
			Send_Reg_WithDefaultAdress(0x61, 0x60);		
		break;
		case 5://偏蓝
			Send_Reg_WithDefaultAdress(0xa6, 0x1e);
			Send_Reg_WithDefaultAdress(0x60, 0xa0);
			Send_Reg_WithDefaultAdress(0x61, 0x40);	
		break;
		case 6://复古
			Send_Reg_WithDefaultAdress(0xa6, 0x1e);
			Send_Reg_WithDefaultAdress(0x60, 0x40);
			Send_Reg_WithDefaultAdress(0x61, 0xa0);
		break;	

	}
}	
//设置图像输出窗口
//width:图像宽度
//height:图像高度
//mode:0，QVGA输出模式；1，VGA输出模式
//QVGA模式可视范围广但近物不是很清晰，VGA模式可视范围小近物清晰
void OV7725::Set_Window(u_short width,u_short height,u_char mode){
	u_char raw,temp;
	u_short sx,sy;
	
	if(mode){
		if(width>640) width=640;
		if(height>480) height=480;
		sx=(640-width)/2;
		sy=(480-height)/2;
		Send_Reg_WithDefaultAdress(COM7,0x06);		//设置为VGA模式
		Send_Reg_WithDefaultAdress(HSTART,0x23); 	//水平起始位置
		Send_Reg_WithDefaultAdress(HSIZE,0xA0); 	//水平尺寸
		Send_Reg_WithDefaultAdress(VSTRT,0x07); 	//垂直起始位置
		Send_Reg_WithDefaultAdress(VSIZE,0xF0); 	//垂直尺寸
		Send_Reg_WithDefaultAdress(HREF,0x00);
		Send_Reg_WithDefaultAdress(HOutSize,0xA0); //输出尺寸
		Send_Reg_WithDefaultAdress(VOutSize,0xF0); //输出尺寸
	}
	else{
		if(width>320) width=320;
		if(height>240) height=240;
		sx=(320-width)/2;
		sy=(240-height)/2;
		Send_Reg_WithDefaultAdress(COM7,0x46);		//设置为QVGA模式
		Send_Reg_WithDefaultAdress(HSTART,0x3f); 	//水平起始位置
		Send_Reg_WithDefaultAdress(HSIZE, 0x50); 	//水平尺寸
		Send_Reg_WithDefaultAdress(VSTRT, 0x03); 	//垂直起始位置
		Send_Reg_WithDefaultAdress(VSIZE, 0x78); 	//垂直尺寸
		Send_Reg_WithDefaultAdress(HREF,  0x00);
		Send_Reg_WithDefaultAdress(HOutSize,0x50);	//输出尺寸
		Send_Reg_WithDefaultAdress(VOutSize,0x78); //输出尺寸
	}
	raw=Read_Reg_WithDefaultAdress(HSTART);
	temp=raw+(sx>>2);//sx高8位存在HSTART,低2位存在HREF[5:4]
	Send_Reg_WithDefaultAdress(HSTART,temp);
	Send_Reg_WithDefaultAdress(HSIZE,width>>2);//width高8位存在HSIZE,低2位存在HREF[1:0]
	
	raw=Read_Reg_WithDefaultAdress(VSTRT);
	temp=raw+(sy>>1);//sy高8位存在VSTRT,低1位存在HREF[6]
	Send_Reg_WithDefaultAdress(VSTRT,temp);
	Send_Reg_WithDefaultAdress(VSIZE,height>>1);//height高8位存在VSIZE,低1位存在HREF[2]
	
	raw=Read_Reg_WithDefaultAdress(HREF);
	temp=((sy&0x01)<<6)|((sx&0x03)<<4)|((height&0x01)<<2)|(width&0x03)|raw;
	Send_Reg_WithDefaultAdress(HREF,temp);
	
	Send_Reg_WithDefaultAdress(HOutSize,width>>2);
	Send_Reg_WithDefaultAdress(VOutSize,height>>1);
	
	Read_Reg_WithDefaultAdress(EXHCH);	
	temp = (raw|(width&0x03)|((height&0x01)<<2));	
	Send_Reg_WithDefaultAdress(EXHCH,temp);	
}




}

#endif