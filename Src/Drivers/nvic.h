#ifndef NVIC_H_
#define NVIC_H_

#include <stdint.h>
#include "bsp.h"

// See Interrupt and exception vectors in Reference manual

#define NVIC_ISER0 (*(volatile uint32_t*)0xE000E100)
#define NVIC_ISER1 (*(volatile uint32_t*)0xE000E104)
#define NVIC_ISER2 (*(volatile uint32_t*)0xE000E108)

#define NVIC_ICER0 (*(volatile uint32_t*)(0xE000E180))
#define NVIC_ICER1 (*(volatile uint32_t*)(0xE000E184))
#define NVIC_ICER2 (*(volatile uint32_t*)(0xE000E188))

#define NVIC_IPR9  (*(volatile uint32_t*)(0xE000E424))


#define NVIC_SET_INTERRUPT_PRIORITY_USART1(X) (NVIC_IPR9 |= X<<12)
#define NVIC_ENABLE_INTERRUPT_USART1() (NVIC_ISER1 |= 1<<5)

#define NVIC_SET_INTERRUPT_PRIORITY_USART2(X) (NVIC_IPR9 |= X<<20)
#define NVIC_ENABLE_INTERRUPT_USART2() (NVIC_ISER1 |= 1<<6)


void nvic_enable_irq(uint8_t irq);
void nvic_disable_irq(uint8_t irq);
void nvic_set_irq_priority(uint8_t module,uint32_t priority);









#endif /* NVIC_H_ */
