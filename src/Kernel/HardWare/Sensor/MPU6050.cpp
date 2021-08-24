#include<HardWare/Sensor/Modules/MPU6050.h>
#include<AbstractDependency/_AbstractHardWare.h>
#include<Kernel/HardWare/SystemClock.h>

#if __Enable_PIN&&__Enable_SystemClock

#define MPU_ADDR				0X68
#define MPU_SELF_TESTX_REG		0X0D	//自检寄存器X
#define MPU_SELF_TESTY_REG		0X0E	//自检寄存器Y
#define MPU_SELF_TESTZ_REG		0X0F	//自检寄存器Z
#define MPU_SELF_TESTA_REG		0X10	//自检寄存器A
#define MPU_SAMPLE_RATE_REG		0X19	//采样频率分频器
#define MPU_CFG_REG				0X1A	//配置寄存器
#define MPU_GYRO_CFG_REG		0X1B	//陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG		0X1C	//加速度计配置寄存器
#define MPU_MOTION_DET_REG		0X1F	//运动检测阀值设置寄存器
#define MPU_FIFO_EN_REG			0X23	//FIFO使能寄存器
#define MPU_I2CMST_CTRL_REG		0X24	//IIC主机控制寄存器
#define MPU_I2CSLV0_ADDR_REG	0X25	//IIC从机0器件地址寄存器
#define MPU_I2CSLV0_REG			0X26	//IIC从机0数据地址寄存器
#define MPU_I2CSLV0_CTRL_REG	0X27	//IIC从机0控制寄存器
#define MPU_I2CSLV1_ADDR_REG	0X28	//IIC从机1器件地址寄存器
#define MPU_I2CSLV1_REG			0X29	//IIC从机1数据地址寄存器
#define MPU_I2CSLV1_CTRL_REG	0X2A	//IIC从机1控制寄存器
#define MPU_I2CSLV2_ADDR_REG	0X2B	//IIC从机2器件地址寄存器
#define MPU_I2CSLV2_REG			0X2C	//IIC从机2数据地址寄存器
#define MPU_I2CSLV2_CTRL_REG	0X2D	//IIC从机2控制寄存器
#define MPU_I2CSLV3_ADDR_REG	0X2E	//IIC从机3器件地址寄存器
#define MPU_I2CSLV3_REG			0X2F	//IIC从机3数据地址寄存器
#define MPU_I2CSLV3_CTRL_REG	0X30	//IIC从机3控制寄存器
#define MPU_I2CSLV4_ADDR_REG	0X31	//IIC从机4器件地址寄存器
#define MPU_I2CSLV4_REG			0X32	//IIC从机4数据地址寄存器
#define MPU_I2CSLV4_DO_REG		0X33	//IIC从机4写数据寄存器
#define MPU_I2CSLV4_CTRL_REG	0X34	//IIC从机4控制寄存器
#define MPU_I2CSLV4_DI_REG		0X35	//IIC从机4读数据寄存器

#define MPU_I2CMST_STA_REG		0X36	//IIC主机状态寄存器
#define MPU_INTBP_CFG_REG		0X37	//中断/旁路设置寄存器
#define MPU_INT_EN_REG			0X38	//中断使能寄存器
#define MPU_INT_STA_REG			0X3A	//中断状态寄存器

#define MPU_ACCEL_XOUTH_REG		0X3B	//加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG		0X3C	//加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG		0X3D	//加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG		0X3E	//加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG		0X3F	//加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG		0X40	//加速度值,Z轴低8位寄存器

#define MPU_TEMP_OUTH_REG		0X41	//温度值高八位寄存器
#define MPU_TEMP_OUTL_REG		0X42	//温度值低8位寄存器

#define MPU_GYRO_XOUTH_REG		0X43	//陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG		0X44	//陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG		0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG		0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG		0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG		0X48	//陀螺仪值,Z轴低8位寄存器

#define MPU_I2CSLV0_DO_REG		0X63	//IIC从机0数据寄存器
#define MPU_I2CSLV1_DO_REG		0X64	//IIC从机1数据寄存器
#define MPU_I2CSLV2_DO_REG		0X65	//IIC从机2数据寄存器
#define MPU_I2CSLV3_DO_REG		0X66	//IIC从机3数据寄存器

