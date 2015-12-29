#include <config.h>

#ifndef IRQ
#define IRQ(irq)
#endif

#ifndef IRQ_WITH_ERROR
#define IRQ_WITH_ERROR(irq) IRQ(irq)
#endif

IRQ(0)
IRQ(1)
IRQ(2)
IRQ(3)
IRQ(4)
IRQ(5)
IRQ(6)
IRQ(7)
IRQ(9)
IRQ(15)
IRQ(16)
IRQ(17)
IRQ(18)
IRQ(19)
IRQ(20)
IRQ(21)
IRQ(22)
IRQ(23)
IRQ(24)
IRQ(25)
IRQ(26)
IRQ(27)
IRQ(28)
IRQ(29)
IRQ(30)
IRQ(31)
IRQ(32)
IRQ(33)
IRQ(34)
IRQ(35)
IRQ(36)
IRQ(37)
IRQ(38)
IRQ(39)
IRQ(40)
IRQ(41)
IRQ(42)
IRQ(43)
IRQ(44)
IRQ(45)
IRQ(46)
IRQ(47)
IRQ_WITH_ERROR(8)
IRQ_WITH_ERROR(10)
IRQ_WITH_ERROR(11)
IRQ_WITH_ERROR(12)
IRQ_WITH_ERROR(13)
IRQ_WITH_ERROR(14)
#if CONFIG_SWI
IRQ(128)
#endif
#ifndef IRQ_MAX
#if CONFIG_SWI
#define IRQ_MAX 255
#else
#define IRQ_MAX 47
#endif
#endif
