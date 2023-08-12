#ifndef DRIVERS_INCLUDE_GPIO_H_
#define DRIVERS_INCLUDE_GPIO_H_

#include <stdint.h>

#define GPIOA_BASE_ADDRESS (0x40010800)
#define GPIOB_BASE_ADDRESS (0x40010C00)
#define GPIOC_BASE_ADDRESS (0x40011000)
#define GPIOD_BASE_ADDRESS (0x40011400)
#define GPIOE_BASE_ADDRESS (0x40011800)
#define GPIOF_BASE_ADDRESS (0x40011C00)
#define GPIOG_BASE_ADDRESS (0x40012000)

#define RESET_REGISTER 0x03

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_Reg_t;

typedef enum
{
	GPIO_Analog_Mode=0,
	GPIO_Floating_input,
	GPIO_Input,
	GPIO_Reserved
}GPIO_Input_Mode_t;

typedef enum
{
	GPIO_General_purpose_output_push_pull=0,
	GPIO_General_purpose_output_Open_drain,
	GPIO_Alternate_function_output_Push_pull,
	GPIO_Alternate_function_output_Open_drain
}GPIO_Output_Mode_t;

typedef enum
{
	GPIO_Input_mode = 0,
	GPIO_Output_mode_max_speed_10_MHz,
	GPIO_Output_mode_max_speed_2_MHz,
	GPIO_Output_mod_max_speed_50_MHz
}GPIO_Mode_t;

typedef enum
{
	GPIO_pin_0=0,
	GPIO_pin_1,
	GPIO_pin_2,
	GPIO_pin_3,
	GPIO_pin_4,
	GPIO_pin_5,
	GPIO_pin_6,
	GPIO_pin_7,
	GPIO_pin_8,
	GPIO_pin_9,
	GPIO_pin_10,
	GPIO_pin_11,
	GPIO_pin_12,
	GPIO_pin_13,
	GPIO_pin_14,
	GPIO_pin_15

}GPIO_Pin_t;

typedef struct{
	uint8_t type;
	uint8_t pin;
	uint8_t mode;
	volatile GPIO_Reg_t *gpio;
}GPIO_Handler_t;



void gpio_init(GPIO_Handler_t *gpio_handler,uint32_t base_address,uint8_t pin, uint8_t mode,uint8_t type);
void gpio_config(GPIO_Handler_t *gpio_handler);
uint8_t gpio_read_pin(GPIO_Handler_t *gpio_handler);
void gpio_write_pin(GPIO_Handler_t *gpio_handler, uint8_t value);
void gpio_toogle_pin(GPIO_Handler_t *gpio_handler);


#endif /* DRIVERS_INCLUDE_GPIO_H_ */
