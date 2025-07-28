# 🛰️ UART "Hello World" via USART2 – STM32F446RE

This project transmits `"Hello World "` over **USART2** (PA2) repeatedly using **bare-metal UART setup** with polling.

---

## 🧠 What the Code Does

- Configures PA2 as **TX** and PA3 as **RX** in **Alternate Function 7 (AF7)**.
- Initializes USART2 at **9600 baud** (based on 16 MHz system clock).
- Transmits the message `"Hello World "` in a loop using blocking TX.

---

## ⚙️ Registers Used

- `RCC_AHB1ENR` / `RCC_APB1ENR` – Enable clocks for GPIOA and USART2
- `GPIOA_MODER`, `GPIOA_AFRL` – Set PA2/PA3 to alternate function (AF7)
- `USART2_BRR` – Set baud rate
- `USART2_CR1`, `USART2_SR`, `USART2_DR` – UART control and data registers

---

## 📦 Notes

- This is a **bare-metal** implementation without HAL or CubeMX.
- The project uses default **startup**, **linker**, and **syscalls** from STM32CubeIDE.
- Crude delay is used between transmissions; not ideal but enough for demonstration.
- You can observe output via a USB-to-UART bridge or ST-Link Virtual COM Port.

---

## ▶️ How to Run

1. Connect PA2 to a serial monitor (e.g., using ST-Link or FTDI).
2. Flash the code to Nucleo-F446RE.
3. Open a terminal (e.g., PuTTY or TeraTerm) at **9600 baud**.
4. Observe `"Hello World "` printed repeatedly.