#define MPU_I2CMST_DELAY_REG	0X67	//IIC主机延时管理寄存器
#define MPU_SIGPATH_RST_REG		0X68	//信号通道复位寄存器
#define MPU_MDETECT_CTRL_REG	0X69	//运动检测控制寄存器
#define MPU_USER_CTRL_REG		0X6A	//用户控制寄存器
#define MPU_PWR_MGMT1_REG		0X6B	//电源管理寄存器1
#define MPU_PWR_MGMT2_REG		0X6C	//电源管理寄存器2 
#define MPU_FIFO_CNTH_REG		0X72	//FIFO计数寄存器高八位
#define MPU_FIFO_CNTL_REG		0X73	//FIFO计数寄存器低八位
#define MPU_FIFO_RW_REG			0X74	//FIFO读写寄存器
#define MPU_DEVICE_ID_REG		0X75	//器件ID寄存器


namespace HardWare{

    MPU6050::MPU6050(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx):I2C_Component(SDA_GPIOx,SDA_PINx,SCL_GPIOx,SCL_PINx){
        Debug_StartBlock("Init");
        this->address=MPU_ADDR;
        this->Send_Reg(MPU_PWR_MGMT1_REG,0x80);
        SystemClock::Delay(100000);
        this->WeakUp();                                 //解除休眠状态
        this->Set_Rate(125);                            //设置采样率,125hz
        this->Set_LPF(6);                               //低通滤波频率，典型值：0x06(5Hz)
        this->Set_Gyro_Fsr(Gyro_Fsr::Fsr_2000dps);      //陀螺仪传感器,±2000dps
        this->Set_Accel_Fsr(Accel_Fsr::Fsr_2g);         //加速度传感器,±2g
        
        //this->Send_Reg(MPU_INT_EN_REG,0X00);	        //关闭所有中断
        //this->Send_Reg(MPU_USER_CTRL_REG,0X00);	        //I2C主模式关闭
        //this->Send_Reg(MPU_FIFO_EN_REG,0X00);	        //关闭FIFO
        //this->Send_Reg(MPU_INTBP_CFG_REG,0X80);	        //INT引脚低电平有效
        
        this->ID_Check();
        
    }

    //设置MPU6050陀螺仪传感器满量程范围
    void MPU6050::Set_Gyro_Fsr(Gyro_Fsr Fsr){
        u_char reg=(u_char)Fsr;
        uint32_t timeout=0;
        do{
            this->Send_Reg(MPU_GYRO_CFG_REG,reg);
            reg=this->Read_Reg(MPU_GYRO_CFG_REG);
        }while(reg!=(u_char)Fsr&&++timeout<=1000);
        if(timeout>=1000){
            Debug_Warning("Gyro_Fsr Timeout");
        }else{
            Debug_Info("Gyro_Fsr OK!");
        }      
    }
    //设置MPU6050加速度传感器满量程范围
    void MPU6050::Set_Accel_Fsr(Accel_Fsr Fsr){
        u_char reg=(u_char)Fsr;
        uint32_t timeout=0;
        do{
            this->Send_Reg(MPU_ACCEL_CFG_REG,reg);
            reg=this->Read_Reg(MPU_ACCEL_CFG_REG);
        }while(reg!=(u_char)Fsr&&++timeout<=1000);
        if(timeout>=1000){
            Debug_Warning("Accel_Fsr Timeout");
        }else{
            Debug_Info("Accel_Fsr OK!");
        } 
    }
    //设置MPU6050的数字低通滤波器
    void MPU6050::Set_LPF(u_short Lpf){
        u_char data=0;
        if(Lpf>=188)data=1;
        else if(Lpf>=98)data=2;
        else if(Lpf>=42)data=3;
        else if(Lpf>=20)data=4;
        else if(Lpf>=10)data=5;
        else data=6; 
        u_char reg=data;
        uint32_t timeout=0;
        do{
            this->Send_Reg(MPU_CFG_REG,reg);
            reg=this->Read_Reg(MPU_CFG_REG);
        }while(reg!=data&&++timeout<=1000);
        if(timeout>=1000){
            Debug_Warning("LPF Timeout");
        }else{
            Debug_Info("LPF OK!");
        }        
    }

