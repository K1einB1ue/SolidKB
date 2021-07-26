#include<HardWare/AD7705.h>
#include<SoftHardWare/SystemClock.h>

#define __CH1_GAIN_BIPOLAR_BUF	(GAIN_1 | UNIPOLAR | BUF_EN)
#define __CH2_GAIN_BIPOLAR_BUF	(GAIN_1 | UNIPOLAR | BUF_EN)

enum
{
	/* 寄存器选择  RS2 RS1 RS0  */
	REG_COMM	    = 0x00,	    /* 通信寄存器 */
	REG_SETUP	    = 0x10,	    /* 设置寄存器 */
	REG_CLOCK	    = 0x20,	    /* 时钟寄存器 */
	REG_DATA	    = 0x30,	    /* 数据寄存器 */
	REG_ZERO_CH1	= 0x60,	    /* CH1 偏移寄存器 */
	REG_FULL_CH1	= 0x70,	    /* CH1 满量程寄存器 */
	REG_ZERO_CH2	= 0x61,	    /* CH2 偏移寄存器 */
	REG_FULL_CH2	= 0x71,	    /* CH2 满量程寄存器 */

	/* 读写操作 */
	WRITE 		    = 0x00,	    /* 写操作 */
	READ 		    = 0x08,	    /* 读操作 */

	/* 通道 */
	CH_1		    = 0,	    /* AIN1+  AIN1- */
	CH_2		    = 1,	    /* AIN2+  AIN2- */
	CH_3		    = 2,	    /* AIN1-  AIN1- */
	CH_4		    = 3		    /* AIN1-  AIN2- */
};

/* 设置寄存器bit定义 */
enum
{
	MD_NORMAL		= (0 << 6),	/* 正常模式 */
	MD_CAL_SELF		= (1 << 6),	/* 自校准模式 */
	MD_CAL_ZERO		= (2 << 6),	/* 校准0刻度模式 */
	MD_CAL_FULL		= (3 << 6),	/* 校准满刻度模式 */

	GAIN_1			= (0 << 3),	/* 增益 */
	GAIN_2			= (1 << 3),	/* 增益 */
	GAIN_4			= (2 << 3),	/* 增益 */
	GAIN_8			= (3 << 3),	/* 增益 */
	GAIN_16			= (4 << 3),	/* 增益 */
	GAIN_32			= (5 << 3),	/* 增益 */
	GAIN_64			= (6 << 3),	/* 增益 */
	GAIN_128		= (7 << 3),	/* 增益 */

	/* 无论双极性还是单极性都不改变任何输入信号的状态，它只改变输出数据的代码和转换函数上的校准点 */
	BIPOLAR			= (0 << 2),	/* 双极性输入 */
	UNIPOLAR		= (1 << 2),	/* 单极性输入 */

	BUF_NO			= (0 << 1),	/* 输入无缓冲（内部缓冲器不启用) */
	BUF_EN			= (1 << 1),	/* 输入有缓冲 (启用内部缓冲器) */

	FSYNC_0			= 0,
	FSYNC_1			= 1		/* 不启用 */
};

/* 时钟寄存器bit定义 */
enum
{
	CLKDIS_0	    = 0x00,		/* 时钟输出使能 （当外接晶振时，必须使能才能振荡） */
	CLKDIS_1	    = 0x10,		/* 时钟禁止 （当外部提供时钟时，设置该位可以禁止MCK_OUT引脚输出时钟以省电 */

	/*
		2.4576MHz（CLKDIV=0 ）或为 4.9152MHz （CLKDIV=1 ），CLK 应置 “0”。
		1MHz （CLKDIV=0 ）或 2MHz   （CLKDIV=1 ），CLK 该位应置  “1”
	*/
	CLK_4_9152M     = 0x08,
	CLK_2_4576M     = 0x00,
	CLK_1M 		    = 0x04,
	CLK_2M 		    = 0x0C,

	FS_50HZ		    = 0x00,
	FS_60HZ		    = 0x01,
	FS_250HZ	    = 0x02,
	FS_500HZ	    = 0x04,

	/*
		四十九、电子秤应用中提高TM7705 精度的方法
        当使用主时钟为 2.4576MHz 时，强烈建议将时钟寄存器设为 84H,此时数据输出更新率为10Hz,即每0.1S 输出一个新数据。
        当使用主时钟为 1MHz 时，强烈建议将时钟寄存器设为80H, 此时数据输出更新率为4Hz, 即每0.25S 输出一个新数据
	*/
	ZERO_0		    = 0x00,
	ZERO_1		    = 0x80
};


