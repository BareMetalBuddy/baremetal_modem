#ifndef QUEUE_H_
#define QUEUE_H_

#include "string.h"
#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE_FOR_QUEUE  (32) 	// buffer size
#define NUMBER_OF_QUEUES       (10) // Number of queues to keep messages

typedef struct queues queues;

typedef struct queues
{
	uint8_t buffer[BUFFER_SIZE_FOR_QUEUE];
	queues *next;
}queues;


// public
void static_queue_init(uint8_t number_of_queues);
static void static_queue_restore(queues *ptr);
static void static_queue_set_reference(queues *reference);
uint8_t static_queue_pop_method(uint8_t *ptr);
uint8_t static_queue_push_method(uint8_t *msg);



#endif /* QUEUE_H_ */
