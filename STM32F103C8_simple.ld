/* Liam Goudge 2016 */
/* Memory configuration for STM32F103C8 */
/* MDFly board is 103C8 which is 64K Flash, 20K RAM */

ENTRY(main)

MEMORY
{
  	SRAM (rwx) 	: ORIGIN = 0x20000000, LENGTH = 20K
  	STACK (rwx)	: ORIGIN = 0x20004E20, LENGTH = 0K	/* Defines address of the end of the stack. Actual end of SRAM is 0x200004E20 */
  	FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 64K

}

PROVIDE(__stack = ORIGIN(STACK) );  				/* __stack required by crt0.o otherwise it assumes 0x8000 */
HeapSize = 5000;
_stack_size = 4K;


SECTIONS {

	. = ORIGIN(FLASH);

	.text :
	{
		*(.isr_vectors)								/* ISR Vector table. Used by startup asm */
		*(.text*)
		*(.rodata*)
	} >FLASH

	__FLASHdata_start = .;


	. = ORIGIN(SRAM);

	.data :
	{
		__RAMdata_start = .;
		*(.data*)
		__RAMdata_end = .;
	} >SRAM AT >FLASH

	__FLASHdata_start = LOADADDR(.data); /* ???????? why set this again ???? */

	.bss :
	{
		__bss_start__ = .;							/* Used by startup asm */
		*(.bss*)
		__bss_end__ = .;							/* Used by startup asm */
	} >SRAM


	end = . ; 										/* Required for _sbrk in semihost.c*/

	.heap :
	{
		__HeapBase = .;								/* required for _sbrk in semihost.c */
    HeapBase = __HeapBase;
		__HeapLimit = __HeapBase + HeapSize ;		/* required for _sbrk in semihost.c */
    HeapLimit = __HeapLimit;
		*(.heap*)

    _heap_bottom = .;
    _heap_top = ORIGIN(SRAM) + LENGTH(SRAM) - _stack_size;

    _stack_bottom = _heap_top;
    _stack_top = ORIGIN(SRAM) + LENGTH(SRAM);

	} > SRAM

}
