#ifndef STM32F446RE_H
#define STM32F446RE_H

#include <stdint.h>  // For fixed-width types like uint32_t

// ------------------------------
// Base Addresses of Peripherals
// ------------------------------
#define RCC_Base        0x40023800  // Reset and Clock Control
#define GPIOA_Base      0x40020000  // GPIO Port A
#define GPIOC_Base      0x40020800  // GPIO Port C
#define TIM2_Base       0x40000000  // Timer 2
#define USART2_Base     0x40004400  // USART2
#define NVIC_ISERBase   0xE000E000  // Nested Vectored Interrupt Controller (ISER region)

// ------------------------------
// Timer 2 Registers
// ------------------------------
#define TIM2_CR1    (*(volatile uint32_t *)(TIM2_Base + 0x00)) // Control Register 1
#define TIM2_DIER   (*(volatile uint32_t *)(TIM2_Base + 0x0C)) // DMA/Interrupt Enable Register
#define TIM2_SR     (*(volatile uint32_t *)(TIM2_Base + 0x10)) // Status Register
#define TIM2_EGR    (*(volatile uint32_t *)(TIM2_Base + 0x14)) // Event Generation Register
#define TIM2_CCMR1  (*(volatile uint32_t *)(TIM2_Base + 0x18)) // Capture/Compare Mode Register 1
#define TIM2_CCER   (*(volatile uint32_t *)(TIM2_Base + 0x20)) // Capture/Compare Enable Register
#define TIM2_CNT    (*(volatile uint32_t *)(TIM2_Base + 0x24)) // Counter
#define TIM2_PSC    (*(volatile uint32_t *)(TIM2_Base + 0x28)) // Prescaler
#define TIM2_ARR    (*(volatile uint32_t *)(TIM2_Base + 0x2C)) // Auto-Reload Register
#define TIM2_CCR1   (*(volatile uint32_t *)(TIM2_Base + 0x34)) // Capture/Compare Register 1

// ------------------------------
// SysTick Registers (Cortex-M4 Core)
// ------------------------------
#define STK_CTRL   (*(volatile uint32_t *)0xE000E010) // SysTick Control and Status
#define STK_LOAD   (*(volatile uint32_t *)0xE000E014) // Reload value
#define STK_VAL    (*(volatile uint32_t *)0xE000E018) // Current value
#define STK_CALIB  (*(volatile uint32_t *)0xE000E01C) // Calibration value

// ------------------------------
// RCC (Reset and Clock Control)
// ------------------------------
#define RCC_CR         (*(volatile uint32_t *)(RCC_Base + 0x00)) // Clock Control Register
#define RCC_AHB1ENR    (*(volatile uint32_t *)(RCC_Base + 0x30)) // AHB1 Peripheral Clock Enable
#define RCC_APB1ENR    (*(volatile uint32_t *)(RCC_Base + 0x40)) // APB1 Peripheral Clock Enable

// ------------------------------
// GPIOA Registers
// ------------------------------
#define GPIOA_MODER    (*(volatile uint32_t *)(GPIOA_Base + 0x00)) // Mode Register
#define GPIOA_IDR      (*(volatile uint32_t *)(GPIOA_Base + 0x10)) // Input Data Register
#define GPIOA_ODR      (*(volatile uint32_t *)(GPIOA_Base + 0x14)) // Output Data Register
#define GPIOA_AFRL     (*(volatile uint32_t *)(GPIOA_Base + 0x20)) // Alternate Function Low Register

// ------------------------------
// GPIOC Registers
// ------------------------------
#define GPIOC_MODER    (*(volatile uint32_t *)(GPIOC_Base + 0x00)) // Mode Register
#define GPIOC_IDR      (*(volatile uint32_t *)(GPIOC_Base + 0x10)) // Input Data Register
#define GPIOC_ODR      (*(volatile uint32_t *)(GPIOC_Base + 0x14)) // Output Data Register
#define GPIOC_AFRL     (*(volatile uint32_t *)(GPIOC_Base + 0x20)) // Alternate Function Low Register

// ------------------------------
// USART2 Registers
// ------------------------------
#define USART2_SR      (*(volatile uint32_t *)(USART2_Base + 0x00)) // Status Register
#define USART2_DR      (*(volatile uint32_t *)(USART2_Base + 0x04)) // Data Register
#define USART2_BRR     (*(volatile uint32_t *)(USART2_Base + 0x08)) // Baud Rate Register
#define USART2_CR1     (*(volatile uint32_t *)(USART2_Base + 0x0C)) // Control Register 1
#define USART2_CR2     (*(volatile uint32_t *)(USART2_Base + 0x10)) // Control Register 2
#define USART2_CR3     (*(volatile uint32_t *)(USART2_Base + 0x14)) // Control Register 3
#define USART2_GTPR    (*(volatile uint32_t *)(USART2_Base + 0x18)) // Guard time and prescaler

// ------------------------------
// NVIC (Nested Vectored Interrupt Controller)
// ------------------------------
#define NVIC_ISER0     (*(volatile uint32_t *)0xE000E100) // Interrupt Set-Enable Register 0
#define NVIC_ISER1     (*(volatile uint32_t *)(NVIC_ISERBase + 0x104)) // Interrupt Set-Enable Register 1

#endif // STM32F446RE_H
