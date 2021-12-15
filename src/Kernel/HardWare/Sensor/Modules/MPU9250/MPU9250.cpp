#include"./MPU9250.h"

#if __Enable_PIN&&__Enable_SystemClock

#define DefaultAddress 0b11010000

DEFREG{
    //MPU9250 registers
    SELF_TEST_X_GYRO        =0x00,
    SELF_TEST_Y_GYRO        =0x01,
    SELF_TEST_Z_GYRO        =0x02,
    SELF_TEST_X_ACCEL       =0x0D,
    SELF_TEST_Y_ACCEL       =0x0E,
    SELF_TEST_Z_ACCEL       =0x0F,
    XG_OFFSET_H             =0x13,
    XG_OFFSET_L             =0x14,
    YG_OFFSET_H             =0x15,
    YG_OFFSET_L             =0x16,
    ZG_OFFSET_H             =0x17,
    ZG_OFFSET_L             =0x18,
    SMPLRT_DIV              =0x19,
    CONFIG                  =0x1A,
    GYRO_CONFIG             =0x1B,
    ACCEL_CONFIG            =0x1C,
    ACCEL_CONFIG2           =0x1D,
    LP_ACCEL_ODR            =0x1E,
    WOM_THR                 =0x1F,
    FIFI_EN                 =0x23,
    I2C_MST_CTRL            =0X24,
    I2C_SLV0_ADDR           =0x25,
    I2C_SLV0_REG            =0x26,
    I2C_SLV0_CTRL           =0x27,
    I2C_SLV1_ADDR           =0x28,
    I2C_SLV1_REG            =0x29,
    I2C_SLV1_CTRL           =0x2A,
    I2C_SLV2_ADDR           =0x2B,
    I2C_SLV2_REG            =0x2C,
    I2C_SLV2_CTRL           =0x2D,
    I2C_SLV3_ADDR           =0x2E,
    I2C_SLV3_REG            =0x2f,
    I2C_SLV3_CTRL           =0x30,
    I2C_SLV4_ADDR           =0x31,
    I2C_SLV4_REG            =0x32,
    I2C_SLV4_DO             =0x33,
    I2C_SLV4_CTRL           =0x34,
    I2C_SLV4_DI             =0x35,
    I2C_MST_STATUS          =0x35,
    INT_PIN_CFG             =0x37,
    INT_ENABLE              =0x38,
    INT_STATUS              =0x3A,
    ACCEL_XOUT_H            =0x3B,
    ACCEL_XOUT_L            =0x3C,
    ACCEL_YOUT_H            =0x3D,
    ACCEL_YOUT_L            =0x3E,
    ACCEL_ZOUT_H            =0x3F,
    ACCEL_ZOUT_L            =0x40,
    TEMP_OUT_H              =0x41,
    TEMP_OUT_L              =0x42,
    GYRO_XOUT_H             =0x43,
    GYRO_XOUT_L             =0x44,
    GYRO_YOUT_H             =0x45,
    GYRO_YOUT_L             =0x46,
    GYRO_ZOUT_H             =0x47,
    GYRO_ZOUT_L             =0x48,
    EXT_SENS_DATA_00        =0x49,
    EXT_SENS_DATA_01        =0x4A,
    EXT_SENS_DATA_02        =0x4B,
    EXT_SENS_DATA_03        =0x4C,
    EXT_SENS_DATA_04        =0x4D,
    EXT_SENS_DATA_05        =0x4E,
    EXT_SENS_DATA_06        =0x4F,
    EXT_SENS_DATA_07        =0x50,
    EXT_SENS_DATA_08        =0x51,
    EXT_SENS_DATA_09        =0x52,
    EXT_SENS_DATA_10        =0x53,
    EXT_SENS_DATA_11        =0x54,
    EXT_SENS_DATA_12        =0x55,
    EXT_SENS_DATA_13        =0x56,
    EXT_SENS_DATA_14        =0x57,
    EXT_SENS_DATA_15        =0x58,
    EXT_SENS_DATA_16        =0x59,
    EXT_SENS_DATA_17        =0x5A,
    EXT_SENS_DATA_18        =0x5B,
    EXT_SENS_DATA_19        =0x5C,
    EXT_SENS_DATA_20        =0x5D,
    EXT_SENS_DATA_21        =0x5E,
    EXT_SENS_DATA_22        =0x5F,
    EXT_SENS_DATA_23        =0x60,
    I2C_SLV0_DO             =0x63,
    I2C_SLV1_DO             =0x64,
    I2C_SLV2_DO             =0x65,
    I2C_SLV3_DO             =0x66,
    I2C_MST_DELAY_CTRL      =0x67,
    SIGNAL_PATH_RESET       =0x68,
    MOT_DETECT_CTRL         =0x69,
    USER_CTRL               =0x6A,
    PWR_MGMT_1              =0x6B,
    PWR_MGMT_2              =0x6C,
    FIFO_COUNTH             =0x72,
    FIFO_COUNTL             =0x73,
    FIFO_R_W                =0x74,
    WHO_AM_I                =0x75,
    XA_OFFSET_H             =0x77,
    XA_OFFSET_L             =0x78,
    YA_OFFSET_H             =0x7A,
    YA_OFFSET_L             =0x7B,
    ZA_OFFSET_H             =0x7D,
    ZA_OFFSET_L             =0x7E,



    //AK8963 registers
    AK8963_WHO_AM_I         =0x00,
    AK8963_INFO             =0x01,
    AK8963_ST1              =0x02,
    AK8963_HXL              =0x03,
    AK8963_HXH              =0x04,
    AK8963_HYL              =0x05,
    AK8963_HYH              =0x06,
    AK8963_HZL              =0x07,
    AK8963_HZH              =0x08,
    AK8963_ST2              =0x09,
    AK8963_CNTL1            =0x0A,
    AK8963_CNTL2            =0x0B,
    AK8963_ASTC             =0x0C,
    AK8963_TS1              =0x0D,
    AK8963_TS2              =0x0E,
    AK8963_I2CDIS           =0x0F,
    AK8963_ASAX             =0x10,
    AK8963_ASAY             =0x11,
    AK8963_ASAZ             =0x12,
};

