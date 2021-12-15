#include"./ADS1256.h"

#if __Enable_PIN&&__Enable_SystemClock


/* 寄存器地址， 后面是复位后缺省值 */
DEFREG{
	STATUS = 0,	// x1H
	MUX    = 1, // 01H
	ADCON  = 2, // 20H
	DRATE  = 3, // F0H
	IO     = 4, // E0H
	OFC0   = 5, // xxH
	OFC1   = 6, // xxH
	OFC2   = 7, // xxH
	FSC0   = 8, // xxH
	FSC1   = 9, // xxH
	FSC2   = 10, // xxH
};

/* 命令定义： TTable 24. Command Definitions --- ADS1256数据手册第34页 */
DEFCMD{
    WAKEUP  = 0x00,	// Completes SYNC and Exits Standby Mode 0000  0000 (00h)
	RDATA   = 0x01, // Read Data 0000  0001 (01h)
	RDATAC  = 0x03, // Read Data Continuously 0000   0011 (03h)
	SDATAC  = 0x0F, // Stop Read Data Continuously 0000   1111 (0Fh)
	RREG    = 0x10, // Read from REG rrr 0001 rrrr (1xh)
	WREG    = 0x50, // Write to REG rrr 0101 rrrr (5xh)
	SELFCAL = 0xF0, // Offset and Gain Self-Calibration 1111    0000 (F0h)
	SELFOCAL= 0xF1, // Offset Self-Calibration 1111    0001 (F1h)
	SELFGCAL= 0xF2, // Gain Self-Calibration 1111    0010 (F2h)
	SYSOCAL = 0xF3, // System Offset Calibration 1111   0011 (F3h)
	SYSGCAL = 0xF4, // System Gain Calibration 1111    0100 (F4h)
	SYNC    = 0xFC, // Synchronize the A/D Conversion 1111   1100 (FCh)
	STANDBY = 0xFD, // Begin Standby Mode 1111   1101 (FDh)
	RESET   = 0xFE, // Reset to Power-Up Values 1111   1110 (FEh)
};

namespace HardWare{

    ADS1256::ADS1256(SPI_PIN_Pack,
    uint32_t DRDY_GPIOx,uint32_t DRDY_PINx,
    uint32_t RST_GPIOx,uint32_t RST_PINx,
    uint32_t PDWN_GPIOx,uint32_t PDWN_PINx):
    SPI_Component(SPI_PIN_Data,SPI_type::IO,{false,true,false}),
    DRDY(DRDY_GPIOx,DRDY_PINx,PIN_Mode::Fast),
    RST(RST_GPIOx,RST_PINx,PIN_Mode::Fast),
    PDWN(PDWN_GPIOx,PDWN_PINx,PIN_Mode::Fast){
        DRDY.F_ReadMode();
        RST=1;
        PDWN=1;
    }

    void ADS1256::Register_In_SolidEvent(std::function<void(void)> Callback){
        SolidEvent::getInstance().Register([&]()->bool{return !this->DRDY;},Callback);
    }

