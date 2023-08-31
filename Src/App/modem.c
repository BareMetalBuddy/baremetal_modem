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

void modem_flush(void)
{
	while(usart_available(&usart2)>0){
		char read_ch = usart_read(&usart2);
	}
}

void modem_test_msg(void)
{
	usart_tx_frame(&usart2,(uint8_t*)"Msg From Modem\n");
}

uint8_t modem_at_command_write(uint8_t* at_cmd, uint8_t id, uint16_t timeout)
{
	static int state  			= RESET;
	static uint16_t timeout_ 	= RESET;
	uint8_t code 				= WAIT;

	switch(state){
		case SEND_AT_CMD:{
			modem_flush();
			uint8_t *ptr = at_cmd;
			for (int i = 0; i < strlen((const char*)at_cmd); i++){
				usart_tx(&usart2,*ptr++);
			}
			state = WAIT_FOR_AT_CMD_ANSWER;
			timeout_ = timeout;
		}
		break;

		case WAIT_FOR_AT_CMD_ANSWER:{
			uint8_t at_cmd_answers[SERIAL_BUFFER_SIZE]; // same size as buffer for ring buffer
			uint8_t index = 0;
			memset(at_cmd_answers,0,sizeof(at_cmd_answers));
			while(usart_available(&usart2)>0){
				at_cmd_answers[index++] = usart_read(&usart2);
				at_cmd_answers[index] = '\0';
			}

			if(strlen((const char*)at_cmd_answers)>0){		 // if the buffer is different than zero
				code = at_check_response(id,at_cmd_answers); // if this line is executed means that there are some data to check
				if(code != WAIT){
					state 	 = SEND_AT_CMD;
					timeout_ = RESET;
				}
			}

			if(code == WAIT){
				timeout_--;
				if(!timeout_){
					code = FAIL;
					state = SEND_AT_CMD;
				}
			}
		}

		break;

		default:
		break;
	}
	return code;
}


void USART2_IRQHandler()
{
	usart_receive(&usart2);
}

