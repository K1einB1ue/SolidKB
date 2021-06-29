#include<HardWare/SYN6288.h>
#include<AbstractDependency/_AbstractHardWare.h>


std::string& convertUTF8ToUnicode(const std::string Info)
{
    static std::string Data;
    Data.clear();
    for(unsigned int i=0;i<Info.size()/3;i++){
        Data+=((Info[i*3]&0xF)<<4)+((Info[i*3+1]>>2)&0xF);
        Data+=((Info[i*3+1]&0x3)<<6)+(Info[i*3+2]&0x3F);
    }
    return Data;
}


std::string& SYNDataFrame(const std::string Data)
{
    static std::string Pack;
    u_char XORCheck = 0;
    Pack.clear();

    Pack+=(char)0xFD;                           //帧头
    Pack+=(char)0x00;                           //数据区长度的高字节:
    Pack+=(char)(Data.size()+3);                //数据区长度的低字节：   长度=1(命令字)+1(命令参数)+文本长度+1(异或校验)

    Pack+=0x01;                                 //命令:0x04 恢复合成命令. 0x21 芯片状态查询命令. 0x88 芯片进入睡眠模式.

    u_char Music=0x00;                          //命令参数:0x00 设置 GB2312 编码格式. 0x01 GBK. 0x02 BIG5. 0x03 UNICODE.
    Pack+=(char)(0x03|(Music<<3));              //编码格式对应的是低3位, 音乐对应的是高5位.


    for(unsigned int i=0;i<5;i++){
        XORCheck = XORCheck^(Pack[i]);          //对前五个字节进行异或校验。
    }
    for(unsigned int i=0;i<Data.size();i++){
        Pack+=Data[i];
        XORCheck = XORCheck^Data[i];            //对文本字节进行异或校验。
    }
    Pack+=(char)XORCheck;

    return Pack;
}


namespace HardWare{
    SYN6288::SYN6288(uint32_t Usartx):Usart(Usartx,9600){
        this->Enable();
    }
    //已经内置了UTF-8到Unicode编码的转换.
    void SYN6288::Send(std::string Info){
        this->Close();
        Override::Usart_Send(this,SYNDataFrame(convertUTF8ToUnicode(Info)));
        this->Open();
    }


    //已经内置了UTF-8到Unicode编码的转换.
    void SYN6288::NonReciveSend(std::string Info){
        this->Close();
        Override::Usart_Send(this,SYNDataFrame(convertUTF8ToUnicode(Info)));
    }


    void SYN6288::NoUTF8_Send(std::string Info){
        this->Close();
        Override::Usart_Send(this,Info);
        this->Open();
    }
    void SYN6288::NoUTF8_NonReciveSend(std::string Info){
        this->Close();
        Override::Usart_Send(this,Info);
    }
}