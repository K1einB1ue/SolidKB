#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"

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

    void DefaultSend(const std::string &Info,unsigned int *ptr);
    void DefaultSend(const std::string &Info);
    virtual void NonReciveSend(const std::string &Info,unsigned int *ptr);
    virtual void Send(const std::string &Info,unsigned int *ptr);
    virtual void NonReciveSend(const std::string &Info);
    virtual void Send(const std::string &Info);

    
};

template<typename DataType>
class DecoderContainer{
    private:
    DataType* Data=nullptr;
    unsigned int Size = 0;
    const unsigned int capacity = 0;
    bool clear_on_end_enable = true;
    std::function<void( DataType*, unsigned int)> decoder_Func = nullptr;


    const DataType* match_data; unsigned int match_size;
    public:

    DecoderContainer(){}

    virtual ~DecoderContainer(){
        delete[] Data;
    }

    void StreamIn(DataType index) {
        if(Size>capacity){
            this->Size = 0;
        }
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

    void Set_Container_Size(unsigned int Size){
        delete[] Data;
        Data=new DataType[Size];
        unsigned int* temp = const_cast<unsigned int *>(&capacity);
        *temp = Size;
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


namespace DecoderPipes{
    class Pipe{
        private:
        DecoderPipeline* m_root;
        public:
        Pipe(DecoderPipeline* root):m_root(root) {}
        virtual void StreamIn(u_char index){}
        virtual void onEnable(){}
        void enableNextPipe(u_int32_t index){
            m_route.m_towards[index]->onEnable();
        }
        void releaseThisPipe(){
            m_root->m_activedPipes.erase(this);
        }
        void enableThisPipe(){
            m_root->m_activedPipes.insert(this);
        }
        PipeRoute m_route;
    };
    //作用:激活一段Pipe(如果没有Pattern_Pipe 则一段管道默认激活)
    class Pattern_Pipe:Pipe{
        u_char* pattern;
    };

    class LenGetter_Pipe:Pipe{
        private:
        u_int32_t lenByte_Size,lenByte_Ptr=0,stringByte_Size=0,stringByte_Ptr=0;
        std::string stringBytes;
        public:
        LenGetter_Pipe(u_int32_t lenByte_Size,DecoderPipeline* root):Pipe(root){
            lenByte_Size=lenByte_Size;
        }

        virtual void StreamIn(u_char index){
            if(lenByte_Ptr++<lenByte_Size){
                stringByte_Size<<=8;
                stringByte_Size|=index;
            }else if(stringByte_Ptr++<stringByte_Size){
                stringBytes+=index;
            }else{
                this->enableNextPipe(0);
                this->releaseThisPipe();
            }
        }

        virtual void onEnable(){
            this->enableThisPipe();
            lenByte_Ptr=0;
            stringByte_Size=0;
            stringByte_Ptr=0;
            stringBytes.clear();
        }
    };

    //作用:第一次通过时执行对应函数,第二次通过时停止执行对应函数.
    class Gate_Pipe:Pipe{
        private:
        bool pipeEnable=false;
        public:

        std::function<void(u_char)> StreamCallback=nullptr;
        virtual void StreamIn(u_char index){
            if(StreamCallback){
                StreamCallback(index);
            }
        }

        virtual void onEnable(){
            if(pipeEnable){
                this->releaseThisPipe();
                pipeEnable=false;
            }else{
                this->enableThisPipe();
                pipeEnable=true;
            }
            this->enableNextPipe(0);
        }
    };

    class PipeRoute{
        public:
        std::vector<Pipe*> m_towards;
    };
} 

class DecoderPipeline{
    friend class DecoderPipes::Pipe;
    private:
    std::vector<DecoderPipes::Pipe> m_pipes;
    std::set<DecoderPipes::Pipe*> m_activedPipes;
    public:
    //TODO:有潜在的被抢中断的可能性!!是中断不安全的!!!尽可能保持少的计算量.
    void StreamIn(u_char index) {
        for(auto item : m_activedPipes){
            item->StreamIn(index);
        }
    }
};