#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <string.h>
#include "bsp.h"
#include "ring_buffer.h"

#define TX_ENABLE 		(1<<3)
#define RX_ENABLE 		(1<<2)
#define USART_ENABLE 	(1<<13)
#define TRANSMIT_DATA_REGISTER_EMPTY (1<<7)
#define RECEIVE_DATA_REGISTER_IS_NOT_EMPTY	(1<<5)
#define RX_INTERRUPT_ENABLE 			    (1<<5)

#define USART1_BASE_ADDRESS (0x40013800)
#define USART2_BASE_ADDRESS (0x40004400)
#define USART3_BASE_ADDRESS (0x40004800)

typedef struct{
	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;
}USART_Reg_t;

typedef struct{
	uint32_t baudrate;
	uint8_t parity;
	uint8_t usart_mode;
	uint8_t data_bit;
	uint8_t stop_bit;
	volatile USART_Reg_t *usart;
	ring_buffer rb;
	uint8_t serial_buffer[SERIAL_BUFFER_SIZE];
}USART_Handler_t;


void usart_init(USART_Handler_t *usart_handler,uint32_t base_address, uint32_t baudrate, uint8_t parity, uint8_t usart_mode, uint8_t data_bit, uint8_t stop_bit);
void usart_config(USART_Handler_t *usart_handler);
void usart_tx_frame(USART_Handler_t *usart_handler, uint8_t * frame);
void usart_tx(USART_Handler_t *usart_handler, uint8_t data);
uint8_t usart_rx(USART_Handler_t *usart_handler);
void usart_interrupt_enable(USART_Handler_t *usart_handler);
void usart_interrupt_disable(USART_Handler_t *usart_handler);
void usart_receive(USART_Handler_t *usart_handler);
uint16_t usart_available(USART_Handler_t *usart_handler);
uint8_t usart_read(USART_Handler_t *usart_handler);


#endif /* USART_H_ */
