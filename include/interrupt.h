/* Based on Jake Sandler implementation */

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "stdint.h"

#define IRQ_NUMBER 72

/*macros used in interrupt.c*/
#define IRQ_IS_BASIC(x) ((x >= 64 ))
#define IRQ_IS_GPU2(x) ((x >= 32 && x < 64 ))
#define IRQ_IS_GPU1(x) ((x < 32 ))
#define IRQ_IS_PENDING(regs, num) ((IRQ_IS_BASIC(num) && ((1 << (num-64)) & regs->irq_basic_pending)) || (IRQ_IS_GPU2(num) && ((1 << (num-32)) & regs->irq_gpu_pending2)) || (IRQ_IS_GPU1(num) && ((1 << (num)) & regs->irq_gpu_pending1)))

/*Enumeration of the IRQs*/
typedef enum
{
    SYSTEM_TIMER_1 = 1,
    USB_CONTROLER = 9,
    ARM_TIMER = 64
} irq_number_t;

typedef struct
{
    uint32_t irq_basic_pending;
    uint32_t irq_gpu_pending1;
    uint32_t irq_gpu_pending2;
    uint32_t fiq_control;
    uint32_t irq_gpu_enable1;
    uint32_t irq_gpu_enable2;
    uint32_t irq_basic_enable;
    uint32_t irq_gpu_disable1;
    uint32_t irq_gpu_disable2;
    uint32_t irq_basic_disable;
} interrupt_registers_t;

/*Generic Interrupt handler fucntion*/
typedef void (*interrupt_handler_f)(void);

/*Generic Interrupt clearer function*/
typedef void (*interrupt_clearer_f)(void);


void interrupts_init(void);
void register_irq_handler(irq_number_t irq_num, interrupt_handler_f handler, interrupt_clearer_f clearer);
void unregister_irq_handler(irq_number_t irq_num);


#endif