DEFSEL(I2C_MST_CTRL){
    MULT_MST_EN             =BIT7,
    WAIT_FOR_ES             =BIT6,
    SLV_3_FIFO_EN           =BIT5,
    I2C_MST_P_NSR           =BIT4,
    I2C_MST_CLK_348KHz      =0,
    I2C_MST_CLK_333KHz      =1,
    I2C_MST_CLK_320KHz      =2,
    I2C_MST_CLK_308KHz      =3,
    I2C_MST_CLK_296KHz      =4,
    I2C_MST_CLK_286KHz      =5,
    I2C_MST_CLK_276KHz      =6,
    I2C_MST_CLK_267KHz      =7,
    I2C_MST_CLK_258KHz      =8,
    I2C_MST_CLK_500KHz      =9,
    I2C_MST_CLK_471KHz      =10,
    I2C_MST_CLK_444KHz      =11,
    I2C_MST_CLK_421KHz      =12,
    I2C_MST_CLK_400KHz      =13,
    I2C_MST_CLK_381KHz      =14,
    I2C_MST_CLK_364KHz      =15,
};

DEFSEL(USER_CTRL){
    FIFO_EN                 =BIT6,
    I2C_MST_EN              =BIT5,
    I2C_IF_DIS              =BIT4,
    FIFO_RST                =BIT2,
    I2C_MST_RST             =BIT1,
    SIG_COND_RST            =BIT0,
};

DEFSEL(PWR_MGMT_1){
    H_RESET                 =BIT7,
    SLEEP                   =BIT6,
    CYCLE                   =BIT5,
    GYRO_STANDBY            =BIT4,
    PD_PTAT                 =BIT3,
    ClkSource_l20MHz        =0,
    ClkSource_Auto          =1,
    ClkSource_20MHz         =6,
    ClkSource_Stop          =7,
};

DEFSEL(PWR_MGMT_2){
    DISABLE_XA              =BIT5,
    DISABLE_YA              =BIT4,
    DISABLE_ZA              =BIT3,
    DISABLE_XG              =BIT2,
    DISABLE_YG              =BIT1,
    DISABLE_ZG              =BIT0,
    SEN_ENABLE              =0,
};

