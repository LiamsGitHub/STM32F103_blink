// Header file for STM32F103 peripheral set
// Rearchitected July 2024

#include "stdint.h" // to get uint definitions


// ****** SYSTICK ****
#define SYST_CSR			(*((volatile uint32_t *)	0xE000E010))		// SYST_CSR SysTick Control and Status Register
#define SYST_RVR			(*((volatile uint32_t *)	0xE000E014))		// SYST_RVR SysTick Reload Value Register. Load value for 1ms (assuming 8MHz clock)
#define SYST_CVR			(*((volatile uint32_t *)	0xE000E018))		// SYST_CVR SysTick Current Value Register

// ****** Reset and Clock Control (RCC) *****
#define RCC_BASE			((uint32_t) 0x40021000)
#define RCC_CR		       	(*((volatile uint32_t *) (RCC_BASE + 0x00))) // Clock control register
#define RCC_CFGR       		(*((volatile uint32_t *) (RCC_BASE + 0x04))) // Clock configuration register
#define RCC_CIR             (*((volatile uint32_t *) (RCC_BASE + 0x08)))
#define RCC_APB2RSTR        (*((volatile uint32_t *) (RCC_BASE + 0x0C)))
#define RCC_APB1RSTR        (*((volatile uint32_t *) (RCC_BASE + 0x10)))
#define RCC_AHBENR          (*((volatile uint32_t *) (RCC_BASE + 0x14)))
#define RCC_APB2ENR       	(*((volatile uint32_t *) (RCC_BASE + 0x18))) // APB2 peripheral clock enable register
#define RCC_APB2ENR         (*((volatile uint32_t *) (RCC_BASE + 0x18)))
#define RCC_APB1ENR         (*((volatile uint32_t *) (RCC_BASE + 0x1C)))
#define RCC_BDCR            (*((volatile uint32_t *) (RCC_BASE + 0x20)))
#define RCC_CSR             (*((volatile uint32_t *) (RCC_BASE + 0x24)))

#define RCC_APB2ENR_IOPAEN	((unsigned int)0b1 << 2) // GPIOA clock enable
#define RCC_APB2ENR_IOPCEN	((unsigned int)0b1 << 4) // GPIOC clock enable
#define RCC_CR_HSEON		((unsigned int)0b1 << 16) // HSE enable
#define RCC_CR_HSERDY		((unsigned int)0x00020000)
#define RCC_CFGR_PLLSRC		((unsigned int)0x00010000)
#define RCC_CFGR_PLLMULL9	((unsigned int)0x001C0000)
// #define RCC_CFGR_MCO		((unsigned int)0x06000000)
#define RCC_CFGR_MCO_Pos	(24U)
#define RCC_CFGR_MCO_Msk	(0b111 << RCC_CFGR_MCO_Pos) // Mask for 3 MCO bits
#define RCC_CFGR_MCO		SPI_CR1_CPHA_Msk

#define RCC_CR_PLLON		((unsigned int)0x01000000)
#define RCC_CR_PLLRDY		((unsigned int)0x02000000)
#define RCC_CFGR_SW_PLL		((unsigned int)0x00000002)
#define RCC_CFGR_SWS_PLL	((unsigned int)0x00000008)
#define RCC_CFGR_MCO_SYSCLK	((unsigned int)0x04000000)

// Nested Vectored Interrupt Controller (NVIC) // CHECK THIS
#define NVIC_BASE           0xE000E100
#define NVIC                (*((volatile uint32_t *) NVIC_BASE))

// **** GPIO Port Registers ****
#define GPIOA_BASE			((uint32_t) 0x40010800)
#define GPIOA_CRL			(*((volatile uint32_t *) (GPIOA_BASE + 0x00))) // Port configuration register low
#define GPIOA_CRH			(*((volatile uint32_t *) (GPIOA_BASE + 0x04))) // Port configuration register high
#define GPIOA_IDR			(*((volatile uint32_t *) (GPIOA_BASE + 0x08))) // Port input data register
#define GPIOA_ODR			(*((volatile uint32_t *) (GPIOA_BASE + 0x0C))) // Port output data register
#define GPIOA_BSRR			(*((volatile uint32_t *) (GPIOA_BASE + 0x10))) // Port bit set/reset register
#define GPIOA_BRR			(*((volatile uint32_t *) (GPIOA_BASE + 0x14))) // Port bit reset register
#define GPIOA_LCKR			(*((volatile uint32_t *) (GPIOA_BASE + 0x18))) // Port configuration lock register