    void ADS1256::Config_Adc(Gain gain,SPS sps){
        u_int32_t i=0;
        Debug_StartBlock("Config_Adc");
        Reset();
        while(DRDY){
            if(++i>=400000000){
                break;
            }
        }
        if(i<400000000){
            Debug_EndOK();
        }else{
            Debug_EndFAIL();
        }
        Debug_EndBlock();
        {
            u_char buf[4];
            /* 状态寄存器定义
                Bits 7-4 ID3, ID2, ID1, ID0  Factory Programmed Identification Bits (Read Only)
            
                Bit 3 ORDER: Data Output Bit Order
                    0 = Most Significant Bit First (default)
                    1 = Least Significant Bit First
                Input data  is always shifted in most significant byte and bit first. Output data is always shifted out most significant
                byte first. The ORDER bit only controls the bit order of the output data within the byte.

                Bit 2 ACAL : Auto-Calibration
                    0 = Auto-Calibration Disabled (default)
                    1 = Auto-Calibration Enabled
                When Auto-Calibration is enabled, self-calibration begins at the completion of the WREG command that changes
                the PGA (bits 0-2 of ADCON register), DR (bits 7-0 in the DRATE register) or BUFEN (bit 1 in the STATUS register)
                values.

                Bit 1 BUFEN: Analog Input Buffer Enable
                    0 = Buffer Disabled (default)
                    1 = Buffer Enabled

                Bit 0 DRDY :  Data Ready (Read Only)	
                    This bit duplicates the state of the DRDY pin.

                ACAL=1使能自校准功能。当 PGA，BUFEEN, DRATE改变时会启动自校准
            */
            buf[0] = (0 << 3) | (1 << 2) | (1 << 1);
            //ADS1256_WriteReg(REG_STATUS, (0 << 3) | (1 << 2) | (1 << 1));
            buf[1] = 0x08;/* 高四位0表示AINP接 AIN0,  低四位8表示 AINN 固定接 AINCOM */
            /*	ADCON: A/D Control Register (Address 02h)
                Bit 7 Reserved, always 0 (Read Only)
                Bits 6-5 CLK1, CLK0 : D0/CLKOUT Clock Out Rate Setting
                    00 = Clock Out OFF
                    01 = Clock Out Frequency = fCLKIN (default)
                    10 = Clock Out Frequency = fCLKIN/2
                    11 = Clock Out Frequency = fCLKIN/4
                    When not using CLKOUT, it is recommended that it be turned off. These bits can only be reset using the RESET pin.

                Bits 4-2 SDCS1, SCDS0: Sensor Detect Current Sources
                    00 = Sensor Detect OFF (default)
                    01 = Sensor Detect Current = 0.5 μ A
                    10 = Sensor Detect Current = 2 μ A
                    11 = Sensor Detect Current = 10μ A
                    The Sensor Detect Current Sources can be activated to verify  the integrity of an external sensor supplying a signal to the
                    ADS1255/6. A shorted sensor produces a very small signal while an open-circuit sensor produces a very large signal.

                Bits 2-0 PGA2, PGA1, PGA0: Programmable Gain Amplifier Setting
                    000 = 1 (default)
                    001 = 2
                    010 = 4
                    011 = 8
                    100 = 16
                    101 = 32
                    110 = 64
                    111 = 64
            */
            buf[2] = (0 << 5) | (0 << 2) | ((u_char)gain << 1);
            //ADS1256_WriteReg(REG_ADCON, (0 << 5) | (0 << 2) | (GAIN_1 << 1));	/* 选择1;1增益, 输入正负5V */

		    /* 因为切换通道和读数据耗时 123uS, 因此扫描中断模式工作时，最大速率 = DRATE_1000SPS */
            buf[3] = (u_char)sps;	// DRATE_10SPS;	/* 选择数据输出速率 */
            Start();
            Send_Byte(USECMD::WREG|0);
            Send_Byte(3);
            Send_Len(4,buf);
            End();
        }
        SystemClock::Delay(50);
    }

    int32_t ADS1256::GetAdc(u_char channel){
        this->Send_Reg(USEREG::MUX,(channel<<4)|(1<<3));
    }

    int32_t ADS1256::ReadAdc(u_char channel){

    }

    void ADS1256::Reset(){
        RST=0;
        SystemClock::Delay(5);
        RST=1;
        SystemClock::Delay(5);
    }

    void ADS1256::CheckChipID(){
        
    }

    void ADS1256::ADS1256_Send_Reg(u_char Reg,u_char txd){
        Start();
        Send_Byte(USECMD::WREG|Reg);	/* 写寄存器的命令, 并发送寄存器地址 */
        Send_Byte(0x00);		        /* 寄存器个数 - 1, 此处写1个寄存器 */
        Send_Byte(txd);         	    /* 发送寄存器值 */
        End();
    }

    u_char ADS1256::ADS1256_Read_Reg(u_char Reg){
        u_char rxd;
        Start();
        Send_Byte(USECMD::RREG|Reg);
        Send_Byte(0x00);
        SystemClock::Delay(10);
        rxd=Read_Byte();
        End();
        return rxd;
    }

}

#endif