DEFSEL(I2C_SLV_CTRL){
    I2C_SLV_EN              =BIT7,
    I2C_SLV_BYTE_SW         =BIT6,
    I2C_SLV_REG_DIS         =BIT5,
    I2C_SLV_GRP             =BIT4,
    I2C_SLV_LENG            =BIT3|BIT2|BIT1|BIT0,
};

DEFSELS(I2C_SLV0_CTRL,I2C_SLV_CTRL);
DEFSELS(I2C_SLV1_CTRL,I2C_SLV_CTRL);
DEFSELS(I2C_SLV2_CTRL,I2C_SLV_CTRL);
DEFSELS(I2C_SLV3_CTRL,I2C_SLV_CTRL);

DEFSEL(I2C_SLV_ADDR){
    I2C_SLV_RNW             =BIT7,
    I2C_ID                  =BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0,
};

DEFSELS(I2C_SLV1_ADDR,I2C_SLV_ADDR);
DEFSELS(I2C_SLV1_ADDR,I2C_SLV_ADDR);
DEFSELS(I2C_SLV2_ADDR,I2C_SLV_ADDR);
DEFSELS(I2C_SLV3_ADDR,I2C_SLV_ADDR);

DEFSEL(AK8963_CNTL1){
    Mode_Power_Down                     =0,
    Mode_Single_Measurement             =BIT0,
    Mode_Continuous_Measurement1        =BIT1,
    Mode_Continuous_Measurement2        =BIT1|BIT2,
    Mode_External_Trigger_Measurement   =BIT2,
    Mode_Self_Test                      =BIT3,
    Mode_Fuse_ROM_Access                =BIT0|BIT1|BIT2|BIT3,
    Bits_16                             =BIT4,
    Bits_14                             =0,
};

DEFSEL(AK8963_CNTL2){
    Normal                              =0,
    Reset                               =BIT0,
};

DEFSEL(GYRO_CONFIG){
    _250DPS                             =0x00,
    _500DPS                             =0x08,
    _1000DPS                            =0x10,
    _2000DPS                            =0x18,
};

DEFSEL(ACCEL_CONFIG){
    _2G                                 =0x00,
    _4G                                 =0x08,
    _8G                                 =0x10,
    _16G                                =0x18,
};

DEFDAT{
    DLPF_184                =0x01,
    DLPF_92                 =0x02,
    DLPF_41                 =0x03,
    DLPF_20                 =0x04,
    DLPF_10                 =0x05,
    DLPF_5                  =0x06,

    AK8963_I2C_ADDR         =0x0C,
};

namespace HardWare{

    MPU9250::MPU9250(SPI_PIN_Pack):
    SPI_Component(SPI_PIN_Data,SPI_type::IO,{true,true,false}){
        //选择陀螺仪时钟源
        this->Send_Reg(USEREG::PWR_MGMT_1,USESEL(PWR_MGMT_1)::H_RESET);
        SystemClock::Delay(100000);
        this->Send_Reg(USEREG::PWR_MGMT_1,USESEL(PWR_MGMT_1)::ClkSource_l20MHz);
        SystemClock::Delay(100000);

        /**********************Init SLV0 i2c**********************************/ 
        //检测MPU9250出厂ID
        this->Check();
        //设置I2C总线速度为400kHZ
        this->Send_Reg(USEREG::I2C_MST_CTRL,USESEL(I2C_MST_CTRL)::I2C_MST_CLK_400KHz);
        //开启I2C主机模式,并固定为SPI模式
        this->Send_Reg(USEREG::USER_CTRL,USESEL(USER_CTRL)::I2C_MST_EN|USESEL(USER_CTRL)::I2C_IF_DIS);
        //延时使能I2C_SLV0 _DLY_ enable 
        this->Send_Reg(USEREG::I2C_MST_DELAY_CTRL,0x01);
        //enable IIC and EXT_SENS_DATA==1 Byte
        this->Send_Reg(USEREG::I2C_SLV0_CTRL,(USESEL(I2C_SLV0_CTRL)::I2C_SLV_LENG&BIT0)|USESEL(I2C_SLV0_CTRL)::I2C_SLV_GRP|USESEL(I2C_SLV0_CTRL)::I2C_SLV_BYTE_SW);

        ///*******************Init GYRO and ACCEL******************************/ 
        //设置陀螺仪带宽为184Hz
        this->Send_Reg(USEREG::CONFIG,USEDAT::DLPF_184);
        //设置采样分配系数为07
        this->Send_Reg(USEREG::SMPLRT_DIV,0x07);
        //开启加速度计与陀螺仪
        this->Send_Reg(USEREG::PWR_MGMT_2,USESEL(PWR_MGMT_2)::SEN_ENABLE);
        //设置陀螺仪量程为2000DPS作为默认数值
        this->SetGyro_Scale(GyroScale::_2000DPS);
        //设置带宽为184Hz作为默认数值
        this->Send_Reg(USEREG::ACCEL_CONFIG2,USEDAT::DLPF_184);
        //设置加速度量程为16g作为默认数值
        this->SetAccel_Scale(AccelScale::_16G);
        
        /**********************Init MAG **********************************/
        //检测AK8963出厂ID
        this->Check_AK8963();
        /*校准磁力计*/
        this->Send_Reg_AK8963(USEREG::AK8963_CNTL2,USESEL(AK8963_CNTL2)::Reset);
        //设置AK8963至掉电状态
        this->Send_Reg_AK8963(USEREG::AK8963_CNTL1,USESEL(AK8963_CNTL1)::Mode_Power_Down);

        /*********************卡尔曼滤波器初始化**************************/



    }

