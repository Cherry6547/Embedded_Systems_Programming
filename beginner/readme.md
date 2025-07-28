# 🟢 Beginner Projects – Bare-Metal Embedded Systems (STM32F446RE)

This folder contains the **first phase** of my embedded systems journey using the STM32 Nucleo-F446RE board. All projects are written using **pure bare-metal programming** — no HAL, no CubeMX — just raw register-level control in C.

These projects are focused on building a **strong foundation** by directly controlling the microcontroller's GPIO, timers, interrupts, and UART peripherals.

---

## ✅ Completed Beginner Projects

| Project Name        | Description |
|---------------------|-------------|
| `gpio_toggle/`      | Toggle an LED using GPIO output and control it using a push-button input (polling method). |
| `button_interrupt/` | Handle external interrupts from a push-button to toggle an LED without polling. |
| `systick_delay/`    | Use the SysTick timer to implement precise millisecond delays without blocking the CPU. |
| `uart_tx_rx/`       | Transmit and receive data via UART using polling and interrupt-based approaches. |
| `pwm_generation/`   | Generate a PWM signal using TIM2 by configuring it manually through registers. |

---

## 🧰 Tools Used

- **Board**: STM32 Nucleo-F446RE
- **Language**: C
- **Programming Style**: Bare-metal (register-level)
- **IDE**: STM32CubeIDE
- **Flashing**: ST-Link (built-in)
- **Serial Terminal**: PuTTY / TeraTerm

---

## 📌 Goals of the Beginner Phase

- Learn how to configure GPIOs manually.
- Understand how timers like SysTick and TIM2 work.
- Use NVIC and EXTI to handle interrupts.
- Communicate with a PC using UART (both TX and RX).
- Generate PWM signals directly through timer registers.

---

More advanced and structured projects will be added in the `intermediate/` and `advanced/` folders as I progress.

