#include"./SSD1306.h"

enum class SSD1306_CMD : u_char{
    OLED_Address1           =0x78,//OLED地址1
    OLED_Address2           =0x79,//OLED地址2
    OLED_Sin_CMD            =0x00,//接下来发送的都是命令
    OLED_Con_CMD            =0x80,//接下来发送的一个字节是命令
    OLED_Sin_DAT            =0x40,//接下来发送的都是数据
    OLED_Con_DAT            =0xC0,//接下来发送的一个字节是数据

    //命令:设置对比度.
    //=Byte<0x00~0xFF>
    CMD_CFG_Contrast        =0x81,

    //命令:设置复用率,复用率指选通的COM行数.
    //=Bit[5:0]<0x0F~0x3F>.
    CMD_CFG_N               =0xA8,

    //命令:设置垂直显示偏移,垂直显示偏移是指整个屏幕向上移动的行数,是环绕显示的不会被剔除.
    //=Bit[5:0]<0x0F~0x3F>
    CMD_CFG_VertOffset      =0xD3,
    
    //命令:设置显示时钟分频数,振荡器频率.
    //=Bit[7:0]
    //| [7:4]:振荡频率
    //| [3:0]+1:分频数
    CMD_CFG_DIV             =0xD5,
    
    //命令:设置预充电周期.
    //=Bit[7:0]
    CMD_CFG_PreCharge       =0xD9,

    //命令:设置COM硬件配置.
    //=Bit[5:4]
    //| [5]:设置COM左右反置
    //| [4]:设置序列/备选管教配置
    CMD_CFG_Hardware        =0xDA,

    //命令:设置V.comh输出的高电平.
    //+Bit[6:4]
    CMD_CFG_Vcomh           =0xDB,
    //命令:设置GDDRAM寻址模式.
    //=Enum<0x00/0x01/0x02>
    //| 0x00:水平寻址   {电视机的扫描模式,自动移动指针}	
    //| 0x01:垂直寻址   {电视机的扫描模式改为从向下扫描开始,自动移动指针}
    //| 0x02:页寻址     {从左扫到右,不会换行,自动移动指针}
    CMD_CFG_ScanMode        =0x20,

    //命令:设置Charge Pump enable/disable
    //=Enum<0x10/0x14>
    //| 0x10:关闭
    //| 0x14:开启
    CMD_CFG_ChargePump      =0x8D,

    //命令:设置列起始和结束地址.
    //=Byte<0x00~0xff>
    //| 列起始地址
    //=Byte<0x00~0xff>
    //| 列终止地址
    CMD_CFG_Column          =0x21,

    //命令:设置页起始和结束地址.
    //=Byte<0x00~0xff>
    //| 页起始地址
    //=Byte<0x00~0xff>
    //| 页终止地址
    CMD_CFG_Page            =0x22,
   
    CMD_Close               =0xAE,//命令:关闭OLED显示
    CMD_Open                =0xAF,//命令:打开OLED显示
    CMD_Mapping_COL0        =0xA1,//命令:设置GDDRAM的COL0映射到驱动器输出SEG0.
    CMD_Mapping_COL127      =0xA2,//命令:设置GDDRAM的COL127映射到SEG0.
    CMD_ScanForm_COM0       =0xC0,//命令:设置从COM0扫描到COM[N-1],N为复用率.
    CMD_ScanForm_COMN1      =0xC8,//命令:设置从COM[N-1]扫描到COM0,N为复用率.
    CMD_1_Light             =0xA6,//命令:设置显示模式为1亮0灭.
    CMD_0_Light             =0xA7,//命令:设置显示模式为0亮1灭.
    CMD_ALL_Light           =0xA5,//命令:设置显示模式为全亮模式,此时屏幕无视GDDRAM中的数据,并点亮全屏.
    CMD_Normal_Light        =0xA4,//命令:设置显示模式为正常模式,此时屏幕输出GDDRAM中的显示数据.

    //命令:
    //| <0x00~0x0F>:Bit[4:0]设置起始列地址低位.(用于页寻址模式)
    //| <0x10~0x1F>:Bit[4:0]设置起始列地址高位.(用于页寻址模式)

    //命令:
    //| Enum<0x40~0x7F>:设置GDDRAM起始行对应0~63
};

