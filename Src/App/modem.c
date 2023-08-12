#include "modem.h"

static GPIO_Handler_t modem_tx;
static GPIO_Handler_t modem_rx;
static USART_Handler_t usart2;

void modem_init()
{
	rcc_enable_clock(GPIO_PORT_A);
	gpio_init(&modem_tx,GPIOA_BASE_ADDRESS,GPIO_pin_2,GPIO_Alternate_function_output_Push_pull,GPIO_Output_mode_max_speed_10_MHz);
	gpio_config(&modem_tx);
	gpio_init(&modem_rx,GPIOA_BASE_ADDRESS,GPIO_pin_3,GPIO_Floating_input,GPIO_Input_mode);
	gpio_config(&modem_rx);

	rcc_enable_clock(SERIAL_PORT_2);
	usart_init(&usart2,USART2_BASE_ADDRESS,BAUDRATE,0,0,0,0);
	usart_config(&usart2);

	usart_interrupt_enable(&usart2);

	nvic_set_irq_priority(1,SERIAL_PORT_2);
	nvic_enable_irq(SERIAL_PORT_2);
}

void modem_test_msg(void)
{
	usart_tx_frame(&usart2,(uint8_t*)"Msg From Modem\n");
}

