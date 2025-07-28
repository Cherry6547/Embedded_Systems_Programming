# 🌈 PWM LED Fade with TIM2 – STM32F446RE

This project creates a smooth LED fading effect by controlling PWM duty cycle using **TIM2 Channel 1** on pin **PA5**.

---

## 🧠 What the Code Does

- Sets PA5 to alternate function mode (AF1 = TIM2_CH1).
- Configures TIM2 to run at 1 KHz (1 ms resolution) with 10 PWM steps.
- Uses PWM Mode 1 to gradually:
  - Increase duty cycle from 0% to ~90%
  - Then decrease back to 0%
- The LED appears to "breathe" or fade in/out.

---

## ⚙️ Registers Used

- `RCC_AHB1ENR`, `RCC_APB1ENR` – Clock control
- `GPIOA_MODER`, `GPIOA_AFRL` – Set PA5 to AF mode for PWM output
- `TIM2_PSC`, `TIM2_ARR`, `TIM2_CCR1` – Timer base and compare registers
- `TIM2_CCMR1`, `TIM2_CCER`, `TIM2_CR1`, `TIM2_EGR` – PWM configuration

---

## 📦 Notes

- Uses **bare-metal code only**, no HAL or CubeMX.
- Default startup and linker files from STM32CubeIDE template.
- Crude delay loop is used to slow down visible fade — can be replaced with `SysTick`.

---

## ▶️ How to Run

1. Flash to your STM32 Nucleo-F446RE.
2. Connect an LED with resistor to **PA5**, or observe onboard LED if it's wired to PA5.
3. Watch it fade in and out repeatedly.
