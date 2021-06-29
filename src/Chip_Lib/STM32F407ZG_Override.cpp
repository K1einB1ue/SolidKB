#include<AbstractDependency/_AbstractHardWare.h>
#include<VirtualHardWare.h>

#ifdef STM32F407ZG
    __attribute__((optimize("O0"))) void nop(){}
    extern "C" void SysTick_Handler(void){
        HAL_IncTick();
    }

    volatile unsigned long* IN(uint32_t GPIOx,uint32_t PINx){
        uint32_t addr=0x40020010ul+GPIOx*0x400ul;
        uint32_t INaddr=(addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(PINx<<2);
        return (volatile unsigned long*)INaddr;
    }

    volatile unsigned long* OUT(uint32_t GPIOx,uint32_t PINx){
        uint32_t addr=0x40020014ul+GPIOx*0x400ul;
        uint32_t OUTaddr=(addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(PINx<<2);
        return (volatile unsigned long*)OUTaddr;
    }

    #if __Enable_PIN
        GPIO_TypeDef* GPIO_Mapping[]={GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,GPIOI};
        GPIO_InitTypeDef FastPullUp_Type;
        GPIO_InitTypeDef FastNoPull_Type;

        void PullUpInit(uint32_t GPIOx,uint32_t PINx){
            FastPullUp_Type.Pin=1<<PINx;
            FastPullUp_Type.Mode=GPIO_MODE_OUTPUT_PP;
            FastPullUp_Type.Pull=GPIO_PULLUP;
            FastPullUp_Type.Speed=GPIO_SPEED_FAST;
            HAL_GPIO_Init(GPIO_Mapping[GPIOx],&FastPullUp_Type);
        }
        void NoPullInit(uint32_t GPIOx,uint32_t PINx){
            FastNoPull_Type.Pin=1<<PINx;
            FastNoPull_Type.Mode=GPIO_MODE_OUTPUT_PP;
            FastNoPull_Type.Pull=GPIO_NOPULL;
            FastNoPull_Type.Speed=GPIO_SPEED_FAST;
            HAL_GPIO_Init(GPIO_Mapping[GPIOx],&FastNoPull_Type);
        }
        void PIN_Default(PIN* PIN){

            PIN->IN= IN(PIN->GetGPIO(),PIN->GetPIN());
            PIN->OUT= OUT(PIN->GetGPIO(),PIN->GetPIN());

            GPIO_TypeDef* GPIO_Type=GPIO_Mapping[PIN->GetGPIO()];    

            PIN->F_ReadMode=[=](){
                GPIO_Type->MODER&=~(3<<(PIN->GetPIN()*2));     
            };   

            PIN->F_WriteMode=[=](){
                GPIO_Type->MODER&=~(3<<(PIN->GetPIN()*2));
                GPIO_Type->MODER|=(1<<(PIN->GetPIN()*2));
            };  

        }

        std::map<PIN_Mode,std::function<void(PIN*)>> Override::PINPrototypes{
            {PIN_Mode::Fast,[](PIN* PIN){
                NoPullInit(PIN->GetGPIO(),PIN->GetPIN());
                PIN_Default(PIN);
            }},
            {PIN_Mode::FastPullUp,[](PIN* PIN){               
                PullUpInit(PIN->GetGPIO(),PIN->GetPIN());
                PIN_Default(PIN);
            }},
        };
        
        void Override::GPIOx_PreEnable(uint32_t GPIOx){
            switch(GPIOx){
                case 0:__HAL_RCC_GPIOA_CLK_ENABLE();break;
                case 1:__HAL_RCC_GPIOB_CLK_ENABLE();break;
                case 2:__HAL_RCC_GPIOC_CLK_ENABLE();break;
                case 3:__HAL_RCC_GPIOD_CLK_ENABLE();break;
                case 4:__HAL_RCC_GPIOE_CLK_ENABLE();break;
                case 5:__HAL_RCC_GPIOF_CLK_ENABLE();break;
                case 6:__HAL_RCC_GPIOG_CLK_ENABLE();break;
                case 7:__HAL_RCC_GPIOH_CLK_ENABLE();break;
                case 8:__HAL_RCC_GPIOI_CLK_ENABLE();break;
            }
        }

        void Override::GPIOx_PreDisable(uint32_t GPIOx){
            switch(GPIOx){
                case 0:__HAL_RCC_GPIOA_CLK_DISABLE();break;
                case 1:__HAL_RCC_GPIOB_CLK_DISABLE();break;
                case 2:__HAL_RCC_GPIOC_CLK_DISABLE();break;
                case 3:__HAL_RCC_GPIOD_CLK_DISABLE();break;
                case 4:__HAL_RCC_GPIOE_CLK_DISABLE();break;
                case 5:__HAL_RCC_GPIOF_CLK_DISABLE();break;
                case 6:__HAL_RCC_GPIOG_CLK_DISABLE();break;
                case 7:__HAL_RCC_GPIOH_CLK_DISABLE();break;
                case 8:__HAL_RCC_GPIOI_CLK_DISABLE();break;
            }
        }


    #endif

    #if __Enable_SystemClock
        static uint32_t fac_us=0;
        void Clock_Init(uint32_t plln,uint32_t pllm,uint32_t pllp,uint32_t pllq){
            HAL_StatusTypeDef ret = HAL_OK;
            RCC_OscInitTypeDef RCC_OscInitStructure; 
            RCC_ClkInitTypeDef RCC_ClkInitStructure;
            
            __HAL_RCC_PWR_CLK_ENABLE(); //使能PWR时钟
            
            //下面这个设置用来设置调压器输出电压级别，以便在器件未以最大频率工作
            //时使性能与功耗实现平衡。
            __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);//设置调压器输出电压级别1
            
            RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    //时钟源为HSE
            RCC_OscInitStructure.HSEState=RCC_HSE_ON;                      //打开HSE
            RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;//打开PLL
            RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;//PLL时钟源选择HSE
            RCC_OscInitStructure.PLL.PLLM=pllm; //主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63.
            RCC_OscInitStructure.PLL.PLLN=plln; //主PLL倍频系数(PLL倍频),取值范围:64~432.  
            RCC_OscInitStructure.PLL.PLLP=pllp; //系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
            RCC_OscInitStructure.PLL.PLLQ=pllq; //USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15.
            ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);//初始化
            
            if(ret!=HAL_OK) while(1);
            
            //选中PLL作为系统时钟源并且配置HCLK,PCLK1和PCLK2
            RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
            RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;//设置系统时钟时钟源为PLL
            RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;//AHB分频系数为1
            RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV4; //APB1分频系数为4
            RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV2; //APB2分频系数为2
            ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_5);//同时设置FLASH延时周期为5WS，也就是6个CPU周期。
                
            if(ret!=HAL_OK) while(1);

            //STM32F405x/407x/415x/417x Z版本的器件支持预取功能
            if (HAL_GetREVID() == 0x1001){
                __HAL_FLASH_PREFETCH_BUFFER_ENABLE();  //使能flash预取
            }
        }
        void Delay_init(uint32_t SYSCLK) {
            HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTick频率为HCLK
	        fac_us=SYSCLK;
        }
        
        
        


        
        std::map<Clock_Speed,std::function<void(void)>> Override::ClockPrototypes{
            {Clock_Speed::HighSpeed,[](){
                HAL_Init();Clock_Init(336,8,2,7);Delay_init(168);
            }},//168Mhz
        };


        void Override::Delay_Prototype(uint32_t us){
            uint32_t ticks;
            uint32_t told,tnow,tcnt=0;
            uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
            ticks=us*fac_us; 						//需要的节拍数 
            told=SysTick->VAL;        				//刚进入时的计数器值
            while(1) {
                tnow=SysTick->VAL;	
                if(tnow!=told) {	    
                    if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
                    else tcnt+=reload-tnow+told;	    
                    told=tnow;
                    if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
                }  
	        };

        };
    #endif



    #ifdef __Enable_Uart

        std::function<void(char*,int)> Uart_Callback[CFG_Usart_Size+CFG_Uart_Size];
        u_char Uart_RxBuffer[CFG_Usart_Size+CFG_Uart_Size][CFG_Uart_Buf_Size];

        std::vector<std::pair<unsigned int,std::string>> EndFlags{
            {0,"\x0d\n"},{0,"\x0d\n"},{0,"\x0d\n"},{0,"\x0d\n"},{0,"\x0d\n"}
        };

        bool EndCheck(unsigned int AllUartx,char Res){
            if(EndFlags[AllUartx].second[EndFlags[AllUartx].first++]==Res){
                if(EndFlags[AllUartx].first==EndFlags[AllUartx].second.size()){
                    EndFlags[AllUartx].first=0;
                    return true;
                }
            }else{
                EndFlags[AllUartx].first=0;
            }
            return false;
        }


        std::vector<std::pair<u_char*,std::function<void(char*,int)>&>> Override::UsartOccupation{
            {Uart_RxBuffer[0],Uart_Callback[0]},{Uart_RxBuffer[1],Uart_Callback[1]},{Uart_RxBuffer[2],Uart_Callback[2]},
        };

        std::vector<std::pair<u_char*,std::function<void(char*,int)>&>> Override::UartOccupation{
            {Uart_RxBuffer[CFG_Uart_Size],Uart_Callback[CFG_Uart_Size]},{Uart_RxBuffer[CFG_Uart_Size+1],Uart_Callback[CFG_Uart_Size+1]},
        };

        UART_HandleTypeDef USART_Handler[CFG_Usart_Size+CFG_Uart_Size];

        USART_TypeDef* USART_Mapping[]{
            USART1,
            USART2,
            USART3,
            UART4,
            UART5,
        };


        void Override::Usartx_PreEnable(Usart* Usart){
            USART_Handler[Usart->Usartx].Instance=                                      USART_Mapping[Usart->Usartx];
            USART_Handler[Usart->Usartx].Init.BaudRate=                                 Usart->Bound*3.125376;
            USART_Handler[Usart->Usartx].Init.WordLength=                               UART_WORDLENGTH_8B;     //字长为8位数据格式.
            USART_Handler[Usart->Usartx].Init.StopBits=                                 UART_STOPBITS_1;	    //一个停止位.
            USART_Handler[Usart->Usartx].Init.Parity=                                   UART_PARITY_NONE;	    //无奇偶校验位.
            USART_Handler[Usart->Usartx].Init.HwFlowCtl=                                UART_HWCONTROL_NONE;    //无硬件流控.
            USART_Handler[Usart->Usartx].Init.Mode=                                     UART_MODE_TX_RX;		//收发模式.
            HAL_UART_Init(&USART_Handler[Usart->Usartx]);	                            				        //HAL_UART_Init()会使能UART1.
            //该函数会开启接收中断:标志位UART_IT_RXNE,并且设置接收缓冲以及接收缓冲接收最大数据量.
            HAL_UART_Receive_IT(&USART_Handler[Usart->Usartx],UartOccupation[Usart->Usartx].first,1);
        }

        void Override::Usartx_PreDisable(Usart* Usart){

        }
        
        void Override::Uartx_PreEnable(Uart* Uart){

        }

        void Override::Uartx_PreDisable(Uart* Uart){

        }

        void Override::Usart_Send(Usart* Usart,std::string Info){
            for(unsigned int i=0;i<Info.size();i++){
                while((USART_Mapping[Usart->Usartx]->SR&0x40)==0);
                USART_Mapping[Usart->Usartx]->DR=(u_char)Info[i];
            }
        }

        void Override::Uart_Send(Uart* Uart,std::string Info){
            for(unsigned int i=0;i<Info.size();i++){
                while((USART_Mapping[Uart->Uartx]->SR&0x40)==0);
                USART_Mapping[Uart->Uartx]->DR=(u_char)Info[i];
            }
        }
        
        

        extern "C" void HAL_UART_MspInit(UART_HandleTypeDef *huart){
            //GPIO端口设置
            GPIO_InitTypeDef GPIO_Initure;

            if(huart->Instance==USART1){
                if(!PIN::CoverPIN(0,9)||!PIN::CoverPIN(0,10)){
                    return;
                }

                __HAL_RCC_USART1_CLK_ENABLE();			        //使能USART1时钟

                GPIO_Initure.Pin=GPIO_PIN_9;			        //PA9 TX
                GPIO_Initure.Mode=GPIO_MODE_AF_PP;		        //复用推挽输出
                GPIO_Initure.Pull=GPIO_PULLUP;			        //上拉
                GPIO_Initure.Speed=GPIO_SPEED_FAST;		        //高速
                GPIO_Initure.Alternate=GPIO_AF7_USART1;	        //复用为USART1
                HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	        //初始化PA9

                GPIO_Initure.Pin=GPIO_PIN_10;			        //PA10 RX
                HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	        //初始化PA10
                
                HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
                HAL_NVIC_SetPriority(USART1_IRQn,3,2);			//抢占优先级3，子优先级2
            }

            if(huart->Instance==USART2){
                if(!PIN::CoverPIN(0,2)||!PIN::CoverPIN(0,3)){
                    return;
                }

                __HAL_RCC_USART2_CLK_ENABLE();			        //使能USART2时钟

                GPIO_Initure.Pin=GPIO_PIN_2;			        //PA2 TX
                GPIO_Initure.Mode=GPIO_MODE_AF_PP;		        //复用推挽输出
                GPIO_Initure.Pull=GPIO_PULLUP;			        //上拉
                GPIO_Initure.Speed=GPIO_SPEED_FAST;		        //高速
                GPIO_Initure.Alternate=GPIO_AF7_USART2;	        //复用为USART2
                HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	        //初始化PA2

                GPIO_Initure.Pin=GPIO_PIN_3;			        //PA3 RX
                HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	        //初始化PA3
                
                HAL_NVIC_EnableIRQ(USART2_IRQn);				//使能USART2中断通道
                HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//抢占优先级3，子优先级3
            }

            if(huart->Instance==USART3){
                if(!PIN::CoverPIN(1,10)||!PIN::CoverPIN(1,11)){
                    return;
                }

                __HAL_RCC_USART3_CLK_ENABLE();			        //使能USART3时钟

                GPIO_Initure.Pin=GPIO_PIN_10;			        //PB10
                GPIO_Initure.Mode=GPIO_MODE_AF_PP;		        //复用推挽输出
                GPIO_Initure.Pull=GPIO_PULLUP;			        //上拉
                GPIO_Initure.Speed=GPIO_SPEED_FAST;		        //高速
                GPIO_Initure.Alternate=GPIO_AF7_USART3;	        //复用为USART3
                HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	        //初始化PB10

                GPIO_Initure.Pin=GPIO_PIN_11;			        //PB11
                HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	        //初始化PB11
                
                HAL_NVIC_EnableIRQ(USART3_IRQn);				//使能USART3中断通道
                HAL_NVIC_SetPriority(USART3_IRQn,3,4);			//抢占优先级3，子优先级4
            }

        }



        

        


        //数据位
        u_char Res[5];

        //状态位
        uint16_t USART_RX_STA[5];

        //位长
        uint16_t Len[5];

        //接收标志位
        bool ReciveFlag[5]={false};

        void Override::Usart_Close(Usart* Usart){
            ReciveFlag[Usart->Usartx]=true;
        }
        void Override::Usart_Open(Usart* Usart){
            ReciveFlag[Usart->Usartx]=false;
        }

        
        //串口1中断服务程序
        extern "C" void USART1_IRQHandler(void)                	
        { 
            if(ReciveFlag[0]){
                Res[0]=USART1->DR;    
            }
            else if(USART1->SR&(1<<5)) {  
                Res[0]=USART1->DR;                     
                Override::UsartOccupation[0].first[Len[0]++]=Res[0];
                
                if(EndCheck(0,Res[0])&&Override::UsartOccupation[0].second){
                    Override::UsartOccupation[0].second((char*)Override::UsartOccupation[0].first,Len[0]-2);
                    Len[0]=0;                  
                }		 
            }
        } 

        extern "C" void USART2_IRQHandler(){
            if(ReciveFlag[1]){
                Res[1]=USART2->DR;    
            }
            else if(USART2->SR&(1<<5)) {  
                Res[1]=USART2->DR;   
                Override::UsartOccupation[1].first[Len[1]++]=Res[1];
                if(EndCheck(1,Res[1])&&Override::UsartOccupation[1].second){
                    Override::UsartOccupation[1].second((char*)Override::UsartOccupation[1].first,Len[1]-2);
                    Len[1]=0;
                }		 
            }
        }

        extern "C" void USART3_IRQHandler(){
            if(ReciveFlag[2]){
                Res[2]=USART3->DR;    
            }
            else if(USART3->SR&(1<<5)) {  
                Res[2]=USART3->DR;   
                Override::UsartOccupation[2].first[Len[2]++]=Res[2];
                if(EndCheck(2,Res[2])&&Override::UsartOccupation[2].second){
                    Override::UsartOccupation[2].second((char*)Override::UsartOccupation[2].first,Len[2]-2);
                    Len[2]=0;
                }
            }
        }

        extern "C" void UART4_IRQHandler(){
            
        }

        extern "C" void UART5_IRQHandler(){
            
        }

        
    #endif
#endif