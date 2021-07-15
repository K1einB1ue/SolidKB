#pragma once
#include<AbstractDependency/__AbstractDependency.h>
#include<Abstract/IOAbstract.h>

class Peripheral_UART{
    private:
    std::function<void(char)>* Callback=nullptr;
    public:

    uint32_t Bound;
    uint32_t Uartx;

    Peripheral_UART(uint32_t Uartx,uint32_t Bound);
    virtual ~Peripheral_UART();
    void BindCallback(std::function<void(char)> Callback);

    //用于提前绑定函数
    void Enable();
    void Open();
    void Close();

    void DefaultSend(std::string Info,unsigned int *ptr);
    void DefaultSend(std::string Info);
    virtual void NonReciveSend(std::string Info,unsigned int *ptr);
    virtual void Send(std::string Info,unsigned int *ptr);
    virtual void NonReciveSend(std::string Info);
    virtual void Send(std::string Info);

    
};

template<typename DataType, unsigned int Capacity>
class DecoderContainer{
    private:
    DataType Data[Capacity];
    unsigned int Size = 0;
    const unsigned int capacity = Capacity;
    bool clear_on_end_enable = true;
    std::function<void( DataType*, unsigned int)> decoder_Func = nullptr;


    const DataType* match_data; unsigned int match_size;
    public:

    void StreamIn(DataType index) {
        this->Data[Size++] = index;
        if(Size<match_size){
            return;
        }
        unsigned int i;
        for (i = 0; i < match_size; i++) {
            if (match_data[i] != Data[Size - match_size + i]) {
                break;
            }
        }
        if (i >= match_size && this->decoder_Func) {
            this->decoder_Func(this->Data, this->Size);
            if (clear_on_end_enable) {
                this->Size = 0;
            }
        }
    }

    void End(const char* str, unsigned int size) {
        this->match_data = str;
        this->match_size = size;
    }

    void End_Decoder(std::function<void(DataType*,unsigned int)> decoder_Func) {
        this->decoder_Func = decoder_Func;
    }

    void End_Clear(bool enable) {
        this->clear_on_end_enable = enable;
    }

};



class IO_Uart:public Peripheral_UART,public IOAbstract{//暂时废弃
    public:
    IO_Uart(uint32_t Uartx,uint32_t Bound);
    virtual ~IO_Uart();

    protected:
};