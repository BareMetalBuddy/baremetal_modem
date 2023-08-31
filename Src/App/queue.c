
#include "queue.h"

queues *header;
queues *tail;
queues list_of_queues[NUMBER_OF_QUEUES];


void static_queue_init(uint8_t number_of_queues){
	header = &list_of_queues[0];
	for (int i = 0; i < number_of_queues - 1; i++) {
		list_of_queues[i].next = &list_of_queues[i + 1];
	}
	list_of_queues[number_of_queues - 1].next = '\0';  // last node

	tail = '\0';
}

static void static_queue_restore(queues *ptr)
{
	queues* aux;
	aux = header;

	if (aux != '\0')
	{
		while (aux->next != '\0')
		aux = aux->next;
		ptr->next = '\0';
		aux->next = ptr;
	}
	else
	{
		header = ptr;
		ptr->next = '\0';
	}
}

static void static_queue_set_reference(queues *reference)
{
	queues* aux;
	aux = tail;

	if (aux != '\0')
	{
		while (aux->next != '\0')
			aux = aux->next;
		reference->next = '\0';
		aux->next = reference;
	}
	else
	{
		tail = reference;
	}
}

uint8_t static_queue_pop_method(uint8_t *ptr)
{
	queues* aux;
	uint8_t result = 1;

	if (tail != '\0')
	{
		if (tail->next != '\0')
		{
			aux = tail->next;
			memcpy(ptr, tail->buffer,strlen(tail->buffer)+1);
			static_queue_restore(tail);
			tail = aux;
		}
		else
		{
			memcpy(ptr, tail->buffer,strlen(tail->buffer)+1);
			static_queue_restore(tail);
			tail = '\0';
		}
	}
	else
	{
		result = 0;
	}
	return result;
}

uint8_t static_queue_push_method(uint8_t *msg)
{
	queues *aux;

	if(header != '\0') // si header es distinto de null
	{
		if (header->next != '\0') {
			aux = header->next;
			memcpy(header->buffer,(const char*)msg,strlen(msg)+1);
			header->next = '\0';
			static_queue_set_reference(header);
			header = aux;
		}
		else
		{
			memcpy(header->buffer,(const char*)msg,strlen(msg)+1);
			static_queue_set_reference(header);
			header = '\0';
		}
	}
	else
	{
		return 0;
	}
	return 1;
}
