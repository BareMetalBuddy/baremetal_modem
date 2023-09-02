
#ifndef DRIVERS_ADC_H_
#define DRIVERS_ADC_H_

#include <stdint.h>

//configure the ADC pin that we want to use and enable enable clock access to this pin (D15(A0)) -> PC0/ADC10


#define ADC1_BASE_ADDRESS (0X40012400)
#define ADC2_BASE_ADDRESS (0X40012800)

typedef struct
{
	volatile uint32_t ADC_SR;
	volatile uint32_t ADC_CR1;
	volatile uint32_t ADC_CR2;
	volatile uint32_t ADC_SMPR1;
	volatile uint32_t ADC_SMPR2;
	volatile uint32_t ADC_JOFR1;
	volatile uint32_t ADC_JOFR2;
	volatile uint32_t ADC_JOFR3;
	volatile uint32_t ADC_JOFR4;
	volatile uint32_t ADC_HTR;
	volatile uint32_t ADC_LTR;
	volatile uint32_t ADC_SQR1;
	volatile uint32_t ADC_SQR2;
	volatile uint32_t ADC_SQR3;
	volatile uint32_t ADC_JSQR;
	volatile uint32_t ADC_JDR1;
	volatile uint32_t ADC_JDR2;
	volatile uint32_t ADC_JDR3;
	volatile uint32_t ADC_JDR4;
	volatile uint32_t ADC_DR;

}ADC_Reg_t;

typedef struct
{
	volatile ADC_Reg_t *adcx;
}ADC_Handler_t;

void adc_init(ADC_Handler_t *adcx,uint32_t base_address_adc_selected, uint8_t channel);
void adc_start_conversion(ADC_Handler_t *adcx);
uint32_t adc_read(ADC_Handler_t *adcx);

#endif /* DRIVERS_ADC_H_ */
