# 🚀 Beginner Bare-Metal Projects – STM32F446RE

This folder contains beginner-level embedded systems projects written in **pure bare-metal C** (no HAL/CubeMX). Each project is aimed at mastering direct register access and understanding fundamental MCU behavior using the STM32F446RE.

---

## 📁 Projects Covered

### 1. **blinky_basic**
- Toggles onboard LED (PA5) with software delay loop.
- Introduces GPIO and clock configuration.

### 2. **pushbutton_toggle**
- Toggles LED when user button (PC13) is pressed.
- Uses GPIO input with simple logic.

### 3. **systick_delay**
- Replaces crude delay with **SysTick timer-based** delay.
- Demonstrates usage of Cortex-M SysTick peripheral.

### 4. **tim2_interrupt**
- LED toggled every 1 second using **TIM2 update interrupt**.
- Teaches basic timer configuration and NVIC handling.

### 5. **pwm_fade**
- LED fades in/out by varying PWM duty cycle on TIM2_CH1 (PA5).
- Explains PWM mode, prescaler, and CCR updates.

### 6. **uart_tx_polling**
- Sends `"Hello World "` over USART2 (PA2) continuously.
- Demonstrates UART TX with polling and baud rate setup.

### 7. **uart_rx_interrupt**
- Receives strings via USART2 RX interrupt.
- Responds to `HI`, `PING`, or other commands with appropriate messages.
- Introduces UART RX, circular buffer, and string comparison.

---

## 🛠️ Tools & Environment

- **Board:** STM32 Nucleo-F446RE
- **IDE:** STM32CubeIDE (used only for startup, linker, and dummy syscall files)
- **Language:** C (no CMSIS/STM32 HAL abstraction)
- **Programming Method:** SWD via onboard ST-Link

---

## 🔍 Philosophy

- **No HAL**, no boilerplate. Just clean register-level C.
- Focused on **one concept per project**.
- All code is **commented** for learning and reference.

---

## 📦 Note

All projects are written assuming:
- You understand basic C
- You're using STM32CubeIDE-generated startup and linker files
- The onboard LED is connected to **PA5**


More advanced and structured projects will be added in the `intermediate/` and `advanced/` folders as I progress.