static std::vector<u_char> OledInitPack{
    (u_char)SSD1306_CMD::OLED_Address1,
    (u_char)SSD1306_CMD::CMD_Close,
    0x00,//| <0x00~0x0F>:Bit[4:0]设置起始列地址低位.(用于页寻址模式)
    0x10,//| <0x10~0x1F>:Bit[4:0]设置起始列地址高位.(用于页寻址模式)
    0x40,//| Enum<0x40~0x7F>:设置GDDRAM起始行对应0~63
    (u_char)SSD1306_CMD::CMD_CFG_Contrast,
    0xCF,
    (u_char)SSD1306_CMD::CMD_Mapping_COL0,
    (u_char)SSD1306_CMD::CMD_ScanForm_COMN1,
    (u_char)SSD1306_CMD::CMD_CFG_N,
    0x3F,
    (u_char)SSD1306_CMD::CMD_CFG_VertOffset,
    0x00,
    (u_char)SSD1306_CMD::CMD_CFG_DIV,
    0x80,//| 设置时钟为100帧/秒.
    (u_char)SSD1306_CMD::CMD_CFG_PreCharge,
    0xF1,
    (u_char)SSD1306_CMD::CMD_CFG_Hardware,
    0x12,
    (u_char)SSD1306_CMD::CMD_CFG_Vcomh,
    0x40,
    (u_char)SSD1306_CMD::CMD_CFG_ScanMode,
    0x02,
    (u_char)SSD1306_CMD::CMD_CFG_ChargePump,
    0x14,
    (u_char)SSD1306_CMD::CMD_1_Light,
    (u_char)SSD1306_CMD::CMD_Open,
};

static std::vector<u_char> OledFramePack{
    (u_char)SSD1306_CMD::OLED_Address1,
    (u_char)SSD1306_CMD::OLED_Sin_DAT,
    (u_char)SSD1306_CMD::CMD_CFG_ScanMode,
    0x00,

    (u_char)SSD1306_CMD::CMD_CFG_Column,
    0x00,//| 列起始地址 0
    0x7F,//| 列终止地址 127

    (u_char)SSD1306_CMD::CMD_CFG_Page,
    0x00,//| 页起始地址 0
    0x07,//| 页终止地址 7
};


#if __Enable_PIN

namespace HardWare{
    SSD1306::SSD1306(uint32_t SDA_GPIOx,uint32_t SDA_PINx,uint32_t SCL_GPIOx,uint32_t SCL_PINx):I2C_Component(SDA_GPIOx,SDA_PINx,SCL_GPIOx,SCL_PINx){}
    void SSD1306::Open(){
        this->CMDs.push(CMD::ToOpen);
        this->Refresh();
    }
    void SSD1306::Close(){
        this->CMDs.push(CMD::ToClose);
    }
    SSD1306::~SSD1306(){}
    void SSD1306::Refresh(){}
}

#endif

#if __Enable_PIN&&__Enable_SystemClock
namespace I2C{

    SSD1306::SSD1306(
    uint32_t SDA_GPIOx,uint32_t SDA_PINx,
    uint32_t SCL_GPIOx,uint32_t SCL_PINx):
    HardWare::SSD1306(SDA_GPIOx,SDA_PINx,SCL_GPIOx,SCL_PINx){
        this->Start();
        for(unsigned int i=0;i<OledInitPack.size();i++){
            this->Send_Byte(OledInitPack[i]);
            this->Fast_Ack();
        }
        this->Stop();

        bool* on = const_cast<bool*>(&ON);
        *on=true;

        __GraphicInit(128,64);
    }

    void SSD1306::Refresh(){
        for(unsigned int i=0;i<this->Screen_Pixel_Height;i++){
            this->Start();
            this->Send_Byte((u_char)SSD1306_CMD::OLED_Address1);
            this->Fast_Ack();
            this->Send_Byte((u_char)SSD1306_CMD::OLED_Sin_CMD);
            this->Fast_Ack();
            this->Send_Byte(0xb0+i);    //设置行起始地址
            this->Fast_Ack();
            this->Send_Byte(0x00);      //设置低列起始地址
            this->Fast_Ack();
            this->Send_Byte(0x10);      //设置高列起始地址
            this->Fast_Ack();
            this->Stop();


            this->Start();
            this->Send_Byte((u_char)SSD1306_CMD::OLED_Address1);
            this->Fast_Ack();
            this->Send_Byte((u_char)SSD1306_CMD::OLED_Sin_DAT);
            this->Fast_Ack();
            
            u_char byte;
            for(unsigned int j=0;j<this->Screen_Pixel_Width;j++){  
                byte=0;
                for(unsigned char z=0;z<8;z++){
                    byte<<=1;
                    if(this->canvas->GetRenderColor(i,j).Byte)byte++;
                }
                this->Send_Byte(byte);
                this->Fast_Ack();
            }
            
            this->Stop();
        }
    }


