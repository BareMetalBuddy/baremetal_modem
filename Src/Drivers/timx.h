
#ifndef TIMX_H_
#define TIMX_H_

#include <stdint.h>

#define TIM1_BASE_ADDRESS (0x40012C00)
#define TIM2_BASE_ADDRESS (0x40000000)
#define TIM3_BASE_ADDRESS (0x40000400)
#define TIM4_BASE_ADDRESS (0x40000800)
#define TIM5_BASE_ADDRESS (0x40000C00)
#define TIM6_BASE_ADDRESS (0x40001000)
#define TIM7_BASE_ADDRESS (0x40001400)
#define TIM8_BASE_ADDRESS (0x40013400)

// General-purpose timers (TIM2 to TIM5)
typedef struct{
	volatile uint32_t TIMx_CR1;
	volatile uint32_t TIMx_CR2;
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t TIMx_CCMR2;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
	uint32_t reserver1;
	volatile uint32_t TIMx_CCR1;
	volatile uint32_t TIMx_CCR2;
	volatile uint32_t TIMx_CCR3;
	volatile uint32_t TIMx_CCR4;
	uint32_t reserver2;
	volatile uint32_t TIMx_DCR;
	volatile uint32_t TIMx_DMAR;

}GeneralPurposeTimx_Reg_t;


typedef struct{
	uint16_t period;
	uint16_t prescaler;
	volatile GeneralPurposeTimx_Reg_t *timx;
}TIMx_Handler_t;


void timx_init(TIMx_Handler_t *timx_handler,uint32_t base_address,uint32_t period, uint32_t prescaler);
void timx_config(TIMx_Handler_t *timx_handler);
void timx_update_interrupt(TIMx_Handler_t *timx_handler,uint8_t status);



#endif /* TIMX_H_ */
