
#ifndef APP_ANALOG_SENSOR_1_H_
#define APP_ANALOG_SENSOR_1_H_

#include "adc.h"
#include "rcc.h"
#include "gpio.h"
#include "adc.h"

void analog_sensor_1_init(void);
uint32_t analog_sensor_1_read(void);


#endif /* APP_ANALOG_SENSOR_1_H_ */
