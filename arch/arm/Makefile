LINK_SCRIPT= arch/arm/link.ld
CFLAGS += -mcpu=cortex-m3 -mthumb -Iarch/arm/include
CROSS_COMPILE = arm-none-eabi-
ASMOBJS += 
COBJS += arch/arm/kernel/os.o arch/arm/kernel/startup.o \
	 arch/arm/kernel/malloc.o arch/arm/kernel/threads.o 
OUTPUT := ${KERNEL}.bin
${KERNEL}.bin: ${KERNEL}.elf
	$(CROSS_COMPILE)objcopy -Obinary ${KERNEL}.elf ${KERNEL}.bin
	$(CROSS_COMPILE)objdump -S ${KERNEL}.elf > ${KERNEL}.list

arch-clean:
