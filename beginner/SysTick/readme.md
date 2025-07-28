# ⏱️ SysTick-Based Delay Blinky – STM32F446RE

This project toggles the onboard LED (PA5) with a precise 1-second delay using the **Cortex-M4 SysTick timer**.

---

## 🧠 What the Code Does

- Sets PA5 as a GPIO output.
- Uses the **SysTick timer** to implement a millisecond delay.
- Toggles the LED with a 1000 ms (1 second) interval.

---

## 🧰 Registers Used

- `RCC_AHB1ENR` – Enables GPIOA clock
- `GPIOA_MODER` – Configures PA5 as output
- `GPIOA_ODR` – Toggles the LED
- `STK_CTRL`, `STK_LOAD`, `STK_VAL` – Used to configure and control the SysTick timer

---

## 📦 Notes

- SysTick runs at **16 MHz** core clock → 16000 ticks = 1 ms
- The project uses **bare-metal code only**
- **Startup files**, **linker script**, and **syscalls** are from STM32CubeIDE template

---

## ▶️ How to Run

1. Flash the code to your Nucleo-F446RE.
2. Observe the onboard LED (PA5) blinking every second.
