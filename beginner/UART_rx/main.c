#include "stm32f446re.h"
#include <string.h>

#define size 64
volatile char Buff[size];       // Buffer to store received characters
volatile uint8_t ready = 0;     // Flag to indicate full command is received
volatile uint8_t cmd_index = 0; // Buffer index

void setup() {
    // Enable GPIOA and USART2
    RCC_AHB1ENR |= (1 << 0);
    RCC_APB1ENR |= (1 << 17);

    // Set PA2 (TX) and PA3 (RX) to Alternate Function mode
    GPIOA_MODER &= ~(0b11 << (2 * 2));
    GPIOA_MODER |=  (0b10 << (2 * 2));
    GPIOA_MODER &= ~(0b11 << (3 * 2));
    GPIOA_MODER |=  (0b10 << (3 * 2));

    // Set AF7 (USART2) for PA2 and PA3
    GPIOA_AFRL &= ~(0xF << (4 * 2));
    GPIOA_AFRL |=  (0x7 << (4 * 2));
    GPIOA_AFRL &= ~(0xF << (4 * 3));
    GPIOA_AFRL |=  (0x7 << (4 * 3));

    // Enable USART2 interrupt in NVIC (IRQ38 → ISER1 bit 6)
    NVIC_ISER1 |= (1 << 6);

    // Set baud rate for 9600 @ 16MHz
    USART2_BRR = 0x0683;

    USART2_CR1 |= (1 << 2);  // RE = Receiver enable
    USART2_CR1 |= (1 << 3);  // TE = Transmitter enable
    USART2_CR1 |= (1 << 13); // UE = USART enable
    USART2_CR1 |= (1 << 5);  // RXNEIE = RX interrupt enable
}

// Send a single character
void Uart_tx_bit(char c) {
    while (!(USART2_SR & (1 << 7)));  // Wait for TXE = 1
    USART2_DR = c;
}

// Send a string
void Uart_tx_string(char *str) {
    while (*str)
        Uart_tx_bit(*str++);
}

// Interrupt handler for USART2
void USART2_IRQHandler(void) {
    if (USART2_SR & (1 << 5)) {       // RXNE flag
        char c = USART2_DR;

        if (c == '\r' || c == '\n') {
            Buff[cmd_index] = '\0';   // Null-terminate the command
            ready = 1;
            cmd_index = 0;
        } else {
            if (cmd_index < size - 1) {
                Buff[cmd_index++] = c;
            }
        }
    }
}

int main() {
    setup();
    Uart_tx_string("USART2 Started\n");

    while (1) {
        if (ready) {
            ready = 0;

            if (strcmp((char *)Buff, "HI") == 0) {
                Uart_tx_string("Hello There!\n");
            } else if (strcmp((char *)Buff, "PING") == 0) {
                Uart_tx_string("PONG\n");
            } else {
                Uart_tx_string("INVALID INPUT\n");
            }
        }
    }

    return 0;
}
