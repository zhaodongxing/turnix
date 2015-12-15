/*
 * Copyright (c) 2015 Changli Gao <xiaosuo@gmail.com>
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
#ifndef _ARCH_H_
#define _ARCH_H_

#include <stdint.h>
#include <reg.h>

/* start address for the initialization values of the .data section.
 * defined in linker script */
extern uint32_t _sidata;
/* start address for the .data section. defined in linker script */
extern uint32_t _sdata;
/* end address for the .data section. defined in linker script */
extern uint32_t _edata;
/* start address for the .bss section. defined in linker script */
extern uint32_t _sbss;
/* end address for the .bss section. defined in linker script */
extern uint32_t _ebss;
/* end address for the stack. defined in linker script */
extern uint32_t _estack;



void arch_init(void);
static inline unsigned long interrupt_disable(void)
{
    unsigned long flags;
    asm volatile("mrs %0,primask\n"
                 "cpsid i\n"
                 :"=r"(flags));
    return flags;
}

static inline void interrupt_enable(unsigned long flags)
{
    asm volatile("msr primask,%0\n"::"r"(flags));
}

static inline void arch_context_switch(void)
{
    *SCB_ICSR |= SCB_ICSR_PENDSVSET;
}

struct interrupt_context {
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t ip;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
};

struct arch_context{
    unsigned long sp;
};

static int atomic_add_return(int v, volatile int *ptr);
void _start(void);

#endif

