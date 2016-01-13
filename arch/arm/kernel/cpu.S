#incldue <kernel.h>
.syntax unified
.extern pthread_next
.extern pthread_current
.global pendsv_handler1

.align  4
.section .text.hand
pendsv_handler1:
    push {r3}
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

