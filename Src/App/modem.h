#ifndef APP_MODEM_H_
#define APP_MODEM_H_

#include <stdint.h>
#include <stdio.h>
#include "usart.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "bsp.h"
#include "queue.h"


void modem_init(void);
void modem_test_msg(void);


#endif /* APP_MODEM_H_ */
