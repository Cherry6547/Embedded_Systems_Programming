#include "stm32f446re.h"  // Custom header with register definitions for STM32F446RE

// Simple blocking delay using a for loop
void delay(){
	for(volatile int i = 0; i < 10000000; i++);  // Delay loop (roughly adjustable by tuning the loop count)
}

int main(){
	// 1. Enable clock for GPIOA peripheral (bit 0 in RCC_AHB1ENR)
	RCC_AHB1ENR |= (1 << 0);  // Set bit 0 → Enable GPIOA

	// 2. Set PA5 as General Purpose Output
	GPIOA_MODER &= ~(3 << (2 * 5));     // Clear mode bits for PA5 (bits 10 and 11)
	GPIOA_MODER |=  (0b01 << (2 * 5));  // Set mode to '01' → General purpose output

	// 3. Toggle PA5 (usually connected to the onboard LED) with delay
	while(1){
		GPIOA_ODR ^= (1 << 5);  // Toggle output state of pin PA5
		delay();                // Wait before next toggle
	}
}
