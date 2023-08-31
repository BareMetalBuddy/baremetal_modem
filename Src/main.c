
#include <stdint.h>
#include "cli.h"
#include "rcc.h"
#include "status_led.h"
#include "task.h"
#include "timx.h"
#include "watchdog.h"
#include "at_command.h"
#include "router.h"


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

	at_command_init();
	command_line_interface_init();
	status_led_init();
	//watchdog_init();

	static_queue_init(NUMBER_OF_QUEUES);

	task_init(&task[0],500,0,&task_1,UNBLOCKED); //
	task_init(&task[1],200,0,&task_2,UNBLOCKED); // command line interface
	task_init(&task[2],500,0,&task_3,UNBLOCKED); // watch-dog timer
	task_init(&task[3],200,0,&task_4,BLOCKED);

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

/*Helper task.*/
void task_1(void)
{
	Package *package1;
	Package *package2;
	Package *package3;

	if((package1 = router_dynamic_fifo_get(0))!=NULL){
		if(strstr((const char*)package1->data1,(const char*)"set")){
			printf("%s\n",package1->data1);
		}
	}

	if((package2 = router_dynamic_fifo_get(1))!=NULL){
		if(strstr((const char*)package2->data1,(const char*)"wap.tmovil.cl")){
			printf("%s\n",package2->data1);
		}
	}

	if((package3 = router_dynamic_fifo_get(2))!=NULL){
		if(strstr((const char*)package3->data1,(const char*)"TCP")){
			printf("%s\n",package3->data1);
		}
	}
}

void task_2(void)
{
	command_line_interface();
}

void task_3(void)
{
	//watchdog_reset();
}

// array with the name of at command functions
result_codes (* socket_state_machine[])(void) = {
		at_command_test,
		at_command_echo,
		at_command_cpin,
		at_command_creg,
		at_command_cgatt,
		at_command_cgdcont,
		at_command_qnetopen,
		at_command_wait_new_msg,
		at_command_netopen,
		at_command_cipopen,
		at_command_cipsend,
		at_command_send_data,
		at_command_cipclose,
		at_command_netclose
};

volatile socket_state_machine_codes socket_state = at_test_state;
result_codes rc;
result_codes (* fun)(void);

// each column represent a state : OK, FAIL, WAIT
const socket_state_machine_codes lookup_transitions [14][3] = {
	{at_echo_state, at_test_state,at_test_state}, 	 			 	// at_test
	{at_cpin_state,at_test_state,at_echo_state}, 	 			 	// at_echo
	{at_creg_state, at_test_state,at_cpin_state}, 	 			 	// at_cpin
	{at_cgatt_state, at_cpin_state,at_creg_state},	 			 	// at_creg
	{at_cgdcont_state,at_creg_state,at_cgatt_state}, 			 	// at_cgatt
	{at_qnetopen_state,at_creg_state,at_cgdcont_state}, 	 		// at_command_cgdcont
	{at_wait_new_msg_state,at_netclose_state,at_qnetopen_state},    // at_command_qnetopen
	{at_netopen_state,at_test_state,at_wait_new_msg_state}, // at_wait_new_msg_state
	{at_cipopen_state,at_netclose_state,at_netopen_state}, 	// at_netopen_state
	{at_cipsend_state,at_netclose_state,at_cipopen_state},	// at_cipopen_state
	{at_send_data_state,at_test_state,at_cipsend_state},    // at_cipsend_state
	{at_cipclose_state,at_test_state,at_send_data_state},   // at_send_data_state
	{at_netclose_state,at_test_state,at_cipclose_state},    // at_cipclose_state
	{at_wait_new_msg_state,at_test_state,at_netclose_state} // at_netclose_state
};

void task_4(void)
{
	status_led_toogle();
	fun = socket_state_machine[socket_state];
	rc = fun();
	socket_state = lookup_transitions[socket_state][rc];
	status_led_toogle();
}



