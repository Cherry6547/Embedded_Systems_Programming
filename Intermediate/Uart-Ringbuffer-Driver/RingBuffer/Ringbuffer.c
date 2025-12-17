#include "Ringbuffer.h"
#include <stddef.h>

/*
 * RB_init
 *
 * Initializes the ring buffer control structure.
 * The buffer memory is supplied by the caller to avoid
 * dynamic allocation and keep the design deterministic.
 */
bool RB_init(RB *rb, uint8_t *buff, uint16_t size)
{
    /* Validate input parameters */
    if ((rb == NULL) || (buff == NULL) || (size < 2U))
    {
        return false;
    }

    /* Initialize buffer indices */
    rb->head = 0U;
    rb->tail = 0U;

    /* Store buffer metadata */
    rb->size = size;
    rb->buff = buff;

    return true;
}

/*
 * RB_write
 *
 * Writes one byte into the ring buffer.
 * This function is non-blocking. If the buffer is full,
 * the write operation fails.
 */
bool RB_write(RB *rb, uint8_t data)
{
    /* Check for invalid buffer or full condition */
    if ((rb == NULL) || RB_isfull(rb))
    {
        return false;
    }

    /* Store data at the current head position */
    rb->buff[rb->head] = data;

    /* Advance head index with wrap-around */
    rb->head = (rb->head + 1U) % rb->size;

    return true;
}

/*
 * RB_read
 *
 * Reads one byte from the ring buffer.
 * This function is non-blocking. If the buffer is empty,
 * no data is read.
 */
bool RB_read(RB *rb, uint8_t *data)
{
    /* Validate input parameters and check empty condition */
    if ((rb == NULL) || (data == NULL) || RB_isempty(rb))
    {
        return false;
    }

    /* Read data from the current tail position */
    *data = rb->buff[rb->tail];

    /* Advance tail index with wrap-around */
    rb->tail = (rb->tail + 1U) % rb->size;

    return true;
}

/*
 * RB_isfull
 *
 * Checks whether the ring buffer is full.
 * One slot is left unused to distinguish full from empty.
 */
bool RB_isfull(RB *rb)
{
    if (rb == NULL)
    {
        return true;
    }

    return (((rb->head + 1U) % rb->size) == rb->tail);
}

/*
 * RB_isempty
 *
 * Checks whether the ring buffer is empty.
 */
bool RB_isempty(RB *rb)
{
    if (rb == NULL)
    {
        return true;
    }

    return (rb->head == rb->tail);
}
