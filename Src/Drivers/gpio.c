#include "gpio.h"

void gpio_init(GPIO_Handler_t *gpio_handler,uint32_t base_address,uint8_t pin, uint8_t mode,uint8_t type)
{
	gpio_handler->gpio   = (GPIO_Reg_t*)base_address;
	gpio_handler->pin    = pin;
	gpio_handler->mode   = mode;
	gpio_handler->type   = type;
}

/*
 *
 * */
void gpio_config(GPIO_Handler_t *gpio_handler)
{
	if(gpio_handler->pin < 8){
		(gpio_handler->gpio->CRL) &= ~(RESET_REGISTER<<(gpio_handler->pin)*4);
		(gpio_handler->gpio->CRL) &= ~(RESET_REGISTER<<(((gpio_handler->pin)*4)+2));
		(gpio_handler->gpio->CRL) |= (gpio_handler->type<<(gpio_handler->pin)*4);
		(gpio_handler->gpio->CRL) |= (gpio_handler->mode<<(((gpio_handler->pin)*4)+2));
	}
	else{
		(gpio_handler->gpio->CRH) &= ~(RESET_REGISTER<<((gpio_handler->pin)-8)*4);
		(gpio_handler->gpio->CRH) &= ~(RESET_REGISTER<<((((gpio_handler->pin)-8)*4)+2));
		(gpio_handler->gpio->CRH) |= (gpio_handler->type<<((gpio_handler->pin)-8)*4);
		(gpio_handler->gpio->CRH) |= (gpio_handler->mode<<((((gpio_handler->pin)-8)*4)+2));
	}
}

uint8_t gpio_read_pin(GPIO_Handler_t *gpio_handler)
{
	return 1;
}


void gpio_write_pin(GPIO_Handler_t *gpio_handler, uint8_t value)
{
	switch(value)
	{
	case 0:
		gpio_handler->gpio->ODR &= ~(1<<gpio_handler->pin);
		break;

	case 1:
		gpio_handler->gpio->ODR |= (1<<gpio_handler->pin);
		break;
	}
}

void gpio_toogle_pin(GPIO_Handler_t *gpio_handler)
{
	gpio_handler->gpio->ODR ^= (1<<gpio_handler->pin);
}






















































































































































































































































