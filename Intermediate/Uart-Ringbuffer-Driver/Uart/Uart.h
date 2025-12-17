#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>
#include "Ringbuffer.h"

/*
 * UART Driver Interface
 *
 * This module provides a bare-metal, interrupt-driven UART2 driver
 * for STM32 microcontrollers. The driver uses ring buffers to
 * decouple interrupt context from application context, enabling
 * non-blocking transmit and receive operations.
 *
 * Design goals:
 * - No dynamic memory allocation
 * - Interrupt-driven TX and RX
 * - Non-blocking APIs
 * - Clean separation between driver and application
 */

/*
 * uart2_init
 *
 * Initializes UART2 peripheral, GPIO pins, and internal ring buffers.
 *
 * Parameters:
 * - baudrate : Desired UART baud rate (e.g., 115200)
 * - sysclk   : System clock frequency in Hz
 *
 * Returns:
 * - true  : Initialization successful
 * - false : Invalid parameters
 */
bool uart2_init(uint32_t baudrate, uint32_t sysclk);

/*
 * uart2_write
 *
 * Writes data to UART2 transmit buffer.
 * Data is transmitted asynchronously using interrupts.
 *
 * Parameters:
 * - buff : Pointer to data buffer to transmit
 * - len  : Number of bytes to transmit
 *
 * Returns:
 * - true  : Data accepted for transmission
 * - false : Invalid parameters or buffer full
 */
bool uart2_write(uint8_t *buff, uint16_t len);

/*
 * uart2_read
 *
 * Reads received data from UART2 receive buffer.
 * This function is non-blocking and returns immediately.
 *
 * Parameters:
 * - buff : Pointer to buffer where received data will be copied
 *
 * Returns:
 * - true  : Data was available and copied
 * - false : No data available
 *
 * Note:
 * This function drains the receive ring buffer. For fine-grained
 * control, a byte-wise read API can also be implemented.
 */
bool uart2_read(uint8_t *byte);

/*
 * uart2_tx_isr_handler
 *
 * UART2 transmit interrupt handler.
 * This function should be called from the USART2 IRQ handler
 * when the TXE interrupt is asserted.
 */
void uart2_tx_isr_handler(void);

/*
 * uart2_rx_isr_handler
 *
 * UART2 receive interrupt handler.
 * This function should be called from the USART2 IRQ handler
 * when the RXNE interrupt is asserted.
 */
void uart2_rx_isr_handler(void);

#endif /* UART_H */
