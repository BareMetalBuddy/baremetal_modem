#ifndef APP_MODEM_H_
#define APP_MODEM_H_

#include <stdint.h>
#include <stdio.h>
#include "usart.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "bsp.h"
#include "at_command.h"
#include "queue.h"

#define SEND_AT_CMD (0)
#define WAIT_FOR_AT_CMD_ANSWER (1)

void modem_init(void);
void modem_test_msg(void);
void modem_flush(void);
uint8_t modem_at_command_write(uint8_t* at_cmd, uint8_t id, uint16_t timeout);


#endif /* APP_MODEM_H_ */
