#include "stm32f446re.h"
#include <stdint.h>

// Peripheral and NVIC setup
void setup() {
    RCC_APB1ENR |= (1 << 0);      // Enable TIM2 clock
    RCC_AHB1ENR |= (1 << 0);      // Enable GPIOA clock

    NVIC_ISER0 |= (1 << 28);      // Enable TIM2 interrupt in NVIC

    GPIOA_MODER &= ~(0b11 << (2 * 5)); // Clear mode for PA5
    GPIOA_MODER |=  (1 << (2 * 5));    // Set PA5 as output

    TIM2_DIER |= (1 << 0);        // Enable Update Interrupt for TIM2
}

// Start timer with ~1 second delay
void sleep() {
    TIM2_PSC = 15;                // Prescaler → 16 MHz / (15+1) = 1 MHz
    TIM2_ARR = 999999;            // Auto-reload → 1 second (1 MHz → 1,000,000 ticks)
    TIM2_CR1 |= (1 << 0);         // Enable counter (CEN bit)
}

// TIM2 interrupt handler
void TIM2_IRQHandler(void) {
    if (TIM2_SR & (1 << 0)) {         // Check for update interrupt flag
        TIM2_SR &= ~(1 << 0);         // Clear the flag
        GPIOA_ODR ^= (1 << 5);        // Toggle LED on PA5
    }
}

int main() {
    setup();
    while (1) {
        sleep();   // Continuously re-enabling the timer
    }
    return 0;
}
