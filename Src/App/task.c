#include <task.h>


void task_init(Task_t *task,uint32_t ticks,uint32_t elapsed_time, void (*f)(), States_t state)
{
	task->ticks		    	= ticks;
	task->elapsed_time		= elapsed_time;
	task->function		    = f;
	task->state				= state;
}

void task_change_period(Task_t *task, uint32_t ticks)
{
	task->ticks		     = ticks;
	task->elapsed_time   = 0;
}

void task_change_state(Task_t *task, States_t state)
{
	task->state = state;
}

void task_delete(void)
{

}
