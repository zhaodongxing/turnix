#include <arch.h>
#include <NVIC.h>
#include <timer.h>

/*import from linker,the upper memory*/
extern uint32_t _estack; 

/*init interrupt priority group : 8 group 2 sub*/
void interrupt_init(void){
    pSCB->AIRCR=(pSCB->AIRCR&0xfffff8ff)|(0x4<<8);
    pSCB->SHPR3=(uint32_t)0xEFFF0000;
}

void default_handler(void)
{
	while (1);
}

__attribute((section(".isr_vector")))
struct NVIC_table isr = {
    .stack     = (uint32_t)&_estack,
    .Reset     = (uint32_t)start,
    .NMI       = (uint32_t)default_handler,
    .HardFault = (uint32_t)default_handler,
    .MemManage = (uint32_t)default_handler,
    .PendSV    = (uint32_t)pendsv_handler,
    .SysTick   = (uint32_t)timer_update,
};