namespace HardWare{
    AD7705::AD7705(
        uint32_t DIN_GPIOx  ,uint32_t DIN_PINx, 
        uint32_t DOUT_GPIOx ,uint32_t DOUT_PINx,
        uint32_t SCK_GPIOx  ,uint32_t SCK_PINx,
        uint32_t CS_GPIOx   ,uint32_t CS_PINx,
        uint32_t RST_GPIOx  ,uint32_t RST_PINx,
        uint32_t DRDY_GPIOx ,uint32_t DRDY_PINx
    ):SPI_Component(DIN_GPIOx,DIN_PINx,DOUT_GPIOx,DOUT_PINx,SCK_GPIOx,SCK_PINx,CS_GPIOx,CS_PINx),
    RST(RST_GPIOx,RST_PINx,PIN_Mode::Fast),
    DRDY(DRDY_GPIOx,DRDY_PINx,PIN_Mode::Fast){
        RST.F_WriteMode();
        DRDY.F_ReadMode();
        this->__SPI_CS_Active(0);
        this->__SPI_Mode(0,0);
        SystemClock::Delay(10000);

        /* 硬件复位 */
        this->Reset();              

        /*
		在接口序列丢失的情况下，如果在DIN 高电平的写操作持续了足够长的时间（至少 32个串行时钟周期），
		TM7705 将会回到默认状态。
	    */

        SystemClock::Delay(50000);

        /* 同步SPI接口时序 */
        this->Sync();               
        SystemClock::Delay(50000);

        /* 配置时钟寄存器 */
        this->WriteByte(REG_CLOCK | WRITE | CH_1);              /* 先写通信寄存器，下一步是写时钟寄存器 */
        //this->WriteByte(CLKDIS_0 | CLK_4_9152M | FS_50HZ);      /* 刷新速率50Hz */
        this->WriteByte(CLKDIS_0 | CLK_4_9152M | FS_500HZ);	/* 刷新速率500Hz */
        Debug::StartBlock("CH1_CalibSelf");
        this->CalibSelf(Channel::Ch1);
        Debug::EndBlock();
        SystemClock::Delay(50000);
        Debug::StartBlock("CH2_CalibSelf");
        this->CalibSelf(Channel::Ch2);
        Debug::EndBlock();
        SystemClock::Delay(50000);
    }

    void AD7705::Reset(){
        RST=1;
        SystemClock::Delay(1000);
        RST=0;
        SystemClock::Delay(2000);
        RST=1;
        SystemClock::Delay(1000);
    }

    void AD7705::Sync(){
        this->Start();
        this->Send_Byte(0xFF);
        this->Send_Byte(0xFF);
        this->Send_Byte(0xFF);
        this->Send_Byte(0xFF);
        this->End();
    }
    //启动自校准.内部自动短接AIN+ AIN-校准0位,内部短接到Vref 校准满位.此函数执行过程较长,实测约180ms
    void AD7705::CalibSelf(Channel channel){
        switch (channel)
        {
        case Channel::Ch1:
            /* 自校准CH1 */
            this->WriteByte(REG_SETUP | WRITE | CH_1);	/* 写通信寄存器，下一步是写设置寄存器，通道1 */		
            this->WriteByte(MD_CAL_SELF | __CH1_GAIN_BIPOLAR_BUF | FSYNC_0);    /* 启动自校准 */
            this->WaitDRDY();	/* 等待内部操作完成 --- 时间较长，约180ms */
            break;
        case Channel::Ch2:
            /* 自校准CH2 */
            this->WriteByte(REG_SETUP | WRITE | CH_2);	/* 写通信寄存器，下一步是写设置寄存器，通道2 */
            this->WriteByte(MD_CAL_SELF | __CH2_GAIN_BIPOLAR_BUF | FSYNC_0);	/* 启动自校准 */
            this->WaitDRDY();	/* 等待内部操作完成  --- 时间较长，约180ms */
            break;
        }
    }
    //启动系统校准零位.请将AIN+ AIN-短接后,执行该函数.校准应该由主程序控制并保存校准参数.执行完毕后.可以通过ReadReg(REG_ZERO_CH1)和ReadReg(REG_ZERO_CH2)读取校准参数.
    void AD7705::SystemCalibZero(Channel channel){
        switch (channel)
        {
        case Channel::Ch1:
            /* 校准CH1 */
            this->WriteByte(REG_SETUP | WRITE | CH_1);	/* 写通信寄存器，下一步是写设置寄存器，通道1 */
            this->WriteByte(MD_CAL_ZERO | __CH1_GAIN_BIPOLAR_BUF | FSYNC_0);    /* 启动自校准 */
            this->WaitDRDY();	/* 等待内部操作完成 */
            break;
        case Channel::Ch2:
            /* 校准CH2 */
            this->WriteByte(REG_SETUP | WRITE | CH_2);	/* 写通信寄存器，下一步是写设置寄存器，通道1 */
            this->WriteByte(MD_CAL_ZERO | __CH2_GAIN_BIPOLAR_BUF | FSYNC_0);	/* 启动自校准 */
            this->WaitDRDY();	/* 等待内部操作完成 */
            break;
        }
    }
    //启动系统校准满位.请将AIN+ AIN-接最大输入电压源,执行该函数.校准应该由主程序控制并保存校准参数.执行完毕后.可以通过ReadReg(REG_FULL_CH1)和ReadReg(REG_FULL_CH2)读取校准参数.
    void AD7705::SystemCalibFull(Channel channel){
        switch (channel)
        {
        case Channel::Ch1:
            /* 校准CH1 */
            this->WriteByte(REG_SETUP | WRITE | CH_1);	/* 写通信寄存器，下一步是写设置寄存器，通道1 */
            this->WriteByte(MD_CAL_FULL | __CH1_GAIN_BIPOLAR_BUF | FSYNC_0);/* 启动自校准 */
            this->WaitDRDY();	/* 等待内部操作完成 */
            break;
        case Channel::Ch2:
            /* 校准CH2 */
            this->WriteByte(REG_SETUP | WRITE | CH_2);	/* 写通信寄存器，下一步是写设置寄存器，通道1 */
            this->WriteByte(MD_CAL_FULL | __CH2_GAIN_BIPOLAR_BUF | FSYNC_0);	/* 启动自校准 */
            this->WaitDRDY();	/* 等待内部操作完成 */
            break;
        }
    }

