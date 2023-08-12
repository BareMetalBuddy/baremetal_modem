#include "iwdt.h"

void iwdt_init(IWDT_handler* iwdt_handler,uint32_t base_address)
{
	iwdt_handler->iwdt = (IWDT_reg*)base_address;
}

void iwdt_config(IWDT_handler* iwdt_handler,uint8_t prescaler)
{
	// unblock IWDG_PR and IWDG_RLR
	iwdt_handler->iwdt->IWDG_KR = 0x5555;

	// set prescaler
	iwdt_handler->iwdt->IWDG_PR= prescaler;

	// set reload counter
	iwdt_handler->iwdt->IWDG_RLR =  0xFFF;

	// Block IWDG_PR and IWDG_RLR register
	iwdt_handler->iwdt->IWDG_KR = 0x0000;

	// Reset reload counter
	iwdt_handler->iwdt->IWDG_KR = 0xAAAA;
}

void iwdt_start_counter(IWDT_handler* iwdt_handler)
{
	iwdt_handler->iwdt->IWDG_KR = 0xCCCC;
}

void iwdt_reset(IWDT_handler* iwdt_handler)
{
	iwdt_handler->iwdt->IWDG_KR = 0xAAAA;
}
