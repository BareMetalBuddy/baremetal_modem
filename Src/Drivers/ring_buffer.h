
/**
 * @file ring_buffer.h
 * @brief Simple circular buffer
 *
 * This implementation is not thread-safe.  In particular, none of
 * these functions is guaranteed re-entrant.
 */

#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

typedef struct ring_buffer {
    volatile unsigned char *buf; /**< Buffer items are stored into */
    unsigned short head;         /**< Index of the next item to remove */
    unsigned short tail;         /**< Index where the next item will get inserted */
    unsigned short size;         /**< Buffer capacity minus one */
} ring_buffer;


void rb_init(ring_buffer *rb, unsigned short size, unsigned char *buf);

unsigned short rb_full_count(ring_buffer *rb) ;

int rb_is_full(ring_buffer *rb);

int rb_is_empty(ring_buffer *rb);

void rb_insert(ring_buffer *rb, unsigned char element);

unsigned char rb_remove(ring_buffer *rb);

short rb_safe_remove(ring_buffer *rb);

int rb_safe_insert(ring_buffer *rb, unsigned char element);

int rb_push_insert(ring_buffer *rb, unsigned char element);

void rb_reset(ring_buffer *rb);



#endif

