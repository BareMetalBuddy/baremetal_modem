#include <timx.h>

void timx_init(TIMx_Handler_t *timx_handler,uint32_t base_address,uint32_t period, uint32_t prescaler)
{
	timx_handler->timx = (GeneralPurposeTimx_Reg_t*)base_address;
	timx_handler->period = period;
	timx_handler->prescaler = prescaler;
}

void timx_config(TIMx_Handler_t *timx_handler)
{
	timx_handler->timx->TIMx_ARR = timx_handler->period;
	timx_handler->timx->TIMx_PSC = timx_handler->prescaler;
	timx_handler->timx->TIMx_EGR = 1; 		// Re-initializes the timer counter and generates an update of the registers.
	timx_handler->timx->TIMx_CR1 |= (1<<0); // Counter enabled
}


void timx_update_interrupt(TIMx_Handler_t *timx_handler,uint8_t status)
{
	if(status == 1){
		timx_handler->timx->TIMx_DIER |= (1<<0);
	}else if(status == 0){
		timx_handler->timx->TIMx_DIER &= ~(1<<0);
	}
	else{}
}

