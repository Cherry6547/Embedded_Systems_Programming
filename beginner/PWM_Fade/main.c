#include "stm32f446re.h"

// Crude delay loop
void delay(uint32_t t){
	while(t--);
}

void setup(){
	// Enable GPIOA and TIM2 clocks
	RCC_AHB1ENR |= (1 << 0);     // GPIOA
	RCC_APB1ENR |= (1 << 0);     // TIM2

	// Set PA5 as Alternate Function (AF1 = TIM2_CH1)
	GPIOA_MODER &= ~(0b11 << (2 * 5));     // Clear PA5 mode
	GPIOA_MODER |=  (0b10 << (2 * 5));     // Set PA5 to Alternate Function
	GPIOA_AFRL  &= ~(0xF << (5 * 4));      // Clear AF bits for PA5
	GPIOA_AFRL  |=  (1 << (5 * 4));        // Set AF1 (TIM2_CH1) for PA5

	// TIM2 PWM Setup
	TIM2_PSC = 16000 - 1;      // Prescaler: 16 MHz / 16000 = 1 KHz (1 ms per count)
	TIM2_ARR = 10 - 1;         // Auto-reload = 10 → 10 steps in PWM cycle (10 ms period)

	// Configure PWM Mode 1 on Channel 1
	TIM2_CCMR1 &= ~(7 << 4);   // Clear OC1M bits
	TIM2_CCMR1 |=  (6 << 4);   // Set OC1M to PWM Mode 1
	TIM2_CCMR1 |=  (1 << 3);   // Enable preload register on CCR1

	// Enable channel 1 output
	TIM2_CCER |= (1 << 0);     // Enable CH1 output

	// Enable auto-reload preload
	TIM2_CR1 |= (1 << 7);      // ARPE: Auto-reload preload enable

	// Generate an update event to apply settings
	TIM2_EGR |= (1 << 0);      // UG: Update generation

	// Start the timer
	TIM2_CR1 |= (1 << 0);      // CEN: Counter enable
}

int main(){
	setup();

	while(1){
		// Fade LED in
		for(uint32_t i = 0; i < 10; i++){
			TIM2_CCR1 = i;       // Increase duty cycle
			delay(1000000);
		}
		// Fade LED out
		for(int32_t j = 9; j >= 0; j--){
			TIM2_CCR1 = j;       // Decrease duty cycle
			delay(1000000);
		}
	}

	return 0;
}
