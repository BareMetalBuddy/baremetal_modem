#include <status_led.h>

static GPIO_Handler_t status_led;

void status_led_init()
{
	rcc_enable_clock(GPIO_PORT_A);
	gpio_init(&status_led,GPIOA_BASE_ADDRESS,GPIO_pin_5,GPIO_General_purpose_output_push_pull,GPIO_Output_mode_max_speed_10_MHz);
	gpio_config(&status_led);
	gpio_write_pin(&status_led,0);
}

void status_led_toogle()
{
	gpio_toogle_pin(&status_led);
}

void status_led_on()
{
	gpio_write_pin(&status_led,1);
}

void status_led_off()
{
	gpio_write_pin(&status_led,0);
}