#define GPIOB_BASE          ((uint32_t) 0x40010C00)
#define GPIOB_CRL			(*((volatile uint32_t *) (GPIOB_BASE + 0x00))) // Port configuration register low
#define GPIOB_CRH			(*((volatile uint32_t *) (GPIOB_BASE + 0x04))) // Port configuration register high
#define GPIOB_IDR			(*((volatile uint32_t *) (GPIOB_BASE + 0x08))) // Port input data register
#define GPIOB_ODR			(*((volatile uint32_t *) (GPIOB_BASE + 0x0C))) // Port output data register
#define GPIOB_BSRR			(*((volatile uint32_t *) (GPIOB_BASE + 0x10))) // Port bit set/reset register
#define GPIOB_BRR			(*((volatile uint32_t *) (GPIOB_BASE + 0x14))) // Port bit reset register
#define GPIOB_LCKR			(*((volatile uint32_t *) (GPIOB_BASE + 0x18))) // Port configuration lock register

#define GPIOC_BASE          ((uint32_t) 0x40011000)
#define GPIOC_CRL			(*((volatile uint32_t *) (GPIOC_BASE + 0x00))) // Port configuration register low
#define GPIOC_CRH			(*((volatile uint32_t *) (GPIOC_BASE + 0x04))) // Port configuration register high
#define GPIOC_IDR			(*((volatile uint32_t *) (GPIOC_BASE + 0x08))) // Port input data register
#define GPIOC_ODR			(*((volatile uint32_t *) (GPIOC_BASE + 0x0C))) // Port output data register
#define GPIOC_BSRR			(*((volatile uint32_t *) (GPIOC_BASE + 0x10))) // Port bit set/reset register
#define GPIOC_BRR			(*((volatile uint32_t *) (GPIOC_BASE + 0x14))) // Port bit reset register
#define GPIOC_LCKR			(*((volatile uint32_t *) (GPIOC_BASE + 0x18))) // Port configuration lock register

#define GPIO_CRH_MODE8        ((unsigned int)0x00000003)
#define GPIO_CRH_CNF8         ((unsigned int)0x0000000C)
#define GPIO_CRL_MODE0        ((unsigned int)0x00000003)
#define GPIO_CRL_CNF0         ((unsigned int)0b11 << 2)
#define GPIO_CRH_MODE13       ((unsigned int)0x20000000)
#define GPIO_CRH_CNF13        ((unsigned int)0xC0000000)
#define GPIO_ODR_ODR0         ((unsigned int)0x00000001)
#define GPIO_ODR_ODR13		((unsigned int)0x2000)


// **** SPI Port Registers ****
#define SPI1_BASE           ((uint32_t) 0x40013000)
#define SPI1_CR1			(*((volatile uint32_t *) (SPI1_BASE + 0x00))) // SPI Control Register1
#define SPI1_CR2			(*((volatile uint32_t *) (SPI1_BASE + 0x04))) // SPI Control Register2
#define SPI1_SR				(*((volatile uint32_t *) (SPI1_BASE + 0x08))) // SPI Status Register
#define SPI1_DR				(*((volatile uint32_t *) (SPI1_BASE + 0x0C))) // SPI Data Register
#define SPI1_CRCPR			(*((volatile uint32_t *) (SPI1_BASE + 0x10))) // SPI CRC polynomial register
#define SPI1_RXCRCR			(*((volatile uint32_t *) (SPI1_BASE + 0x14))) // SPI RX CRC register
#define SPI1_TXCRCR			(*((volatile uint32_t *) (SPI1_BASE + 0x18))) // SPI TX CRC register
#define SPI1_I2SCFGR		(*((volatile uint32_t *) (SPI1_BASE + 0x1C))) // SPI_I2S configuration register
#define SPI1_I2SPR			(*((volatile uint32_t *) (SPI1_BASE + 0x20))) // SPI_I2S prescaler register

#define SPI2_BASE            ((uint32_t) 0x40003800)
#define SPI2_CR1			(*((volatile uint32_t *) SPI2_BASE + 0x00)) // SPI Control Register1
#define SPI2_CR2			(*((volatile uint32_t *) SPI2_BASE + 0x04)) // SPI Control Register2
#define SPI2_SR				(*((volatile uint32_t *) SPI2_BASE + 0x08)) // SPI Status Register
#define SPI2_DR				(*((volatile uint32_t *) SPI2_BASE + 0x0C)) // SPI Data Register
#define SPI2_CRCPR			(*((volatile uint32_t *) SPI2_BASE + 0x10)) // SPI CRC polynomial register
#define SPI2_RXCRCR			(*((volatile uint32_t *) SPI2_BASE + 0x14)) // SPI RX CRC register
#define SPI2_TXCRCR			(*((volatile uint32_t *) SPI2_BASE + 0x18)) // SPI TX CRC register
#define SPI2_I2SCFGR		(*((volatile uint32_t *) SPI2_BASE + 0x1C)) // SPI_I2S configuration register
#define SPI2_I2SPR			(*((volatile uint32_t *) SPI2_BASE + 0x20)) // SPI_I2S prescaler register

