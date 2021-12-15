#include"./PCA9685.h"

#if __Enable_PIN&&__Enable_SystemClock


DEFREG{
    LED0_ON_L               =0x6,
    LED0_ON_H               =0x7,
    LED0_OFF_L              =0x8,
    LED0_OFF_H              =0x9,

    PCA9685_MODE1           =0x0,
    PCA9685_PRESCALE        =0xFE,

    PCA9685_SUBADR1         =0x2,
    PCA9685_SUBADR2         =0x3,
    PCA9685_SUBADR3         =0x4,

    ALLLED_ON_L             =0xFA,
    ALLLED_ON_H             =0xFB,
    ALLLED_OFF_L            =0xFC,
    ALLLED_OFF_H            =0xFD
};


namespace HardWare{
    PCA9685::PCA9685(I2C_PIN_Pack):I2C_Component(I2C_PIN_Data){
        this->address=0x40;
        this->reset();
    }


    void PCA9685::reset(void) {
        Send_Reg(USEREG::PCA9685_MODE1, 0x0);
    }

    void PCA9685::setPWMFreq(float freq) {
        freq /= 0.971;  // Correct for overshoot in the frequency setting (see issue #11).
        float prescaleval = 25000000;
        prescaleval /= 4096;
        prescaleval /= freq;
        prescaleval -= 1;

        uint8_t prescale = std::floor(prescaleval + 0.5);

        uint8_t oldmode =this->Read_Reg(USEREG::PCA9685_MODE1);
        uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
        Send_Reg(USEREG::PCA9685_MODE1, newmode); // go to sleep
        Send_Reg(USEREG::PCA9685_PRESCALE, prescale); // set the prescaler
        Send_Reg(USEREG::PCA9685_MODE1, oldmode);
        SystemClock::Delay(5);
        Send_Reg(USEREG::PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
                                                // This is why the beginTransmission below was not working.
        //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
    }

    void PCA9685::setPWM(uint8_t num, uint16_t on, uint16_t off) {
        //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
        u_char buf[5];
        buf[0]=USEREG::LED0_ON_L+4*num;
        buf[1]=on;
        buf[2]=on>>8;
        buf[3]=off;
        buf[4]=off>>8;
        this->Send_Len(5,buf);
    }

    void PCA9685::setPWM(u_char num,float PWM){
        u_char buf[5];
        u_int16_t temp=PWM*4096;
        buf[0]=USEREG::LED0_ON_L+4*num;
        buf[1]=0;
        buf[2]=0;
        buf[3]=temp;
        buf[4]=temp>>8;
        this->Send_Len(5,buf);
    }

    // Sets pin without having to deal with on/off tick placement and properly handles
    // a zero value as completely off.  Optional invert parameter supports inverting
    // the pulse for sinking to ground.  Val should be a value from 0 to 4095 inclusive.
    void PCA9685::setPin(uint8_t num, uint16_t val, bool invert){
        // Clamp value between 0 and 4095 inclusive.
        val = std::min((int)val, 4095);
        if (invert) {
            if (val == 0)           setPWM(num, 4096, 0);
            else if (val == 4095)   setPWM(num, 0, 4096);
            else                    setPWM(num, 0, 4095-val);
        }else {
            if (val == 4095)        setPWM(num, 4096, 0);
            else if (val == 0)      setPWM(num, 0, 4096);
            else                    setPWM(num, 0, val);
        }
    }


}


#endif
