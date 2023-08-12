#ifndef IWDT_H_
#define IWDT_H_

#include <stdint.h>

#define IWDT_BASE_ADDRESS (0x40003000)
#define IWDT_PRESCALER_3_2_SEC (3)
#define IWDT_PRESCALER_1_6_SEC (2)


typedef struct
{
	volatile uint32_t IWDG_KR;
	volatile uint32_t IWDG_PR;
	volatile uint32_t IWDG_RLR;
	volatile uint32_t IWDG_SR;

}IWDT_reg;

typedef struct
{
	volatile IWDT_reg* iwdt;
}IWDT_handler;

void iwdt_init(IWDT_handler* iwdt_handler,uint32_t base_address);
void iwdt_config(IWDT_handler* iwdt_handler,uint8_t prescaler);
void iwdt_reset(IWDT_handler* iwdt_handler);
void iwdt_start_counter(IWDT_handler* iwdt_handler);

#endif /* IWDT_H_ */
