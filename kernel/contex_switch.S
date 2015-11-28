/*
 * Copyright (c) 2015 zdx <seforna@gmail.com>
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include "reg.h"

osctxsw:
    LDR     r0, =NVIC_INT_CTRL
    LDR     r1, =NVIC_PENDSVSET
    STR     r1, [r0]
    BX      LR                                                ; Enable interrupts at processor level

OSStart_Asm:
    LDR     r0, =NVIC_SYSPRI14                                  ; Set the PendSV exception priority
    LDR     r1, =NVIC_PENDSV_PRI
    STRB    r1, [r0]

    MOVS    r0, #0                                              ; Set the PSP to 0 for initial context switch call
    MSR     PSP, r0

    LDR     r0, =_estack                                    ; Initialize the MSP to the OS_CPU_ExceptStkBase
    LDR     r1, [r0]
    MSR     MSP, r1    

    LDR     r0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     r1, =NVIC_PENDSVSET
    STR     r1, [r0]

    CPSIE   I                                                   ; Enable interrupts at processor level

OSStartHang:
    B       OSStartHang                                         ; Should never get here
    
    

pendsv_handler:
    cpsid   i                                                   ; Prevent interruption during context switch
    MRS     r0, PSP                                             ; PSP is process stack pointer
    CBZ     r0, OS_CPU_PendSVHandler_nosave                     ; Skip register save the first time
   
    SUBS    r0, r0, #0x20                                       ; Save remaining regs r4-11 on process stack
    STM     r0, {R4-r11}

    LDR     r1, =stack1;
    LDR     r1, [r1]
    STR     r0, [r1] 

OS_CPU_PendSVHandler_nosave:
    LDR     r0, =g_OS_Tcb_CurP                                       ; OSTCBCur  = OSTCBHighRdy;
    LDR     r1, =g_OS_Tcb_HighRdyP
    LDR     R2, [r1]
    STR     R2, [r0]

    LDR     r0, [R2]                                       ; r0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
  
    LDM     r0, {R4-r11}                                        ; Restore r4-11 from new process stack
    ADDS    r0, r0, #0x20
            
    MSR     PSP, r0                                             ; Load PSP with new process SP
    ORR     LR, LR, #0x04                                       ; Ensure exception return uses process stack
    
    CPSIE   I
    BX      LR                                                  ; Exception return will restore remaining context
