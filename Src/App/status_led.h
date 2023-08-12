
#ifndef APP_STATUS_LED_H_
#define APP_STATUS_LED_H_

#include "gpio.h"
#include "rcc.h"


void status_led_init();
void status_led_toogle();
void status_led_on();
void status_led_off();


#endif /* APP_STATUS_LED_H_ */
