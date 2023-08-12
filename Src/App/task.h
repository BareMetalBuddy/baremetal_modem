
#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef enum {BLOCKED, UNBLOCKED} States_t;
#define TIMER_TICK_RATE (100)


typedef struct {
	uint32_t ticks;
	uint32_t elapsed_time;	// Time since task's last tick
	void (*function)(void);      // Function to call for task's tick
	States_t state;
}Task_t;

void task_init(Task_t *task,uint32_t ticks,uint32_t elapsed_time, void (*f)(), States_t state);
void task_change_period(Task_t *task,uint32_t ticks);
void task_change_state(Task_t *task, States_t state);
void task_delete(void);

#endif
