 /******************************************************************************
 *	Basic assembly start up for STM32F100C8 and STM32F103C8
 *	Sets up exception vector table, initialized data and hands over to main()
 *  Targets Eclipse Mars with ARM GNU tools gcc-arm-none-eabi-4_8-2013q4
 *	Liam Goudge July 2014 / Jan 2017 / Jul 2024
 *
 *******************************************************************************/
.syntax unified						// Must have this to specify UAL (Universal Assembly Language)
.thumb

.global  Default_Handler
.global  Reset_Handler

.text

// Handler for Reset.
.type Reset_Handler , %function		// Must. Ensures linker generates a Thumb branch address (ends in 1). Without this, generates ARM address and code does not work stand alone
Reset_Handler:
/*	Copy initialized data from FLASH to SRAM
	__etext: End of code section in FLASH, i.e., begin of data sections to copy from.
	__data_start__/__data_end__: RAM address range that data should be
	copied to. Both must be aligned to 4 bytes boundary. */

	ldr		r1, =__FLASHdata_start
	ldr		r2, =__RAMdata_start
	ldr		r3, =__RAMdata_end

init_data_loop:
	cmp		r2, r3
	ittt	lt
	ldrlt	r0, [r1], #4
	strlt	r0, [r2], #4
	blt		init_data_loop

/*  Clear the zero uninitialized data bss section
	__bss_start__: start of the BSS section.
	__bss_end__: end of the BSS section.
	Both addresses must be aligned to 4 bytes boundary. */

zero_bss:
	ldr		r1, =__bss_start__
	ldr		r3, =__bss_end__
	subs	r3, r3, r1		// Length of uninitialized data
	beq		enter_main		// Skip if none
	mov		r2, #0

zero_bss_loop:
	strb	r2, [r1], #1	// Store zero
	subs	r3, r3, #1		// Decrement counter
	bgt		zero_bss_loop	// Repeat until done

enter_main:
	bl		main 			// Call application entry point
	bx		lr


Default_Handler:
	b		Default_Handler // Loops here forever to trap an exception

.section  .isr_vectors

Vectors:
// Cortex M3 exception vectors
.word	__stack				// stack top address
.word   Reset_Handler		// Reset. First code address after reset
.word   Default_Handler		// NMI_Handler
.word   Default_Handler		// HardFault
.word   Default_Handler		// MemManage
.word   Default_Handler		// BusFault
.word   Default_Handler		// UsageFault
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// SVC Handler
.word   Default_Handler		// Debug Monitor
.word   Default_Handler		// RESERVED
.word   Default_Handler		// PendSV
.word   Default_Handler		// SysTick

// STM32F100 specific exception vectors
.word   Default_Handler		// WWDG
.word   Default_Handler		// PVD
.word   Default_Handler		// Tamper Stamp
.word   Default_Handler		// RTC WKUP
.word   Default_Handler		// Flash
.word   Default_Handler		// RCC
.word   Default_Handler		// EXTI0
.word   Default_Handler		// EXTI1
.word   Default_Handler		// EXTI2
.word   Default_Handler		// EXTI3
.word   Default_Handler		// EXTI4
.word   Default_Handler		// DMA1 Channel1
.word   Default_Handler		// DMA1 Channel2
.word   Default_Handler		// DMA1 Channel3
.word   Default_Handler		// DMA1 Channel4
.word   Default_Handler		// DMA1 Channel5
.word   Default_Handler		// DMA1 Channel6
.word   Default_Handler		// DMA1 Channel7
.word   Default_Handler		// ADC1
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// EXTI9_5
.word   Default_Handler		// TIM1_BRK_TIM15
.word   Default_Handler		// TIM1_UP_TIM16
.word   Default_Handler		// TIM1_TRG_COM_TIM17
.word   Default_Handler		// TIM1_CC
.word   Default_Handler		// TIM2
.word   Default_Handler		// TIM3
.word   Default_Handler		// TIM4
.word   Default_Handler		// I2C1_EV
.word   Default_Handler		// I2C1_ER
.word   Default_Handler		// I2C2_EV
.word   Default_Handler		// I2C2_ER
.word   Default_Handler		// SPI1
.word   Default_Handler		// SPI2
.word   Default_Handler		// USART1
.word   Default_Handler		// USART2
.word   Default_Handler		// USART3
.word   Default_Handler		// EXTI15_10
.word   Default_Handler		// RTC_Alarm
.word   Default_Handler		// CEC
.word   Default_Handler		// TIM12
.word   Default_Handler		// TIM13
.word   Default_Handler		// TIM14
.word   Default_Handler		// RESERVED
.word   Default_Handler		// RESERVED
.word   Default_Handler		// FSMC
.word   Default_Handler		// RESERVED
.word   Default_Handler		// TIM5
.word   Default_Handler		// SPI3
.word   Default_Handler		// UART4
.word   Default_Handler		// UART5
.word   Default_Handler		// TIM6_DAC
.word   Default_Handler		// TIM7
.word   Default_Handler		// DMA2_Channel1
.word   Default_Handler		// DMA2_Channel2
.word   Default_Handler		// DMA2_Channel3
.word   Default_Handler		// DMA2_Channel4_5
.word   Default_Handler		// DMA2_Channel5

.end
