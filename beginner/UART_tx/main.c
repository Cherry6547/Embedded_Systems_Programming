#include "stm32f446re.h"
//#define SysClk 84000000
//#define USART_Baudrate 9600
//#define USART_Div (SysClk / (16 * USART_Baudrate))

void setup(){
    // Enable GPIOA and USART2 peripheral clocks
    RCC_AHB1ENR |= (1 << 0);    // GPIOA clock enable
    RCC_APB1ENR |= (1 << 17);   // USART2 clock enable

    // Configure PA2 (TX) and PA3 (RX) as Alternate Function
    GPIOA_MODER &= ~(0b11 << (2 * 2));  // Clear mode bits for PA2
    GPIOA_MODER |=  (0b10 << (2 * 2));  // Set PA2 to AF mode
    GPIOA_MODER &= ~(0b11 << (2 * 3));  // Clear mode bits for PA3
    GPIOA_MODER |=  (0b10 << (2 * 3));  // Set PA3 to AF mode

    // Set AF7 (USART2) for PA2 and PA3
    GPIOA_AFRL &= ~(0xF << (4 * 2));    // Clear AFRL for PA2
    GPIOA_AFRL |=  (0x7 << (4 * 2));    // Set AF7
    GPIOA_AFRL &= ~(0xF << (4 * 3));    // Clear AFRL for PA3
    GPIOA_AFRL |=  (0x7 << (4 * 3));    // Set AF7

    USART2_BRR = 0x0683;         // Baud rate = 9600 @ 16 MHz clock


    USART2_CR1 |= (1 << 2);      // RE = Receiver Enable
    USART2_CR1 |= (1 << 3);      // TE = Transmitter Enable
    USART2_CR1 |= (1 << 13);     // UE = USART Enable
}

// Transmit a single character
void Uart_tx_bit(char c){
    while (!(USART2_SR & (1 << 7)));  // Wait for TXE (Transmit data register empty)
    USART2_DR = c;                    // Load data
}

// Transmit a null-terminated string
void Uart_tx_string(char *str){
    while (*str)
        Uart_tx_bit(*str++);
}

int main(){
    setup();
    while (1) {
        Uart_tx_string("Hello World ");
        for (uint32_t i = 0; i < 1000000; i++);  // Crude delay
    }
    return 0;
}
