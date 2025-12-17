#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Ring Buffer Structure
 *
 * This structure holds the state required to manage a circular buffer.
 * The buffer itself is provided externally to keep the implementation
 * flexible and suitable for embedded systems (no dynamic allocation).
 *
 * Design notes:
 * - One slot is intentionally left unused to distinguish FULL vs EMPTY
 * - Buffer capacity = (size - 1)
 * - Intended for single-producer / single-consumer usage
 *   (e.g., ISR ↔ main context)
 */
typedef struct
{
    volatile uint8_t head;   /* Index where next byte will be written */
    volatile uint8_t tail;   /* Index where next byte will be read */
    uint16_t size;           /* Total buffer size */
    uint8_t *buff;           /* Pointer to user-provided buffer memory */
} RB;

/*
 * RB_init
 *
 * Initializes a ring buffer instance.
 *
 * Parameters:
 * - rb   : Pointer to ring buffer control structure
 * - buff : Pointer to memory used as the buffer
 * - size : Size of the buffer in bytes (must be >= 2)
 *
 * Returns:
 * - true  : Initialization successful
 * - false : Invalid parameters
 */
bool RB_init(RB *rb, uint8_t *buff, uint16_t size);

/*
 * RB_write
 *
 * Writes a single byte into the ring buffer.
 *
 * This function is non-blocking. If the buffer is full,
 * the write operation fails and returns false.
 *
 * Parameters:
 * - rb   : Pointer to ring buffer
 * - data : Byte to be written
 *
 * Returns:
 * - true  : Data written successfully
 * - false : Buffer full or invalid pointer
 */
bool RB_write(RB *rb, uint8_t data);

/*
 * RB_read
 *
 * Reads a single byte from the ring buffer.
 *
 * This function is non-blocking. If the buffer is empty,
 * no data is read and the function returns false.
 *
 * Parameters:
 * - rb   : Pointer to ring buffer
 * - data : Pointer where the read byte will be stored
 *
 * Returns:
 * - true  : Data read successfully
 * - false : Buffer empty or invalid pointer
 */
bool RB_read(RB *rb, uint8_t *data);

/*
 * RB_isfull
 *
 * Checks whether the ring buffer is full.
 *
 * Returns:
 * - true  : Buffer is full
 * - false : Buffer has free space
 */
bool RB_isfull(RB *rb);

/*
 * RB_isempty
 *
 * Checks whether the ring buffer is empty.
 *
 * Returns:
 * - true  : Buffer is empty
 * - false : Buffer contains data
 */
bool RB_isempty(RB *rb);

#endif /* RINGBUFFER_H */