    void MPU9250::Send_Reg_AK8963(u_char reg,u_char txd){
        //设置从机0为AK8963并设置为写入模式
        this->Send_Reg(USEREG::I2C_SLV0_ADDR,USEDAT::AK8963_I2C_ADDR);
        SystemClock::Delay(100);
        //设置寄存器为期望的AK8963寄存器地址
        this->Send_Reg(USEREG::I2C_SLV0_REG,reg);
        SystemClock::Delay(100);
        //存储需要写入的数据
        this->Send_Reg(USEREG::I2C_SLV0_DO,txd);
        SystemClock::Delay(100);
    }

    void MPU9250::Read_Reg_AK8963(u_char reg,u_char count,u_char *dest){
        //设置从机0为AK8963并设置为读取模式
        this->Send_Reg(USEREG::I2C_SLV0_ADDR, USEDAT::AK8963_I2C_ADDR|BIT7);
        SystemClock::Delay(100);
        //设置寄存器为期望的AK8963寄存器地址
        this->Send_Reg(USEREG::I2C_SLV0_REG,reg);
        SystemClock::Delay(100);
        //启用I2C并请求字节
        this->Send_Reg(USEREG::I2C_SLV0_CTRL,USESEL(I2C_SLV0_CTRL)::I2C_SLV_EN|count);
        //等待寄存器被填充
        SystemClock::Delay(1000);
        //从MPU9250的EXT_SENS_DATA寄存器读出数据
        this->Read_Reg(USEREG::EXT_SENS_DATA_00,count,dest);
    }

    void MPU9250::Check_AK8963(){
        u_char temp=0;
        this->Read_Reg_AK8963(USEREG::AK8963_WHO_AM_I,1,&temp);
        if(temp!=0x48){
            Debug_Warning("AK8963 Check Error! ID="+std::to_string(temp));
        }else{
            Debug_Info("AK8963 Check OK");
        }
    }

    void MPU9250::Check(){
        u_char ID = this->Read_Reg(USEREG::WHO_AM_I);
        if(ID!=0x70){
            Debug_Warning("MPU9250 Check Error! ID="+std::to_string(ID));
        }else{
            Debug_Info("MPU9250 Check OK");
        }
    }

    void MPU9250::RefAccel(){
        u_char Buffer[6];
        this->Read_Reg(USEREG::ACCEL_XOUT_H,6,Buffer);
        for(u_char i=0;i<3;i++){this->Accel_Buffer[i]=((uint16_t)Buffer[i*2]<<8)|Buffer[i*2+1];}
        //角加速度原始值处理过程
        this->Accel_x=this->Accel_Buffer[0]/this->Accel_Scale;
        this->Accel_y=this->Accel_Buffer[1]/this->Accel_Scale;
        this->Accel_z=this->Accel_Buffer[2]/this->Accel_Scale;
        //加速度反正切公式计算三个轴和水平面坐标系之间的夹角
        this->Roll_temp=asin(this->Accel_y)*180/3.14;//(atan(this->Accel_y/this->Accel_z))*180/3.14;
	    this->Pitch_temp=atan2(this->Accel_x,this->Accel_y)*180/3.14;//(atan(this->Accel_y/sqrt(this->Accel_x*this->Accel_x+this->Accel_z*this->Accel_z)))*180/3.14;
        //判断计算后角度的正负号
        // if(this->Accel_Buffer[0]<32764) this->Angle_y_temp = +this->Angle_y_temp;
        // if(this->Accel_Buffer[0]>32764) this->Angle_y_temp = -this->Angle_y_temp;
        // if(this->Accel_Buffer[1]<32764) this->Angle_x_temp = +this->Angle_x_temp;
        // if(this->Accel_Buffer[1]>32764) this->Angle_x_temp = -this->Angle_x_temp;
    }

