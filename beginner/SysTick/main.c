#include "stm32f446re.h"
#include <stdint.h>

// Delay function using SysTick timer
void delay(uint32_t t) {
    STK_CTRL = 0;                         // Disable SysTick during setup
    STK_LOAD = (16000 * t) - 1;          // Load value for 't' milliseconds (16 MHz clock)
    STK_VAL = 0;                         // Reset current value
    STK_CTRL = 5;                         // Enable SysTick with processor clock, no interrupt
    while ((STK_CTRL & (1 << 16)) == 0); // Wait until COUNTFLAG is set
}

int main(){
    // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 0);

    // Set PA5 as output
    GPIOA_MODER &= ~(0b11 << (2 * 5));  // Clear mode bits
    GPIOA_MODER |=  (1 << (2 * 5));     // Set as output

    while(1){
        GPIOA_ODR ^= (1 << 5);          // Toggle LED
        delay(1000);                    // Delay 1000 ms (1 second)
    }
}
