#include "nvic.h"

void nvic_enable_irq(uint8_t module)
{
	switch(module)
	{
		case SERIAL_PORT_1:
			NVIC_ENABLE_INTERRUPT_USART1();
			break;

		case SERIAL_PORT_2:
			NVIC_ENABLE_INTERRUPT_USART2();
			break;

		case SERIAL_PORT_3:
			break;

		case BASIC_TIMER_6:
			break;
	}
}

void nvic_disable_irq(uint8_t irq)
{

}

void nvic_set_irq_priority(uint8_t module ,uint32_t priority)
{
	switch(module)
	{
		case SERIAL_PORT_1:
			NVIC_SET_INTERRUPT_PRIORITY_USART1(priority);
			break;

		case SERIAL_PORT_2:
			NVIC_SET_INTERRUPT_PRIORITY_USART2(priority);
			break;

		case SERIAL_PORT_3:
			break;

		case BASIC_TIMER_6:
			break;
	}
}
