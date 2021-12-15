#pragma once
#include"../../Common.hpp"

#if __Enable_PIN&&__Enable_SystemClock






namespace HardWare{

    class ADS1256 : protected SPI_Component {
        private:
        PIN DRDY,RST,PDWN;
        void CheckChipID();
        void ADS1256_Send_Reg(u_char Reg,u_char txd);
        u_char ADS1256_Read_Reg(u_char Reg);
        public:
        /* 增益选项 */
        enum class Gain{
            GAIN_1			= (0),	/* 增益1（缺省） */
            GAIN_2			= (1),	/* 增益2 */
            GAIN_4			= (2),	/* 增益4 */
            GAIN_8			= (3),	/* 增益8 */
            GAIN_16			= (4),	/* 增益16 */
            GAIN_32			= (5),	/* 增益32 */
            GAIN_64			= (6),	/* 增益64 */	
        };
        /* 采样速率选项 */
        /* 数据转换率选择
            11110000 = 30,000SPS (default)
            11100000 = 15,000SPS
            11010000 = 7,500SPS
            11000000 = 3,750SPS
            10110000 = 2,000SPS
            10100001 = 1,000SPS
            10010010 = 500SPS
            10000010 = 100SPS
            01110010 = 60SPS
            01100011 = 50SPS
            01010011 = 30SPS
            01000011 = 25SPS
            00110011 = 15SPS
            00100011 = 10SPS
            00010011 = 5SPS
            00000011 = 2.5SPS
        */
        enum class SPS{
            SPS_30000       = 0b11110000,
            SPS_15000       = 0b11100000,
            SPS_7500        = 0b11010000,
            SPS_3750        = 0b11000000,
            SPS_2000        = 0b10110000,
            SPS_1000        = 0b10100001,
            SPS_500         = 0b10010010,
            SPS_100         = 0b10000010,
            SPS_60          = 0b01110010,
            SPS_50          = 0b01100011,
            SPS_30          = 0b01010011,
            SPS_25          = 0b01000011,
            SPS_15          = 0b00110011,
            SPS_10          = 0b00100011,
            SPS_5           = 0b00010011,
            SPS_2d5         = 0b00000011,
        };

        ADS1256(SPI_PIN_Pack,
            uint32_t DRDY_GPIOx,uint32_t DRDY_PINx,
            uint32_t RST_GPIOx,uint32_t RST_PINx,
            uint32_t PDWN_GPIOx,uint32_t PDWN_PINx
        );

        void Register_In_SolidEvent(std::function<void(void)> Callback);
        void Config_Adc(Gain gain,SPS sps);
        int32_t GetAdc(u_char channel);
        int32_t ReadAdc(u_char channel);
        void Reset();
    };
}


#endif