    void MPU9250::RefGyro(){
        u_char Buffer[6];
        this->Read_Reg(USEREG::GYRO_XOUT_H,6,Buffer);
        for(u_char i=0;i<3;i++){this->Gyro_Buffer[i]=((uint16_t)Buffer[i*2]<<8)|Buffer[i*2+1];}
        //角速度原始值处理过程
        this->Gyro_x=this->Gyro_Buffer[0]/this->Gyro_Scale-this->Gyro_x_Offset;
        this->Gyro_y=this->Gyro_Buffer[1]/this->Gyro_Scale-this->Gyro_y_Offset;
        this->Gyro_z=this->Gyro_Buffer[2]/this->Gyro_Scale-this->Gyro_z_Offset;
    }

    void MPU9250::SetAccel_Scale(AccelScale Scale){
        switch (Scale){
        case AccelScale::_2G:
        this->Send_Reg(USEREG::ACCEL_CONFIG,USESEL(ACCEL_CONFIG)::_2G);
        this->Accel_Scale=65536.0f/4.0f;
        this->Accel_Bottom=-2.0f;
            break;
        case AccelScale::_4G:
        this->Send_Reg(USEREG::ACCEL_CONFIG,USESEL(ACCEL_CONFIG)::_4G);
        this->Accel_Scale=65536.0f/8.0f;
        this->Accel_Bottom=-4.0f;
            break;
        case AccelScale::_8G:
        this->Send_Reg(USEREG::ACCEL_CONFIG,USESEL(ACCEL_CONFIG)::_8G);
        this->Accel_Scale=65536.0f/16.0f;
        this->Accel_Bottom=-8.0f;
            break;
        case AccelScale::_16G:
        this->Send_Reg(USEREG::ACCEL_CONFIG,USESEL(ACCEL_CONFIG)::_16G);
        this->Accel_Scale=65536.0f/32.0f;
        this->Accel_Bottom=-16.0f;
            break;
        }
    }

    void MPU9250::SetGyro_Scale(GyroScale Scale){
        switch (Scale){
        case GyroScale::_250DPS:
        this->Send_Reg(USEREG::GYRO_CONFIG,USESEL(GYRO_CONFIG)::_250DPS);
        this->Gyro_Scale=65536.0f/500.0f;
        this->Gyro_Bottom=-250.0f;
            break;
        case GyroScale::_500DPS:
        this->Send_Reg(USEREG::GYRO_CONFIG,USESEL(GYRO_CONFIG)::_500DPS);
        this->Gyro_Scale=65536.0f/1000.0f;
        this->Gyro_Bottom=-500.0f;
            break;
        case GyroScale::_1000DPS:
        this->Send_Reg(USEREG::GYRO_CONFIG,USESEL(GYRO_CONFIG)::_1000DPS);
        this->Gyro_Scale=65536.0f/2000.0f;
        this->Gyro_Bottom=-1000.0f;
            break;
        case GyroScale::_2000DPS:
        this->Send_Reg(USEREG::GYRO_CONFIG,USESEL(GYRO_CONFIG)::_2000DPS);
        this->Gyro_Scale=65536.0f/4000.0f;
        this->Gyro_Bottom=-2000.0f;
            break;
        }
    }

    void MPU9250::Initialize_Gyro_ZeroDrift(){
        this->RefGyro();
        this->Gyro_x_Offset=this->Gyro_x;
        this->Gyro_y_Offset=this->Gyro_y;
        this->Gyro_z_Offset=this->Gyro_z;
    }

    void MPU9250::RefKalmanFilter(){

    }

}

#endif