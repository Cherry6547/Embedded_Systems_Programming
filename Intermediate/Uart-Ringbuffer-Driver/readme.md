# STM32 UART Driver (Interrupt Driven)

## Overview
This project implements an interrupt-driven UART driver for STM32 (bare-metal),
using ring buffers for both TX and RX. The driver supports non-blocking transmission
and reception and integrates with `printf` via stdio retargeting.

## Features
- UART2 initialization (GPIO, clock, baudrate)
- Interrupt-driven TX using ring buffer
- Interrupt-driven RX using ring buffer
- Non-blocking APIs
- `printf` support via `_write()` retargeting
- Clean driver abstraction (no register access in application)

## Design Highlights
- Ring buffer used to decouple ISR and application
- TXE interrupt enabled only when data is available
- RXNE interrupt used to capture incoming bytes
- Module-private driver state
- Bare-metal friendly (no HAL, no RTOS)

## How to Test
- Flash the code
- Open serial terminal (115200 baud)
- Type characters → echoed back
- Use `printf()` for debug output

## Target
- STM32F446RE (Nucleo)

## Tools
- GCC ARM toolchain
- GDB
- ST-Link (JTAG/SWD)
