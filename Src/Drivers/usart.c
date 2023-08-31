#include "usart.h"


void usart_init(USART_Handler_t *usart_handler,uint32_t base_address,uint32_t baudrate, uint8_t parity, uint8_t usart_mode, uint8_t data_bit, uint8_t stop_bit)
{
	usart_handler->usart = (USART_Reg_t*)base_address;
	usart_handler->baudrate   = baudrate;
	usart_handler->parity     = parity;
	usart_handler->usart_mode = usart_mode;
	usart_handler->data_bit   = data_bit;
	usart_handler->stop_bit   = stop_bit;
}

/*
 * Configure UART baudrate using this formula : (peripheral_clock + (baudrate/2))/baudrate
 * TX and RX enable.
 * USART enable.
 * By default the Word length is 8N1
 * */
void usart_config(USART_Handler_t *usart_handler)
{
	usart_handler->usart->USART_BRR = ((SYSTEM_CLOCK + (usart_handler->baudrate/2))/(usart_handler->baudrate));
	usart_handler->usart->USART_CR1 |= TX_ENABLE | RX_ENABLE;
	usart_handler->usart->USART_CR1 |= USART_ENABLE;
	rb_init(&usart_handler->rb, SERIAL_BUFFER_SIZE, usart_handler->serial_buffer);
}

void usart_tx(USART_Handler_t *usart_handler, uint8_t data)
{
	while(!(usart_handler->usart->USART_SR & TRANSMIT_DATA_REGISTER_EMPTY));
	usart_handler->usart->USART_DR = data;
}


void usart_tx_frame(USART_Handler_t *usart_handler, uint8_t * frame)
{
	for (uint8_t j = 0; j < strlen((const char *)frame); j++){
		usart_tx(usart_handler,*(frame + j));
	}
}

/*
* Make sure the receive data register is not empty
* and then , return data.
*/
uint8_t usart_rx(USART_Handler_t *usart_handler)
{
	while(!(usart_handler->usart->USART_SR & RECEIVE_DATA_REGISTER_IS_NOT_EMPTY));
	return usart_handler->usart->USART_DR;
}

void usart_interrupt_enable(USART_Handler_t *usart_handler)
{
	usart_handler->usart->USART_CR1 |= RX_INTERRUPT_ENABLE;
}

void usart_interrupt_disable(USART_Handler_t *usart_handler)
{
	usart_handler->usart->USART_CR1 &= ~(RX_INTERRUPT_ENABLE);
}

void usart_receive(USART_Handler_t *usart_handler)
{
	if(usart_handler->usart->USART_SR & RECEIVE_DATA_REGISTER_IS_NOT_EMPTY){
		rb_push_insert(&usart_handler->rb,(uint8_t)(usart_handler->usart->USART_DR));
	}
}

uint16_t usart_available(USART_Handler_t *usart_handler)
{
	return rb_full_count(&usart_handler->rb);
}

uint8_t usart_read(USART_Handler_t *usart_handler)
{
	return rb_remove(&usart_handler->rb);
}
