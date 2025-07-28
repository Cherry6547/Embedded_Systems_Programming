#include "stm32f446re.h"

// Setup GPIOA (LED) and GPIOC (Button)
void setup(){
	// Enable clock for GPIOA and GPIOC
	// Bit 0: GPIOA, Bit 2: GPIOC → 0b0101 = 0x5
	RCC_AHB1ENR |= (5 << 0);  // Enable GPIOA and GPIOC

	// Set PA5 as output (01)
	GPIOA_MODER &= ~(3 << (2 * 5));      // Clear bits first
	GPIOA_MODER |=  (1 << (2 * 5));      // Set as output (0b01)

	// Set PC13 as input (00)
	GPIOC_MODER &= ~(0b11 << (2 * 13));  // Set as input
}

int main(){
	setup();

	while(1){
		// Check if button on PC13 is pressed (active low)
		if(!(GPIOC_IDR & (1 << 13))){
			GPIOA_ODR ^= (1 << 5);  // Toggle LED on PA5
			// Optional: Add debounce delay here
		}
	}

	return 0;
}
