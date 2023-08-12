
#include <stdint.h>
#include "modem.h"
#include "cli.h"
#include "rcc.h"
#include "status_led.h"
#include "task.h"
#include "timx.h"
#include "watchdog.h"
#include "queue.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

TIMx_Handler_t timx_handler;

#define NUMBER_OF_TASK (4)
void task_1(void);
void task_2(void);
void task_3(void);
void task_4(void);
Task_t task[NUMBER_OF_TASK];


int main(void)
{
	RCC_TIM2_CLOCK_ENABLE();
	timx_init(&timx_handler,TIM2_BASE_ADDRESS,TIM2_PRESCALER_VALUE_FOR_100MS, TIM2_RELOAD_VALUE_FOR_100MS); // init timer 2 with values for 100ms
	timx_config(&timx_handler);
	timx_update_interrupt(&timx_handler, 1);

	modem_init();
	command_line_interface_init();
	status_led_init();
	watchdog_init();

	task_init(&task[0],500,0,&task_1,UNBLOCKED); // status led
	task_init(&task[1],200,0,&task_2,UNBLOCKED); // command line interface
	task_init(&task[2],500,0,&task_3,UNBLOCKED); // watch-dog timer
	task_init(&task[3],1000,0,&task_4,UNBLOCKED);

	while(1){
		if((timx_handler.timx->TIMx_SR) & ((uint16_t)(0x0001))){
			timx_handler.timx->TIMx_SR &= ~((uint16_t)(0x0001));
	    	for (uint8_t i=0; i < NUMBER_OF_TASK; i++) {
	    		if (task[i].elapsed_time >= task[i].ticks && task[i].state) {
	    			task[i].function();
	    		    task[i].elapsed_time = 0;
	    		}
	    		task[i].elapsed_time += TIMER_TICK_RATE; 	// Increment the elapsed time of the task by the timer tick rate
	    	}
	    }
	}
}

void task_1(void)
{
	status_led_toogle();
}

void task_2(void)
{
	command_line_interface();
}

void task_3(void)
{
	watchdog_reset();
}

void task_4(void)
{
	modem_test_msg();
}
