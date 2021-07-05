#pragma once
#include<AbstractDependency/__AbstractDependency.h>

enum class PIN_Status{
    PIN_NULL,
    IDLE,
    READ,
    WRITE,
};

enum class PIN_Mode{
    Fast,
    FastPullUp,
    AF_DCMI,
};


class PIN
{
private:
    
    PIN_Status PINStatus=PIN_Status::PIN_NULL;
    PIN_Mode PINmode;
    uint32_t GPIOx,PINx;
    static unsigned int GPIO_Enable_Map  [CFG_GPIO_Size];
    static bool PIN_Enable_Map           [CFG_GPIO_Size][CFG_PIN_Size];
    

public:

    PIN(uint32_t GPIOx,uint32_t PINx,PIN_Mode PINmode);

    volatile unsigned long* IN=nullptr;
    volatile unsigned long* OUT=nullptr;
          
    std::function<void(void)> F_ReadMode; 
    std::function<void(void)> F_WriteMode;

    uint32_t GetGPIO();
    uint32_t GetPIN();

    void ReMode(PIN_Mode PINmode);
    ~PIN();

    static bool CoverPIN(uint32_t GPIOx,uint32_t PINx);
    static bool UncoverPIN(uint32_t GPIOx,uint32_t PINx);
    
    operator bool() {
		return *IN;
	}

	void operator=(unsigned long Index) {
		*OUT = Index;
	}

};

