#ifndef BSP_H_
#define BSP_H_

/*We are using a OLIMEXINO-STM32 board: https://www.olimex.com/Products/Duino/STM32/OLIMEXINO-STM32/open-source-hardware*/

#define SYSTEM_CLOCK 					(8000000)
#define BAUDRATE 						(115200)
#define TIM2_PRESCALER_VALUE_FOR_100MS 	(31999)
#define TIM2_RELOAD_VALUE_FOR_100MS 	(24)
#define SERIAL_BUFFER_SIZE 				(96)

#define SERIAL_PORT_1 0
#define SERIAL_PORT_2 1
#define SERIAL_PORT_3 2
#define GPIO_PORT_A 3
#define GPIO_PORT_B 4
#define GPIO_PORT_C 5
#define GPIO_PORT_D 6
#define BASIC_TIMER_6 7
#define BASIC_TIMER_7 8
#define ADC1 9
#define ADC2 10
#define RESET 0



#endif /* BSP_H_ */
