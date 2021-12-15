#include"./ST7735.h"

#if __Enable_PIN&&__Enable_SystemClock

DEFCMD{
    /*[空指令]<0><0>*/
    NOP                 =0x00,
    /*[软件复位]<0><0>需要等待5ms(在非休眠模式下,否则需要在120ms前发送退出休眠命令),并加载所有出场寄存器设置,帧内存不受影响.*/
    SWRESET             =0x01,
    /*[读取设备ID]<0><0>返回3字节长度的设备ID(详见手册9.1.3).*/
    RDDID               =0x04,
    /*[读取显示状态]<0><3Byte>
    -<7>        BSTON       {升压}[On|Off]
    -<6>        MY          {Y轴}[下到上|上到下]
    -<5>        MX          {X轴}[右到左|左到右]
    -<4>        MV          {行列}[互换|正常]
    -<3>        ML          {扫描刷新方向}[下到上|上到下]
    -<2>        RGB         [BGR|RGB]
    -<1>        MH          {扫描刷新方向}[右到左|左到右]
    +<0>        ST24        [Reversed]
    -<7>        ST23        [Reversed]
    -<6:4[1]>   IFPF      {像素大小}[0][1][1]=>12bits/pixel,[1][0][1]=>16bits/pixel,[1][1][0]=>18bits/pixel
    -<3>        IDMON       {闲置模式}[On|Off]
    -<2>        PTLON       {局部模式}[On|Off]
    -<1>        SLPOUT      {睡眠模式}[Out|In]
    +<0>        NORON       {正常显示}[正常显示|局部显示]
    -<7>        ST15        {垂直滚动}[On|Off](未使用)
    -<6>        ST14        {水平滚动}[On|Off](未使用)
    -<5>        INVON       {倒置,反向}[On|Off]
    -<4>        ST12        {所有像素启用}[0](未使用)
    -<3>        ST11        {所有像素弃用}[0](未使用)
    -<2>        DISON       {启用显示}[On|Off]
    -<1>        TEON        {撕裂线效果?}[On|Off]
    +<0:6[1]>   GCSEL       {伽马曲线选择}[0][0][0]=>GC0,[0][0][1]=>GC1,[0][1][0]=>GC2,[0][1][1]=>GC3
    -<5>        TEM         {撕裂线模式?}[mode2|mode1]
    -<4>        ST4         [0](未使用)            
    -<3>        ST3         [0](未使用)
    -<2>        ST2         [0](未使用)
    -<1>        ST1         [0](未使用)
    -<0>        ST0         [0](未使用)
    */
    RDDST               =0x09,
    /*[弃用显示]<0><0>*/
    DISPOFF             =0x28,
    /*[启用显示]<0><0>*/
    DISPON              =0x29,
    /*[设置X坐标]<*><0>*/
    CASET               =0x2A,
    /*[设置Y坐标]<*><0>*/
    RASET               =0x2B,
    /*[开始帧写入]<*><0>*/
    RAMWR               =0x2C
};  //DEFCMD

namespace HardWare{
    void ST7735::TFTScreen_Dat(u_char txd){
        this->Start();
        DC=1;
        this->Send_Byte(txd);
        this->End();
    }

    void ST7735::TFTScreen_Cmd(u_char txd){
        this->Start();
        DC=0;
        this->Send_Byte(txd);
        this->End();
    }

