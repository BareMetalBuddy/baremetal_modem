#ifndef APP_ROUTER_H_
#define APP_ROUTER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Package{
	uint8_t * data1;
	uint8_t * data2;
	uint8_t * data3;
	uint8_t * data4;
	uint8_t * data5;
	uint8_t largo;
}Package;

struct DinamicFIFOList {
    struct DinamicFIFOList *next;
    Package *package;
};

typedef struct DinamicFIFOList DinamicFIFOList;

typedef struct RouterControl{
	DinamicFIFOList * create;
	DinamicFIFOList * status;
	DinamicFIFOList * monitoring;
	DinamicFIFOList * connection;
}RouterControl;

uint8_t router_dynamic_fifo_add(Package * package,uint8_t list);
Package* router_dynamic_fifo_get(uint8_t list);

#endif /* APP_ROUTER_H_ */