// Universal Synchronous/Asynchronous Receiver/Transmitter (USART)
#define USART1_BASE         0x40013800
#define USART1_SR           (*((volatile uint32_t *) (USART1_BASE + 0x00)))
#define USART1_DR           (*((volatile uint32_t *) (USART1_BASE + 0x04)))
#define USART1_BRR          (*((volatile uint32_t *) (USART1_BASE + 0x08)))
#define USART1_CR1          (*((volatile uint32_t *) (USART1_BASE + 0x0C)))
#define USART1_CR2          (*((volatile uint32_t *) (USART1_BASE + 0x10)))
#define USART1_CR3          (*((volatile uint32_t *) (USART1_BASE + 0x14)))
#define USART1_GTPR         (*((volatile uint32_t *) (USART1_BASE + 0x18)))

// Analog-to-Digital Converter (ADC1)
#define ADC1_BASE           0x40012400
#define ADC1_SR             (*((volatile uint32_t *) (ADC1_BASE + 0x00)))
#define ADC1_CR1            (*((volatile uint32_t *) (ADC1_BASE + 0x04)))
#define ADC1_CR2            (*((volatile uint32_t *) (ADC1_BASE + 0x08)))
#define ADC1_SMPR1          (*((volatile uint32_t *) (ADC1_BASE + 0x0C)))
#define ADC1_SMPR2          (*((volatile uint32_t *) (ADC1_BASE + 0x10)))
#define ADC1_JOFR1          (*((volatile uint32_t *) (ADC1_BASE + 0x14)))
#define ADC1_JOFR2          (*((volatile uint32_t *) (ADC1_BASE + 0x18)))
#define ADC1_JOFR3          (*((volatile uint32_t *) (ADC1_BASE + 0x1C)))
#define ADC1_JOFR4          (*((volatile uint32_t *) (ADC1_BASE + 0x20)))
#define ADC1_HTR            (*((volatile uint32_t *) (ADC1_BASE + 0x24)))
#define ADC1_LTR            (*((volatile uint32_t *) (ADC1_BASE + 0x28)))
#define ADC1_SQR1           (*((volatile uint32_t *) (ADC1_BASE + 0x2C)))
#define ADC1_SQR2           (*((volatile uint32_t *) (ADC1_BASE + 0x30)))
#define ADC1_SQR3           (*((volatile uint32_t *) (ADC1_BASE + 0x34)))
#define ADC1_JSQR           (*((volatile uint32_t *) (ADC1_BASE + 0x38)))
#define ADC1_JDR1           (*((volatile uint32_t *) (ADC1_BASE + 0x3C)))
#define ADC1_JDR2           (*((volatile uint32_t *) (ADC1_BASE + 0x40)))
#define ADC1_JDR3           (*((volatile uint32_t *) (ADC1_BASE + 0x44)))
#define ADC1_JDR4           (*((volatile uint32_t *) (ADC1_BASE + 0x48)))
#define ADC1_DR             (*((volatile uint32_t *) (ADC1_BASE + 0x4C)))

// I2C
#define I2C1_BASE           0x40005400
#define I2C1_CR1            (*((volatile uint32_t *) (I2C1_BASE + 0x00)))
#define I2C1_CR2            (*((volatile uint32_t *) (I2C1_BASE + 0x04)))
#define I2C1_OAR1           (*((volatile uint32_t *) (I2C1_BASE + 0x08)))
#define I2C1_OAR2           (*((volatile uint32_t *) (I2C1_BASE + 0x0C)))
#define I2C1_DR             (*((volatile uint32_t *) (I2C1_BASE + 0x10)))
#define I2C1_SR1            (*((volatile uint32_t *) (I2C1_BASE + 0x14)))
#define I2C1_SR2            (*((volatile uint32_t *) (I2C1_BASE + 0x18)))
#define I2C1_CCR            (*((volatile uint32_t *) (I2C1_BASE + 0x1C)))
#define I2C1_TRISE          (*((volatile uint32_t *) (I2C1_BASE + 0x20)))



