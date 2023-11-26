#include "start.h"


/*SysClock = HSE_VALUE / PLL_M * PLL_N / PLL_P = 84MHz */
/*
    1. Initialize the Clock as 84MHz with HSE as source
    2. Initialize System
*/




uint8_t HSEStatus = 0;
uint32_t StartUpCounter = 0;
uint32_t SystemCoreClock = 0;
void My_SystemInit(void);
void My_SystemClockConfig(void);
void My_SystemClockUpdate(void);


void My_SystemInit(void)
{
    // FPU settings, set CP10 and CP11 Full Access 
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
    My_SystemClockConfig();
    My_SystemClockUpdate();
}

void My_SystemClockConfig()
{
    // ResSetClockSION bit 
    RCC->CR |= (uint32_t)0x00000001;

    // Reset CFGR register 
    RCC->CFGR = 0x00000000;

    // Reset HSEON, CSSON and PLLON bits 
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    // Reset PLLCFGR register 
    RCC->PLLCFGR = 0x24003010;

    // Reset HSEBYP bit 
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    // Disable all interrupts 
    RCC->CIR = 0x00000000;

    // HSE ON
    RCC -> CR |= 1U<<16;

    // Wait until HSE is ready
    do
    {
        HSEStatus = (RCC->CR & 1<<17)>>17;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter <= HSE_STARTUP_TIMEOUT));
    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }
    if (HSEStatus == (uint32_t)0x01)
    {
        // Select regulator voltage output Scale 1 mode 
        RCC->APB1ENR |= 0X1UL<<28U;
        PWR->CR |= 0x3UL<<14U;
    
        //HCLK = PCLK1 =PCLK2 = SYSCLK 
        RCC->CFGR |= 0x00000000U;

        // Set PLL_M = 8, PLL_N = 168, PLL_P = 2, PLL_Q = 7
        RCC -> PLLCFGR = (PLL_M<<0) | (PLL_N<<6) | (PLL_P<<16) | (PLL_Q<<24);

        // Set the HSE as PLL source
        RCC -> PLLCFGR |= 1U<<22;  
         // PLL ON
        RCC -> CR |= 1U<<24;
        // Wait until PLL is ready
        while(!(RCC -> CR & (1U<<25)));

        // Configure Flash prefetch, Instruction cache, Data cache and wait state
        FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;

//        // Set HSE as PLL source
//		RCC -> PLLCFGR |= 1U<<22;	
       
        // Set PLL as system clock
        RCC -> CFGR &= ~(3U<<0);
        RCC -> CFGR |= 2U<<0;
        // Wait until PLL is used as system clock
        while(!(RCC -> CFGR & (2U<<2)));
    }

    

}

void My_SystemClockUpdate(void)
{
    uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
    
    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp)
    {
        case 0x00:  /* HSI used as system clock source */
        SystemCoreClock = HSI_VALUE;
        break;
        case 0x04:  /* HSE used as system clock source */
        SystemCoreClock = HSE_VALUE;
        break;
        case 0x08:  /* PLL used as system clock source */

        /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
            SYSCLK = PLL_VCO / PLL_P
            */    
        pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
        pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
        
        if (pllsource != 0)
        {
            /* HSE used as PLL clock source */
            pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }
        else
        {
            /* HSI used as PLL clock source */
            pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }

        pllp = (RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16;
        SystemCoreClock = pllvco/pllp;
        break;
        default:
        SystemCoreClock = HSI_VALUE;
        break;
  }
}
