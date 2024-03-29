#pragma once
#include"../../AbstractDependency/__AbstractDependency.h"


#ifdef __Enable_PIN


enum class PIN_Status{
    PIN_NULL,
    PIN_Constructed
};

enum class PIN_Mode{
    Fast,
    FastPullUp,
};

namespace std{
    string& to_string(PIN_Mode mode);
}


class PIN
{
private:
    
    PIN_Status PINStatus=PIN_Status::PIN_NULL;
    PIN_Mode PINmode;
    uint32_t GPIOx,PINx;
    

public:
    PIN(uint32_t GPIOx,uint32_t PINx,PIN_Mode PINmode=PIN_Mode::Fast,std::string Info="Nor");
    PIN();

    volatile unsigned long* IN=nullptr;
    volatile unsigned long* OUT=nullptr;
          
    std::function<void(void)> F_ReadMode; 
    std::function<void(void)> F_WriteMode;

    uint32_t GetGPIO();
    uint32_t GetPIN();

    void Construct(uint32_t GPIOx,uint32_t PINx,PIN_Mode PINmode=PIN_Mode::Fast,std::string Info="Nor");
    
    void ReMode(PIN_Mode PINmode);
    ~PIN();
    
    operator bool() {
		return *IN;
	}

	void operator=(unsigned long Index) {
		*OUT = Index;
	}

};

#endif