LINK_SCRIPT= arch/arm/link.ld
CFLAGS += -mcpu=cortex-m3 -mthumb -Iarch/arm/include
CROSS_COMPILE = arm-none-eabi-
ASMOBJS += 
COBJS += arch/arm/kernel/interrupt.o arch/arm/kernel/arch.o \
	 arch/arm/driver/timer.o arch/arm/driver/usart.o  \
     arch/arm/driver/rcc_clock.o 
OUTPUT := ${KERNEL}.bin
${KERNEL}.bin: ${KERNEL}.elf
	$(CROSS_COMPILE)objcopy -Obinary ${KERNEL}.elf ${KERNEL}.bin
	$(CROSS_COMPILE)objdump -S ${KERNEL}.elf > ${KERNEL}.list

arch-clean:
	-$(RM) ${KERNEL}.bin ${KERNEL}.list 