    //设置MPU6050的采样率(4~1000)
    void MPU6050::Set_Rate(u_short Rate){
        u_char data;
        if(Rate>1000)Rate=1000;
        if(Rate<4)Rate=4;
        data=1000/Rate-1;
        u_char reg=data;
        uint32_t timeout=0;
        do{
            this->Send_Reg(MPU_SAMPLE_RATE_REG,reg);
            reg=this->Read_Reg(MPU_SAMPLE_RATE_REG);
        }while(reg!=data&&++timeout<=1000);
        if(timeout>=1000){
            Debug_Warning("Rate Timeout");
        }else{
            Debug_Info("Rate OK!");
        } 
    }



    void MPU6050::Refresh_Temperature(){
        u_char buf[2]={0}; 
        if(this->Read_Len(MPU_TEMP_OUTH_REG,2,buf)){
            Debug_Warning("Refresh_Temperature Timeout");
            return;
        }else{
            Debug_Info("Refresh_Temperature OK!");
        } 
        short raw;
        raw=((uint16_t)buf[0]<<8)|buf[1];  
        this->Temperature=(36.53+((double)raw)/340)*100;  
    }

    void MPU6050::Refresh_Gyroscope(){
        u_char buf[6]={0};  
        if(this->Read_Len(MPU_GYRO_XOUTH_REG,6,buf)){
            Debug_Warning("Refresh_Gyroscope Timeout");
            return;
        }else{
            Debug_Info("Refresh_Gyroscope OK!");
        }
        this->Gyroscope_Pack.gx=((uint16_t)buf[0]<<8)|buf[1];  
        this->Gyroscope_Pack.gy=((uint16_t)buf[2]<<8)|buf[3];  
        this->Gyroscope_Pack.gz=((uint16_t)buf[4]<<8)|buf[5];
        
    }

    void MPU6050::Refresh_Accelerometer(){
        u_char buf[6]={0};  
        if(this->Read_Len(MPU_ACCEL_XOUTH_REG,6,buf)){
            Debug_Warning("Refresh_Accelerometer Timeout");
            return;
        }else{
            Debug_Info("Refresh_Accelerometer OK!");
        }
        this->Accelerometer_Pack.ax=((uint16_t)buf[0]<<8)|buf[1];  
        this->Accelerometer_Pack.ay=((uint16_t)buf[2]<<8)|buf[3]; 
        this->Accelerometer_Pack.az=((uint16_t)buf[4]<<8)|buf[5];
    }


    void MPU6050::Refresh(uint32_t Div){
        if(++this->Cnt==Div){
            this->Refresh_Accelerometer();
            this->Refresh_Gyroscope();
            this->Refresh_Temperature();
            this->Cnt=0;
        }
    }

    void MPU6050::Refresh_KalmanFilter(uint32_t Div){

    }

    void MPU6050::WeakUp(){
        u_char reg=0x00;
        uint32_t timeout=0;
        do{
            this->Send_Reg(MPU_PWR_MGMT1_REG,reg);
            reg=this->Read_Reg(MPU_PWR_MGMT1_REG);
        }while(reg!=0x00&&++timeout<=1000);
        if(timeout>=1000){
            Debug_Warning("WeakUp Timeout");
        }else{
            Debug_Info("WeakUp OK!");
        }  
        this->Send_Reg(MPU_PWR_MGMT1_REG,0X00);
    }

    void MPU6050::ID_Check(){
        u_char res=this->Read_Reg(MPU_DEVICE_ID_REG); 
        if(res==this->address){
            Debug_Info("ID_Check OK!");
            Debug_EndOK();
        }else{
            Debug_Warning("ID="+std::to_string(res)+" Normal=104");
            Debug_EndFAIL();
        }
    }
}

#endif