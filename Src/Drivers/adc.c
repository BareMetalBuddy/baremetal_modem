#include "adc.h"

void adc_init(ADC_Handler_t *adcx,uint32_t base_address_adc_selected, uint8_t channel)
{
	adcx->adcx = (ADC_Reg_t*)base_address_adc_selected;

	/*For a unknown reason the ADC enable register must be configured twice*/
	adcx->adcx->ADC_CR2 |= (1<<0); 		// Enable ADC
	for (volatile uint32_t delay = 0; delay < 1000; delay++);
	adcx->adcx->ADC_CR2 |= (1<<0); 		// Enable ADC

	adcx->adcx->ADC_CR2 |= (1<<2); 			// ADC Calibration
	while (adcx->adcx->ADC_CR2  & (1<<2)); 	// Wait for the calibration is completed
	adcx->adcx->ADC_CR2 |= (1<<1);   		// set mode continuous conversion
	adcx->adcx->ADC_CR2 &= ~(1<<20);
	adcx->adcx->ADC_SMPR1 |= (4<<0); 		// Set Sample time selection - 100: 41.5 cycles
	adcx->adcx->ADC_SQR3 = channel; 		// Set channel
}

void adc_start_conversion(ADC_Handler_t *adcx){}

uint32_t adc_read(ADC_Handler_t *adcx)
{
	adcx->adcx->ADC_CR2 |= (1<<22); 				// Start ADC conversion
	while (!(adcx->adcx->ADC_SR & (1<<1))); 		// wait for conversion to be complete

	return adcx->adcx->ADC_DR; // read converted value
}