    SSD1306::~SSD1306(){}


}
#endif
#if __Enable_PIN
namespace SPI{


    SSD1306::SSD1306(
    uint32_t SDA_GPIOx,uint32_t SDA_PINx,
    uint32_t SCL_GPIOx,uint32_t SCL_PINx,
    uint32_t RES_GPIOx,uint32_t RES_PINx,
    uint32_t DC_GPIOx,uint32_t DC_PINx,
    uint32_t CS_GPIOx,uint32_t CS_PINx):
    HardWare::SSD1306(SDA_GPIOx,SDA_PINx,SCL_GPIOx,SCL_PINx),
    RES(RES_GPIOx,RES_PINx,PIN_Mode::Fast),
    DC(DC_GPIOx,DC_PINx,PIN_Mode::Fast),
    CS(CS_GPIOx,CS_PINx,PIN_Mode::Fast){
        
        RES=0;
        SystemClock::Delay(15000);
        RES=1;
        
        SSD1306_Cmd(0xAE);
        SSD1306_Cmd(0x00);
        SSD1306_Cmd(0x10);
        SSD1306_Cmd(0x40);
        SSD1306_Cmd(0x81);
        SSD1306_Cmd(0xCF);
        SSD1306_Cmd(0xA1);
        SSD1306_Cmd(0xC8);
        SSD1306_Cmd(0xA6);
        SSD1306_Cmd(0xA8);
        SSD1306_Cmd(0x3F);
        SSD1306_Cmd(0xD3);
        SSD1306_Cmd(0x00);
        SSD1306_Cmd(0xD5);
        SSD1306_Cmd(0x80);
        SSD1306_Cmd(0xD9);
        SSD1306_Cmd(0xF1);
        SSD1306_Cmd(0xDA);
        SSD1306_Cmd(0x12);
        SSD1306_Cmd(0xDB);
        SSD1306_Cmd(0x40);
        SSD1306_Cmd(0x20);
        SSD1306_Cmd(0x02);
        SSD1306_Cmd(0x8D);
        SSD1306_Cmd(0x14);
        SSD1306_Cmd(0xA4);
        SSD1306_Cmd(0xA6);
        SSD1306_Cmd(0xAF);

        bool* on = const_cast<bool*>(&ON);
        *on=true;
        
        __GraphicInit(128,64);
        this->canvas=new SolidGL::Components::Canvas<SolidGL::Draw::Bit>(128,64);
    }

    void SSD1306::Refresh(){
        
        for(uint i=0;i<this->Screen_Pixel_Height/8;i++){
            SSD1306_Cmd(0xB0+i);
            SSD1306_Cmd(0x00);
            SSD1306_Cmd(0x10);
            
            u_char byte;
            for(uint n=0;n<this->Screen_Pixel_Width;n++){
                byte=0;
                for(int z=7;z>=0;z--){
                    byte<<=1;
                    if(this->canvas->GetRenderColor(n,i*8+z).Byte)byte++;
                }
                this->SSD1306_Dat(byte);
            }
        }

        while(!this->CMDs.empty()){
            bool* on = const_cast<bool*>(&ON);
            switch (CMDs.top()){
            case CMD::ToOpen:

                SSD1306_Cmd(0x8D);//电荷泵使能
                SSD1306_Cmd(0x14);//开启电荷泵
                SSD1306_Cmd(0xAF);//点亮屏幕
                *on=true;

            break;
            case CMD::ToClose:

                SSD1306_Cmd(0x8D);//电荷泵使能
                SSD1306_Cmd(0x10);//关闭电荷泵
                SSD1306_Cmd(0xAF);//关闭屏幕
                *on=false;

            break;
            default:
            break;
            } 
            CMDs.pop();
        }
    }
    void SSD1306::SSD1306_Dat(u_char txd){
        DC=1;CS=0;
        for(u_char i=0;i<8;i++){
            SCL=0;
            if(txd&0x80) SDA=1;
            else SDA=0;
            SCL=1;
            txd<<=1; 
        }
        CS=1;DC=1;
    }
    void SSD1306::SSD1306_Cmd(u_char txd){
        DC=0;CS=0;
        for(u_char i=0;i<8;i++){
            SCL=0;
            if(txd&0x80) SDA=1;
            else SDA=0;
            SCL=1;
            txd<<=1; 
        }
        CS=1;DC=1;
    }

    SSD1306::~SSD1306(){}

}

#endif