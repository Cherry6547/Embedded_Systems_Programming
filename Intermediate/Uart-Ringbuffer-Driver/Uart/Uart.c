#include "Uart.h"
#include "stm32f446re.h"
#include <stddef.h>

/*
 * Module-private ring buffers for UART2
 *
 * TX buffer:
 *  - Application writes data
 *  - ISR reads data and transmits
 *
 * RX buffer:
 *  - ISR writes received data
 *  - Application reads data
 */
static RB tx_rb;
static RB rx_rb;

/* Static buffer storage (no dynamic allocation) */
static uint8_t tx_buff[256];
static uint8_t rx_buff[256];

/*
 * uart2_init
 *
 * Initializes UART2 peripheral along with GPIO configuration,
 * interrupt enable, and ring buffer initialization.
 */
bool uart2_init(uint32_t baudrate, uint32_t sysclk)
{
    /* Basic parameter validation */
    if ((baudrate == 0U) || (sysclk == 0U))
    {
        return false;
    }

    /* Enable GPIOA and USART2 clocks */
    RCC->AHB1ENR |= (1U << 0);     /* GPIOA clock */
    RCC->APB1ENR |= (1U << 17);    /* USART2 clock */

    /* Configure PA2 (TX) and PA3 (RX) as alternate function */
    GPIOA->MODER &= ~((3U << (2U * 2U)) | (3U << (2U * 3U)));
    GPIOA->MODER |=  ((2U << (2U * 2U)) | (2U << (2U * 3U)));

    /* Select AF7 (USART2) for PA2 and PA3 */
    GPIOA->AFRL &= ~((0xFU << (4U * 2U)) | (0xFU << (4U * 3U)));
    GPIOA->AFRL |=  ((7U   << (4U * 2U)) | (7U   << (4U * 3U)));

    /* Enable USART2 interrupt in NVIC */
    NVIC->ISER[1] |= (1U << 6);    /* USART2 IRQ */

    /* Configure baud rate */
    USART2->BRR = sysclk / baudrate;

    /*
     * Configure USART2:
     * - Enable transmitter (TE)
     * - Enable receiver (RE)
     * - Enable RXNE interrupt
     * - Enable USART (UE)
     */
    USART2->CR1 &= ~((1U << 2) | (1U << 3) | (1U << 5) | (1U << 7) | (1U << 13));
    USART2->CR1 |=  ((1U << 2) | (1U << 3) | (1U << 5) | (1U << 13));

    /* Initialize TX and RX ring buffers */
    RB_init(&tx_rb, tx_buff, 256U);
    RB_init(&rx_rb, rx_buff, 256U);

    return true;
}

/*
 * uart2_write
 *
 * Writes data to UART2 transmit buffer.
 * Transmission is interrupt-driven and non-blocking.
 */
bool uart2_write(uint8_t *buff, uint16_t len)
{
    if ((buff == NULL) || (len == 0U))
    {
        return false;
    }

    /* Push data into TX ring buffer */
    for (uint16_t i = 0U; i < len; i++)
    {
        RB_write(&tx_rb, buff[i]);
    }

    /* Enable TXE interrupt to start transmission */
    USART2->CR1 |= (1U << 7);

    return true;
}

/*
 * uart2_read
 *
 * Reads one byte from UART2 receive buffer.
 * Non-blocking API.
 */
bool uart2_read(uint8_t *byte)
{
    if (byte == NULL)
    {
        return false;
    }

    if (RB_isempty(&rx_rb))
    {
        return false;
    }

    RB_read(&rx_rb, byte);
    return true;
}

/*
 * USART2_IRQHandler
 *
 * Central interrupt handler for USART2.
 * Dispatches TX and RX events to dedicated handlers.
 */
void USART2_IRQHandler(void)
{
    /* TXE interrupt: transmit next byte */
    if (USART2->SR & (1U << 7))
    {
        uart2_tx_isr_handler();
    }

    /* RXNE interrupt: receive new byte */
    if (USART2->SR & (1U << 5))
    {
        uart2_rx_isr_handler();
    }
}

/*
 * uart2_tx_isr_handler
 *
 * Handles transmit interrupt.
 * Sends next byte from TX ring buffer or disables TXE interrupt
 * when no more data is available.
 */
void uart2_tx_isr_handler(void)
{
    uint8_t byte;

    if (RB_read(&tx_rb, &byte))
    {
        USART2->DR = byte;
    }
    else
    {
        /* No more data to send, disable TXE interrupt */
        USART2->CR1 &= ~(1U << 7);
    }
}

/*
 * uart2_rx_isr_handler
 *
 * Handles receive interrupt.
 * Reads received byte from data register and stores it
 * in RX ring buffer.
 */
void uart2_rx_isr_handler(void)
{
    uint8_t data;

    /* Reading DR clears RXNE flag */
    data = USART2->DR;
    RB_write(&rx_rb, data);
}