    ST7735::ST7735(
    uint32_t SCL_GPIOx,uint32_t SCL_PINx,
    uint32_t SDA_GPIOx,uint32_t SDA_PINx,
    uint32_t RES_GPIOx,uint32_t RES_PINx,
    uint32_t DC_GPIOx,uint32_t DC_PINx,
    uint32_t CS_GPIOx,uint32_t CS_PINx,
    uint32_t BLK_GPIOx,uint32_t BLK_PINx
    ):SPI_Component(SDA_GPIOx,SDA_PINx,0,0,SCL_GPIOx,SCL_PINx,CS_GPIOx,CS_PINx,SPI_type::O,{true,true,false}),
    RES(RES_GPIOx,RES_PINx,PIN_Mode::Fast,"RES"),
    DC(DC_GPIOx,DC_PINx,PIN_Mode::Fast,"DC"),
    BLK(BLK_GPIOx,BLK_PINx,PIN_Mode::Fast,"BLK"){
        RES.F_WriteMode();
        DC.F_WriteMode();
        BLK.F_WriteMode();
       
        RES=0;
        SystemClock::Delay(100000);
        RES=1;
        SystemClock::Delay(100000);
        TFTScreen_Cmd(0x11);//Sleep exit
        SystemClock::Delay(120000);
        
        /*
        TFTScreen_Cmd(0x36);    //MADCTL
        TFTScreen_Dat(0x00);    //Byte:MY,MX,MV,ML,RGB,0,0,0

        TFTScreen_Cmd(0x3A);    //COLCTL
        TFTScreen_Dat(0x05);    //Byte:0,D6,D5,D4,0,D2,D1,D0

        TFTScreen_Cmd(0xB2);
        TFTScreen_Dat(0x0C);
        TFTScreen_Dat(0x0C);
        TFTScreen_Dat(0x00);
        TFTScreen_Dat(0x33);
        TFTScreen_Dat(0x33);

        TFTScreen_Cmd(0xB7); 
        TFTScreen_Dat(0x35);  

        TFTScreen_Cmd(0xBB);
        TFTScreen_Dat(0x19);

        TFTScreen_Cmd(0xC0);
        TFTScreen_Dat(0x2C);

        TFTScreen_Cmd(0xC2);
        TFTScreen_Dat(0x01);

        TFTScreen_Cmd(0xC3);
        TFTScreen_Dat(0x12);   

        TFTScreen_Cmd(0xC4);
        TFTScreen_Dat(0x20);  

        TFTScreen_Cmd(0xC6); 
        TFTScreen_Dat(0x0F);    

        TFTScreen_Cmd(0xD0); 
        TFTScreen_Dat(0xA4);
        TFTScreen_Dat(0xA1);

        TFTScreen_Cmd(0xE0);
        TFTScreen_Dat(0xD0);
        TFTScreen_Dat(0x04);
        TFTScreen_Dat(0x0D);
        TFTScreen_Dat(0x11);
        TFTScreen_Dat(0x13);
        TFTScreen_Dat(0x2B);
        TFTScreen_Dat(0x3F);
        TFTScreen_Dat(0x54);
        TFTScreen_Dat(0x4C);
        TFTScreen_Dat(0x18);
        TFTScreen_Dat(0x0D);
        TFTScreen_Dat(0x0B);
        TFTScreen_Dat(0x1F);
        TFTScreen_Dat(0x23);

        TFTScreen_Cmd(0xE1);
        TFTScreen_Dat(0xD0);
        TFTScreen_Dat(0x04);
        TFTScreen_Dat(0x0C);
        TFTScreen_Dat(0x11);
        TFTScreen_Dat(0x13);
        TFTScreen_Dat(0x2C);
        TFTScreen_Dat(0x3F);
        TFTScreen_Dat(0x44);
        TFTScreen_Dat(0x51);
        TFTScreen_Dat(0x2F);
        TFTScreen_Dat(0x1F);
        TFTScreen_Dat(0x1F);
        TFTScreen_Dat(0x20);
        TFTScreen_Dat(0x23);

        TFTScreen_Cmd(0x21); 

        TFTScreen_Cmd(0x11); 
        SystemClock::Delay(200000);

        TFTScreen_Cmd(0x29); 
        */
        
        TFTScreen_Cmd(0x21); 
        TFTScreen_Cmd(0x21); 

        TFTScreen_Cmd(0xB1); 
        TFTScreen_Dat(0x05);
        TFTScreen_Dat(0x3A);
        TFTScreen_Dat(0x3A);

        TFTScreen_Cmd(0xB2);
        TFTScreen_Dat(0x05);
        TFTScreen_Dat(0x3A);
        TFTScreen_Dat(0x3A);

        TFTScreen_Cmd(0xB3); 
        TFTScreen_Dat(0x05);  
        TFTScreen_Dat(0x3A);
        TFTScreen_Dat(0x3A);
        TFTScreen_Dat(0x05);
        TFTScreen_Dat(0x3A);
        TFTScreen_Dat(0x3A);

        TFTScreen_Cmd(0xB4);
        TFTScreen_Dat(0x03);

        TFTScreen_Cmd(0xC0);
        TFTScreen_Dat(0x62);
        TFTScreen_Dat(0x02);
        TFTScreen_Dat(0x04);

        TFTScreen_Cmd(0xC1);
        TFTScreen_Dat(0xC0);

        TFTScreen_Cmd(0xC2);
        TFTScreen_Dat(0x0D);
        TFTScreen_Dat(0x00);

        TFTScreen_Cmd(0xC3);
        TFTScreen_Dat(0x8D);
        TFTScreen_Dat(0x6A);   

        TFTScreen_Cmd(0xC4);
        TFTScreen_Dat(0x8D); 
        TFTScreen_Dat(0xEE); 

        TFTScreen_Cmd(0xC5);  /*VCOM*/
        TFTScreen_Dat(0x0E);    

        TFTScreen_Cmd(0xE0);
        TFTScreen_Dat(0x10);
        TFTScreen_Dat(0x0E);
        TFTScreen_Dat(0x02);
        TFTScreen_Dat(0x03);
        TFTScreen_Dat(0x0E);
        TFTScreen_Dat(0x07);
        TFTScreen_Dat(0x02);
        TFTScreen_Dat(0x07);
        TFTScreen_Dat(0x0A);
        TFTScreen_Dat(0x12);
        TFTScreen_Dat(0x27);
        TFTScreen_Dat(0x37);
        TFTScreen_Dat(0x00);
        TFTScreen_Dat(0x0D);
        TFTScreen_Dat(0x0E);
        TFTScreen_Dat(0x10);

        TFTScreen_Cmd(0xE1);
        TFTScreen_Dat(0x10);
        TFTScreen_Dat(0x0E);
        TFTScreen_Dat(0x03);
        TFTScreen_Dat(0x03);
        TFTScreen_Dat(0x0F);
        TFTScreen_Dat(0x06);
        TFTScreen_Dat(0x02);
        TFTScreen_Dat(0x08);
        TFTScreen_Dat(0x0A);
        TFTScreen_Dat(0x13);
        TFTScreen_Dat(0x26);
        TFTScreen_Dat(0x36);
        TFTScreen_Dat(0x00);
        TFTScreen_Dat(0x0D);
        TFTScreen_Dat(0x0E);
        TFTScreen_Dat(0x10);

        TFTScreen_Cmd(0x3A); 
        TFTScreen_Dat(0x05);

        TFTScreen_Cmd(0x36);
        TFTScreen_Dat(0xA8);

        TFTScreen_Cmd(0x29); 
        BLK=1;
    }