    void AD7705::WriteByte(u_char data){
        this->Start();
        this->Send_Byte(data);
        this->End();
    }
    void AD7705::Write3Byte(u_int data){
        this->Start();
        this->Send_Byte((data>>16)&0xFF);
        this->Send_Byte((data>>8)&0xFF);
        this->Send_Byte((data)&0xFF);
        this->End();
    }
    void AD7705::WriteReg(u_char regID,u_int regValue){
        u_char bits=0;
        switch (regID)
        {
        case REG_COMM:
        case REG_SETUP:
        case REG_CLOCK:
            bits=8;
            break;
        case REG_ZERO_CH1:
        case REG_FULL_CH1:
        case REG_ZERO_CH2:
        case REG_FULL_CH2:
            bits=24;
            break;
        case REG_DATA:
        default:
            return;
        }
        if(bits==8){
            this->WriteByte((u_char)regValue);
        }else if(bits==24){
            this->Write3Byte(regValue);
        }
    }

    u_char AD7705::ReadByte(){
        u_char read=0;
        this->Start();
        read=this->Read_Byte();
        this->End();
        return read;
    }

    u_short AD7705::Read2Byte(){
        u_short read=0;
        this->Start();
        read=this->Read_Byte();
        read<<=8;
        read+=this->Read_Byte();
        this->End();
        return read;
    }

    u_int AD7705::Read3Byte(){
        u_int read=0;
        this->Start();
        read=this->Read_Byte();
        read<<=8;
        read+=this->Read_Byte();
        read<<=8;
        read+=this->Read_Byte();
        this->End();
        return read;
    }

    u_int AD7705::ReadReg(u_char regID){
        uint8_t bits=0;
        uint32_t read=0;

        switch (regID)
        {
            case REG_COMM:		        /* 通信寄存器              */
            case REG_SETUP:		        /* 设置寄存器         8bit */
            case REG_CLOCK:		        /* 时钟寄存器         8bit */
                bits = 8;
                break;

            case REG_ZERO_CH1:	        /* CH1 偏移寄存器     24bit */
            case REG_FULL_CH1:	        /* CH1 满量程寄存器   24bit */
            case REG_ZERO_CH2:	        /* CH2 偏移寄存器     24bit */
            case REG_FULL_CH2:	        /* CH2 满量程寄存器   24bit */
                bits = 24;
                break;

            case REG_DATA:		        /* 数据寄存器         16bit */
            default:
                return 0xFFFFFFFF;
        }

        this->WriteByte(regID | READ);	/* 写通信寄存器,指定下一步是写操作,并指定写哪个寄存器 */

        if (bits == 16)
        {
            read = this->Read2Byte();
        }
        else if (bits == 8)
        {
            read = this->ReadByte();
        }
        else	                        /* 24bit */
        {
            read = this->Read3Byte();
        }
        return read;
    }

    void AD7705::WaitDRDY(){    
        uint32_t i;
        for(i=0;i<40000000ul;i++){
            if(!DRDY){
                Debug::Info("OK");
                break;
            }
        }
        if(i>=40000000ul){
            Debug::Warning("WaitDRDY TimeOut!");
        }
    }

    u_short AD7705::ReadChannel1(){
        uint16_t read = 0;
        
        /* 为了避免通道切换造成读数失效，读2次 */
        for (uint8_t i = 0; i < 2; i++)
        {
            this->WaitDRDY();		/* 等待DRDY口线为0 */
            this->WriteByte(0x38);
            read = this->Read2Byte();
        }
        return read;	
    }
    u_short AD7705::ReadChannel2(){
        uint16_t read = 0;
        
        /* 为了避免通道切换造成读数失效，读2次 */
        for (uint8_t i = 0; i < 2; i++)
        {
            this->WaitDRDY();		/* 等待DRDY口线为0 */
            this->WriteByte(0x39);
            read = this->Read2Byte();
        }
        return read;	
    }
    int AD7705::Get_Channel1_mV(){
        return (this->ReadChannel1()*5000)/65535;
    }
    int AD7705::Get_Channel2_mV(){
        return (this->ReadChannel2()*5000)/65535;
    }
}