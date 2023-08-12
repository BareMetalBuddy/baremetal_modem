#include "ring_buffer.h"

/**
 * Ring buffer type.
 *
 * The buffer is empty when head == tail.
 *
 * The buffer is full when the head is one byte in front of the tail,
 * modulo buffer length.
 *
 * One byte is left free to distinguish empty from full. */

/**
 * Initialize a ring buffer.
 *
 *  @param rb   Instance to initialize
 *
 *  @param size Number of items in buf.  The ring buffer will always
 *              leave one element unoccupied, so the maximum number of
 *              elements it can store will be size - 1.  Thus, size
 *              must be at least 2.
 *
 *  @param buf  Buffer to store items into
 */
void rb_init(ring_buffer *rb, unsigned short size, unsigned char *buf) {
    rb->head = 0;
    rb->tail = 0;
    rb->size = size - 1;
    rb->buf = buf;
}

/**
 * @brief Return the number of elements stored in the ring buffer.
 * @param rb Buffer whose elements to count.
 */
unsigned short rb_full_count(ring_buffer *rb) {
	volatile ring_buffer *arb = rb;
    int size = arb->tail - arb->head;
    if (arb->tail < arb->head) {
        size += arb->size + 1;
    }
    return (unsigned short)size;
}

/**
 * @brief Returns true if and only if the ring buffer is full.
 * @param rb Buffer to test.
 */
int rb_is_full(ring_buffer *rb) {
    return (rb->tail + 1 == rb->head) ||
        (rb->tail == rb->size && rb->head == 0);
}

/**
 * @brief Returns true if and only if the ring buffer is empty.
 * @param rb Buffer to test.
 */
int rb_is_empty(ring_buffer *rb) {
    return rb->head == rb->tail;
}

/**
 * Append element onto the end of a ring buffer.
 * @param rb Buffer to append onto.
 * @param element Value to append.
 */
void rb_insert(ring_buffer *rb, unsigned char element) {
    rb->buf[rb->tail] = element;
    rb->tail = (rb->tail == rb->size) ? 0 : rb->tail + 1;
}

/**
 * @brief Remove and return the first item from a ring buffer.
 * @param rb Buffer to remove from, must contain at least one element.
 */
unsigned char rb_remove(ring_buffer *rb) {
    unsigned char ch = rb->buf[rb->head];
    rb->head = (rb->head == rb->size) ? 0 : rb->head + 1;
    return ch;
}

/**
 * @brief Attempt to remove the first item from a ring buffer.
 *
 * If the ring buffer is nonempty, removes and returns its first item.
 * If it is empty, does nothing and returns a negative value.
 *
 * @param rb Buffer to attempt to remove from.
 */
short rb_safe_remove(ring_buffer *rb) {
    return rb_is_empty(rb) ? -1 : rb_remove(rb);
}

/**
 * @brief Attempt to insert an element into a ring buffer.
 *
 * @param rb Buffer to insert into.
 * @param element Value to insert into rb.
 * @sideeffect If rb is not full, appends element onto buffer.
 * @return If element was appended, then true; otherwise, false. */
int rb_safe_insert(ring_buffer *rb, unsigned char element) {
    if (rb_is_full(rb)) {
        return 0;
    }
    rb_insert(rb, element);
    return 1;
}

/**
 * @brief Append an item onto the end of a non-full ring buffer.
 *
 * If the buffer is full, removes its first item, then inserts the new
 * element at the end.
 *
 * @param rb Ring buffer to insert into.
 * @param element Value to insert into ring buffer.
 * @return On success, returns -1.  If an element was popped, returns
 *         the popped value.
 */
int rb_push_insert(ring_buffer *rb, unsigned char element) {
    int ret = -1;
    if (rb_is_full(rb)) {
        ret = rb_remove(rb);
    }
    rb_insert(rb, element);
    return ret;
}

/**
 * @brief Discard all items from a ring buffer.
 * @param rb Ring buffer to discard all items from.
 */
void rb_reset(ring_buffer *rb) {
    rb->tail = rb->head;
}
