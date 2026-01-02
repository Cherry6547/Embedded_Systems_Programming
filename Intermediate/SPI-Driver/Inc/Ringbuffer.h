#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include<stdint.h>
#include<stdbool.h>

typedef struct {
    volatile uint8_t head;
    volatile uint8_t tail;
    uint16_t size;
    uint8_t *buff;
}RB;

bool RB_init(RB *rb,uint8_t *buff,uint16_t size);
bool RB_write(RB *rb,uint8_t data);
bool RB_read(RB *rb,uint8_t *data);
bool RB_isfull(RB *rb);
bool RB_isempty(RB *rb);

#endif
