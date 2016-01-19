#incldue <kernel.h>
.syntax unified
.type pendsv_handler, %function
.extern pthread_next
.extern pthread_current
.global pendsv_handler,atomic_add_return
.global arch_enable_interrupt
.global interrupt_enable
.global interrupt_disable

pendsv_handler:
    cpsid i
    mrs   r0, psp
    stmdb r0!, {r4-r11}
    ldr r1,=pthread_current
    ldr r2,[r1]
    str r0,[r2]
    ldr r2,=pthread_next
    ldr r0,[r2]
    str r0,[r1]

    ldr r1,[r0]
    ldmia r1!,{r4-r11}
    msr psp,r1
    orr lr,lr,#0x04
    cpsie i
    bx lr

atomic_add_return:
    ldrex r2,[r1]
    add   r2,r2,r0
    strex r3,r2,[r1]
    cmp   r3,#0
    ite   eq
    moveq r0,r2
    bne   atomic_add_return
    bx    lr

arch_enable_interrupt:
   cpsie i
   bx lr
    
interrupt_disable:
   mrs r0,primask
   cpsid i
   bx lr

interrupt_enable:
   msr primask,r0
   bx lr



