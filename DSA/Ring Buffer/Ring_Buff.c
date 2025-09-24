/******************************************************************************
 * Simple Ring Buffer (Circular Buffer) Implementation in C
 *
 * Author: Your Name
 * License: MIT
 *
 * A ring buffer is a fixed-size FIFO (first-in, first-out) data structure
 * that wraps around when it reaches the end of the buffer.
 * This implementation supports single-byte put/get operations.
 ******************************************************************************/

#include <stdio.h>

/* Ring buffer structure */
typedef struct {
    int head;       // index where next byte will be written
    int tail;       // index where next byte will be read
    char *buff;     // pointer to buffer array
    int size;       // total buffer size
} Ring_Buff;

/* Initialize the ring buffer */
void RB_init(Ring_Buff *rb, char *buff, int size) {
    rb->head = 0;
    rb->tail = 0;
    rb->buff = buff;
    rb->size = size;
}

/* Check if buffer is full */
int RB_isFull(Ring_Buff *rb) {
    return ((rb->head + 1) % rb->size == rb->tail);
}

/* Check if buffer is empty */
int RB_isEmpty(Ring_Buff *rb) {
    return (rb->head == rb->tail);
}

/* Insert one character into buffer */
int RB_Put(Ring_Buff *rb, char data) {
    if (RB_isFull(rb)) {
        printf("RB is FULL\n");
        return 0; // fail
    } else {
        rb->buff[rb->head] = data;
        rb->head = (rb->head + 1) % rb->size; // wrap-around
        return 1; // success
    }
}

/* Retrieve one character from buffer */
int RB_Get(Ring_Buff *rb, char *data) {
    if (RB_isEmpty(rb)) {
        printf("RB is EMPTY\n");
        return 0; // fail
    } else {
        *data = rb->buff[rb->tail];
        rb->tail = (rb->tail + 1) % rb->size; // wrap-around
        return 1; // success
    }
}

/* ---------------------- Test Code ---------------------- */
int main() {
    Ring_Buff rb;
    char buff[6];  // buffer of size 6, effective capacity = 5
    char data;

    RB_init(&rb, buff, 6);

    // Fill the buffer with some test data
    for (char c = 'A'; c <= 'E'; c++) {
        RB_Put(&rb, c);
    }

    printf("Buffer full? %d\n", RB_isFull(&rb));

    // Read back all the data
    while (!RB_isEmpty(&rb)) {
        if (RB_Get(&rb, &data)) {
            printf("Got: %c\n", data);
        }
    }

    printf("Buffer empty? %d\n", RB_isEmpty(&rb));
    return 0;
}
