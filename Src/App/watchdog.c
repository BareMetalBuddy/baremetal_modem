#include "watchdog.h"

static IWDT_handler iwdt;

void watchdog_init(void)
{
	iwdt_init(&iwdt, IWDT_BASE_ADDRESS);
	iwdt_config(&iwdt, IWDT_PRESCALER_1_6_SEC);
	iwdt_start_counter(&iwdt);
}


void watchdog_reset(void)
{
	iwdt_reset(&iwdt);
}
