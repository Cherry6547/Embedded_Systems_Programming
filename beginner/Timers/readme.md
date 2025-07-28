# ⏲️ LED Toggle Using TIM2 Interrupt – STM32F446RE

This project toggles the onboard LED (PA5) every second using **Timer 2 update interrupt** on the STM32 Nucleo-F446RE.

---

## 🧠 What the Code Does

- Sets PA5 as output.
- Configures TIM2 with:
  - Prescaler = 15 → Timer runs at 1 MHz
  - Auto-reload = 999,999 → Interrupt fires every ~1 second
- Enables TIM2 interrupt in NVIC.
- Toggles the LED inside `TIM2_IRQHandler()` whenever the update event occurs.

---

## ⚙️ Registers Used

- `RCC_APB1ENR`, `RCC_AHB1ENR` – Enable clocks for TIM2 and GPIOA
- `GPIOA_MODER`, `GPIOA_ODR` – Control LED pin
- `TIM2_PSC`, `TIM2_ARR`, `TIM2_DIER`, `TIM2_SR`, `TIM2_CR1` – Configure Timer 2
- `NVIC_ISER0` – Enable TIM2 interrupt

---

## 📦 Notes

- Bare-metal only — no HAL, CubeMX, or CMSIS abstraction.
- Default **startup**, **linker**, and **syscalls** are used from STM32CubeIDE template.
- Timer automatically restarts after every update.

---

## ▶️ How to Run

1. Flash to your STM32 Nucleo-F446RE board.
2. Observe the onboard LED blinking once every second without blocking main loop.
