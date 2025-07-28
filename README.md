# 🚀 Embedded Systems Journey – STM32 Nucleo (Bare-Metal Only)

Welcome to my embedded systems repository! This is a hands-on journey using the **STM32 Nucleo-F446RE** board, focused entirely on **bare-metal programming** — no STM32 HAL, no CubeMX, no libraries — just pure register-level control.

---

## 🧠 What This Repository Is About

This is a personal documentation of my journey to master embedded systems using STM32. The goal is to build deep understanding by writing every line from scratch and controlling the hardware directly.

Key principles:
- **Bare-metal only** (direct register manipulation)
- **No HAL/CubeMX**
- **No external libraries**
- Focused on **real learning** and **real hardware testing**

---

## 🗺️ Learning Roadmap

### ✅ Beginner Phase – [Completed]
- ✅ GPIO Input/Output (LED blinking, push-button toggle)
- ✅ SysTick-based delay
- ✅ TIM2 with interrupt (trigger ISR after delay)
- ✅ UART transmission and reception using polling and interrupts
- ✅ PWM generation using TIM2

### 🛠️ Intermediate Phase – [In Progress]
- DMA (register-based)
- EXTI (external interrupts)
- NVIC priority grouping and nesting
- UART ring buffer implementation
- Timer-based task scheduling
- Software debouncing and button state machines

### 🔝 Advanced Phase – [Planned]
- SPI and I2C using bare-metal
- Sensor interfacing without libraries
- Writing custom drivers (UART, GPIO, PWM)
- Bare-metal task scheduler
- Memory-mapped peripherals
- Bootloader development
- Low-power and sleep modes
- Intro to RTOS (from a bare-metal foundation)

---

## 📁 Repository Structure

```markdown
<pre>
├── beginner/
│ ├── gpio_toggle/
│ ├── button_interrupt/
│ ├── uart_tx_rx/
│ └── pwm_generation/
├── intermediate/
│ └── coming_soon/
├── advanced/
│ └── coming_soon/
└── README.md

</pre>
```
Each folder includes:
- Fully commented C source code
- Register macros (`stm32f446re.h`)
- A README with explanation of logic and key registers used

---

## 🔧 Tools & Hardware

- **Board**: STM32 Nucleo-F446RE
- **Processor**: ARM Cortex-M4
- **IDE**: STM32CubeIDE (for building & flashing)
- **Language**: C (no HAL, no libraries)
- **Terminal**: PuTTY/TeraTerm for UART testing

---

## 💡 Why Bare-Metal?

> “Understanding comes from control.”

This journey is about full control of hardware — without HAL or library abstractions. By manually setting registers, I’m learning exactly how peripherals work at the lowest level.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
