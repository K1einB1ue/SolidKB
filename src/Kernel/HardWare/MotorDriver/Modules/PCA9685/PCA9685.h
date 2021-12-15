#pragma once
#include"../../Common.hpp"

#if __Enable_PIN&&__Enable_SystemClock


namespace HardWare{
    class PCA9685:public I2C_Component{
        private:
        public:
        PCA9685(
            I2C_PIN_Pack
        );
        void reset(void);
        void setPWMFreq(float freq);
        void setPWM(uint8_t num, uint16_t on, uint16_t off);
        void setPin(uint8_t num, uint16_t val, bool invert=false);
        void setPWM(u_char num,float PWM);
    };
}

#endif