# 🔘 Button-Controlled LED Toggle – STM32F446RE

This program toggles the onboard LED (PA5) when the user presses the onboard push-button (PC13) on the STM32 Nucleo-F446RE board.

---

## 🧠 What the Code Does

- Enables clocks for GPIOA (LED) and GPIOC (button).
- Sets:
  - **PA5** as output (for LED)
  - **PC13** as input (for button)
- Continuously checks if the button is pressed (logic LOW) using polling.
- Toggles the LED on each press (no delay/debounce for now).

---

## ⚙️ Registers Used

- `RCC_AHB1ENR` – Enable GPIO clocks
- `GPIOA_MODER` – Set PA5 as output
- `GPIOC_MODER` – Set PC13 as input
- `GPIOC_IDR` – Read button input
- `GPIOA_ODR` – Toggle LED output

---

## 📦 Project Notes

- Written using **bare-metal programming** (no HAL/CubeMX).
- **Default startup files**, **linker script**, and **syscall stubs** from STM32CubeIDE are used.
- No debounce logic yet — fast repeated toggles may happen with one press.

---

## ▶️ How to Run

1. Flash to Nucleo-F446RE using STM32CubeIDE.
2. Press the blue user button (PC13).
3. Watch the green LED (PA5) toggle with each press.
