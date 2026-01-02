#include "Ringbuffer.h"
#include<stddef.h>
bool RB_init(RB *rb,uint8_t *buff,uint16_t size){
    if(rb == NULL || buff == NULL || size < 2){
        return false;
    }
    rb->head = 0;
    rb->tail = 0;
    rb->size = size;
    rb->buff = buff;
    return true;
}
bool RB_write(RB *rb,uint8_t data){
    if(RB_isfull(rb)){
        return false;
    }
    rb->buff[rb->head] = data;
    rb->head = (rb->head + 1U) % rb->size;
    return true;
}
bool RB_read(RB *rb,uint8_t *data){
    if(RB_isempty(rb)){
        return false;
    }
    *data = rb->buff[rb->tail];
    rb->tail = (rb->tail + 1U) % rb->size;
    return true;
}
bool RB_isfull(RB *rb){
    if(((rb->head + 1U) % rb->size) == rb->tail){
        return true;
    }
    return false;
}
bool RB_isempty(RB *rb){
    if(rb->head == rb->tail){
        return true;
    }
    return false;
}
