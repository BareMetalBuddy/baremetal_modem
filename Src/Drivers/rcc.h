
#ifndef DRIVERS_INCLUDE_RCC_H_
#define DRIVERS_INCLUDE_RCC_H_

#include <stdint.h>
#include "bsp.h"

#define RCC_BASE_ADDRESS (0x40021000)
#define RCC_AHBENR  (RCC_BASE_ADDRESS + 0x14)
#define RCC_APB1ENR (RCC_BASE_ADDRESS + 0x1C)
#define RCC_APB2ENR (RCC_BASE_ADDRESS + 0x18)
#define RCC_BDCR (RCC_BASE_ADDRESS + 0x20)

// GPIO's enable clock
#define RCC_GPIOA_CLOCK_ENABLE() (*((uint32_t*)RCC_APB2ENR) |= (1<<2))
#define RCC_GPIOB_CLOCK_ENABLE() (*((uint32_t*)RCC_APB2ENR) |= (1<<3))
#define RCC_GPIOC_CLOCK_ENABLE() (*((uint32_t*)RCC_APB2ENR) |= (1<<4))
#define RCC_GPIOD_CLOCK_ENABLE() (*((uint32_t*)RCC_APB2ENR) |= (1<<5))
#define RCC_GPIOE_CLOCK_ENABLE() (*((uint32_t*)RCC_APB2ENR) |= (1<<6))

// Basic timers (TIM6 and TIM7) enable clock
#define RCC_TIM6_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<4))
#define RCC_TIM7_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<5))
#define RCC_TIM2_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<0))

// USARTs enable clock
#define RCC_USART1_CLOCK_ENABLE() (*((uint32_t*)RCC_APB2ENR) |=(1<<14))
#define RCC_USART2_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<17))
#define RCC_USART3_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<18))

// I2C bus enable clock
#define RCC_I2C1_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<21))
#define RCC_I2C2_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |=(1<<22))

// ADC1, ADC2 and ADC3 bus enable clock
#define ADC1_CLOCK_ENABLE()     (*((uint32_t*)RCC_APB2ENR) |=(1<<9))
#define ADC2_CLOCK_ENABLE()     (*((uint32_t*)RCC_APB2ENR) |=(1<<10))


/*After reset, access to the Backup registers and RTC is disabled and the Backup domain
(BKP) is protected against possible parasitic write access. To enable access to the Backup
registers and the RTC, proceed as follows:

- enable the power and backup interface clocks by setting the PWREN and BKPEN bits
in the RCC_APB1ENR register
- set the DBP bit the Power Control register (PWR_CR) to enable access to the Backup
registers and RTC.*/

#define RCC_BACKUP_INTERFACE_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |= (1<<27))
#define RCC_POWER_INTERFACE_CLOCK_ENABLE() (*((uint32_t*)RCC_APB1ENR) |= (1<<28))

#define RCC_LSE_OSC_ENABLE() (*((uint32_t*)RCC_BDCR) |= (1<<0))
#define RCC_LSE_OSC_READY() (*((uint32_t*)RCC_BDCR) & (1<<1))

// set 1 ->  RTC clock enable.
#define RCC_RTC_CLOCK_ENABLE() (*((uint32_t*)RCC_BDCR) |= (1<<15))

// set 1 -> Resets the entire Backup domain
#define RCC_RESET_BACKUP_DOMAIN() (*((uint32_t*)RCC_BDCR) |= (1<<16))
#define RCC_RESET_BACKUP_DOMAIN_NOT_ACTIVATED() (*((uint32_t*)RCC_BDCR) &= ~(1<<16))

/*
RTC clock source selection
00: No clock
01: LSE oscillator clock used as RTC clock
10: LSI oscillator clock used as RTC clock
11: HSE oscillator clock divided by 128 used as RTC clock
*/
#define RCC_RTC_CLOCK_SOURCE_SEL(X) (*((uint32_t*)RCC_BDCR) |= (X<<8))


void rcc_enable_clock(uint8_t module);

#endif /* DRIVERS_INCLUDE_RCC_H_ */
