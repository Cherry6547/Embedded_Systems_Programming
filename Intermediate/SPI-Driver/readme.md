# Bare-Metal SPI Driver for STM32F446RE

This repository contains a **bare-metal SPI driver** written from scratch for the STM32F446RE microcontroller, without using HAL or CMSIS drivers.

## Features
- SPI initialization (Master mode)
- Full-duplex communication
- Interrupt-driven transmit and receive
- Overrun (OVR) and Mode Fault (MODF) error handling
- Manual Chip Select (GPIO-based)
- Clean state-based driver design

## Motivation
The goal of this project is to deeply understand:
- How SPI works at the register level
- Why specific control bits (SSM, SSI, CR1, CR2) are required
- How interrupt-driven SPI communication is implemented in real systems

## Files Overview
- `spi.c / spi.h` – SPI driver implementation
- `main.c` – Example usage of the SPI driver
- `stm32f446re.h` – Register definitions

## Key Concepts Covered
- SPI CR1 & CR2 configuration
- TXE, RXNE, BSY flag handling
- Interrupt Service Routine (ISR) design
- Error recovery without resetting the MCU

## Hardware Used
- STM32 Nucleo-F446RE
- On-board GPIO for Chip Select

## Status
✅ Working  
🔧 Improvements planned:
- DMA-based SPI
- Timeout handling
- Multi-device support

## Author
Charan Sai  
(Embedded Systems | Bare-metal | Drivers)
