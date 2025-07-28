# 📬 UART RX Interrupt Command Parser – STM32F446RE

This project implements a basic **UART command interface** using **USART2** with **interrupt-driven RX** on STM32F446RE. Type commands like `HI` or `PING` via serial, and the board will respond accordingly.

---

## 🧠 What the Code Does

- Sets PA2 (TX) and PA3 (RX) in alternate function mode (AF7).
- Initializes USART2 at **9600 baud** using a **16 MHz** system clock.
- Enables **RX interrupt** to collect incoming characters into a buffer.
- On newline/enter (`\r` or `\n`), parses the buffer:
  - `"HI"` → responds with `"Hello There!"`
  - `"PING"` → responds with `"PONG"`
  - Else → `"INVALID INPUT"`

---

## ⚙️ Registers Used

- `RCC_AHB1ENR`, `RCC_APB1ENR` – Enable clocks for GPIOA and USART2
- `GPIOA_MODER`, `GPIOA_AFRL` – Set up PA2/PA3 as alternate function AF7
- `USART2_BRR`, `USART2_CR1`, `USART2_SR`, `USART2_DR` – UART config and data handling
- `NVIC_ISER1` – Enable USART2 IRQ (IRQ #38)

---

## 📦 Notes

- Uses **bare-metal code** — no HAL/CubeMX.
- Simple polling-based TX and interrupt-based RX.
- Minimal software buffer (`Buff[size]`) to store incoming strings.
- Uses default STM32CubeIDE startup/linker/syscall files.

---

## ▶️ How to Run

1. Flash code to STM32 Nucleo-F446RE.
2. Connect PA2 (TX) and PA3 (RX) to a UART-USB bridge (e.g., FTDI or onboard ST-Link VCP).
3. Open a serial terminal (9600 baud, 8N1).
4. Type `HI`, `PING`, or other commands followed by Enter.
5. Observe the board's response.

---

## 🔧 Example

| Sent   | Response        |
|--------|-----------------|
| `HI`   | `Hello There!`  |
| `PING` | `PONG`          |
| `ABC`  | `INVALID INPUT` |
