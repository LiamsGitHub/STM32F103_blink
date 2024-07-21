#Liam Goudge 2014
# Project Name
NAME=F103_Blink

################### File Locations #####################
TOOLS = $ ../../arm-gnu-toolchain-13.3.rel1-darwin-arm64-arm-none-eabi/bin/

CC=		$(TOOLS)arm-none-eabi-gcc
NM =	$(TOOLS)arm-none-eabi-nm			# generate symbol table
OD=		$(TOOLS)arm-none-eabi-objdump
AS =	$(TOOLS)arm-none-eabi-as
SZ =	$(TOOLS)arm-none-eabi-size

# Other Stuff
ODFLAGS = -h --syms -S

################### Build Steps #####################

all:
	@ echo "Build: "$(NAME)
	@ echo "path="$(TOOLS)

	$(TOOLS)arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -g -nostartfiles -T STM32F103C8_simple.ld  main.c  STM32F100C8startup.s -o $(NAME).elf -lm
	$(TOOLS)arm-none-eabi-nm $(NAME).elf
	
	@ echo " "	
	@ echo "List file generation:"
	$(OD) $(ODFLAGS) $(NAME).elf > $(NAME).lst
		
	@ echo " "
	@ echo "Executable size:"
	$(SZ) $(NAME).elf

clean:
	@ echo "Clean up"
	/bin/rm -f *.o *.elf *.lst
	

	
	