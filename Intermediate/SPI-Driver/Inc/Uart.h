#ifndef UART_H
#define UART_H

#include "Ringbuffer.h"
#include <stdbool.h>
#include<stdint.h>

bool uart2_init(uint32_t baudrate, uint32_t sysclk);
bool uart2_write(uint8_t *buff, uint16_t len);
bool uart2_read(uint8_t *byte);
void uart2_tx_isr_handler();
void uart2_rx_isr_handler();
void log_uart(const char *str);
#endif
