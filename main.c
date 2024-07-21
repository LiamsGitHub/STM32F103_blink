// This code provides simple boot and LED blink for STM32F103 MCU
// It routes the internal high speed clock to MCO on PA8 and toggles GPIOs PC13 and PA0
// PC13 drives a small LED via a 1K resistor
// Requires startup assembly file StartUp_simple.s, register header file STM32F103.h, link script STM32F100C8_simple.ld and a Makefile
// Updated Aug 2016
// Updated Aug 2018 to work with MDFly STM32F103C8T6 board (48 pin LQFP 64KB flash)
// Updated Jul 2024. New Eclipse version. Better header and register addressing.

#include "../Foundation/stm32f103.h"

void delay_ms(unsigned int ms);
void SystemClock_Config(void);

int main(void)
{
    // Configure the system clock
    SystemClock_Config();

    // Enable the GPIOA and GPIOC clocks
    RCC_APB2ENR = RCC_APB2ENR | RCC_APB2ENR_IOPAEN;
    RCC_APB2ENR = RCC_APB2ENR | RCC_APB2ENR_IOPCEN;

    // MCO: Route HSE 8M clock out through PA8
    RCC_CFGR = RCC_CFGR & ~(RCC_CFGR_MCO_Msk);
    RCC_CFGR = RCC_CFGR | (0b110 << 24); // 0b110 selects HSE clock


    // Configure PA0 as output push-pull
    GPIOA_CRL = GPIOA_CRL & ~(0b11 << 0); // Clear MODE0 bits
    GPIOA_CRL = GPIOA_CRL | (0b10 << 0);  // Set MODE0 bits. Output 2Mhz.
    GPIOA_CRL = GPIOA_CRL & ~(0b11 << 2); // Clear CNF0 bits. Sets output push-pull.

    // Configure PA8 as output push-pull for MCO
    GPIOA_CRH = GPIOA_CRH & ~(0b11 << 0); // Clear MODE0 bits
    GPIOA_CRH = GPIOA_CRH | (0b10 << 0);  // Set MODE0 bits. Output 2Mhz.
    GPIOA_CRH = GPIOA_CRH & ~(0b11 << 2); // Clear CNF0 bits. Output. Push pull.
    GPIOA_CRH = GPIOA_CRH | (0b10 << 2);  // Set CNF bits. Alternate function. Output push pull.

    // Configure PC13 as output push-pull for LED
    GPIOC_CRH = GPIOC_CRH & ~(0b11 << 20); // Clear MODE13 bits
    GPIOC_CRH = GPIOC_CRH | (0b10 << 20);  // Set MODE13 bits. Output 2Mhz.
    GPIOC_CRH = GPIOC_CRH & ~(0b11 << 22); // Clear CNF13 bits. Sets output push-pull.


    // Main loop
    while (1)
    {
        // Toggle PA0 and PC13
        GPIOA_ODR ^= GPIO_ODR_ODR0;
        GPIOC_ODR ^= GPIO_ODR_ODR13;

        // Delay for 500 ms
        delay_ms(500);
    }
}

void delay_ms(unsigned int ms)
{
	// Simple SYSTICK polling - no interrupts
    SYST_CSR = 0; // STCSR. SysTick Control and Status Register.
    SYST_RVR = (8000 - 1);  // STRVR. SysTick Reload Value Register. Load value for 1ms (assuming 72MHz clock)
    SYST_CVR = 0; // STCVR. SysTick Current Value Register
    SYST_CSR = 0x05; // STCSR

    for (unsigned int i = 0; i < ms; i++)
    {
        // Wait until the COUNTFLAG is set
        while ( (SYST_CSR & (0b1<<16)) == 0);
    }

    // Disable SysTick
    SYST_CSR = 0;
}


void SystemClock_Config(void)
{
    // Enable HSE (High Speed External) clock
    RCC_CR = RCC_CR | RCC_CR_HSEON;
    while (!(RCC_CR & RCC_CR_HSERDY));

}