    void ST7735::RecRender(RenderInterface &renderInterface){    
        DC=0;                                                                                                               //CASET
        this->Send_Single(USECMD::CASET);                                                                                   
        DC=1;
        this->Send_Single((u_char)renderInterface.GetAbsoluteTransform().Position.x>>8);                                       //x起始高位
        this->Send_Single((u_char)renderInterface.GetAbsoluteTransform().Position.x&0xFF);                                     //x起始低位
        this->Send_Single((u_char)(renderInterface.GetAbsoluteTransform().Position.x+renderInterface.recSize.x)>>8);           //x结束高位
        this->Send_Single((u_char)(renderInterface.GetAbsoluteTransform().Position.x+renderInterface.recSize.x)&0xFF);         //x结束低位
        DC=0;       
        this->Send_Single(USECMD::RASET);                                                                                      //RASET
        DC=1;       
        this->Send_Single((u_char)renderInterface.GetAbsoluteTransform().Position.y>>8);                                       //y起始高位
        this->Send_Single((u_char)renderInterface.GetAbsoluteTransform().Position.y&0xFF);                                     //y起始低位
        this->Send_Single((u_char)(renderInterface.GetAbsoluteTransform().Position.y+renderInterface.recSize.y+1)>>8);         //y结束高位
        this->Send_Single((u_char)(renderInterface.GetAbsoluteTransform().Position.y+renderInterface.recSize.y+1)&0xFF);	    //y结束低位
        DC=0;       
        this->Send_Single(USECMD::RAMWR);                                                                                      //RAMWR
        DC=1;
        for(uint i=0;i<renderInterface.recSize.x;i++){
            for(uint j=0;j<renderInterface.recSize.y;j++){
                uint16_t temp = renderInterface.GetRenderColor(j,i).Bytes;
                this->Start();
                this->Send_Byte(temp>>8);
                this->Send_Byte(temp);
                this->End();
            }
        }
    }


}

#endif