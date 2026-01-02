#include "stm32f446re.h"
#include "spi.h"
#include "Uart.h"   // UART driver with ring buffer (used for logging)
#include <string.h>

int main(void)
{
    /* Transmit and receive buffers */
    uint8_t tx[] = "SPI test\r\n";
    uint8_t rx[sizeof(tx)] = {0};

    /* Initialize peripherals */
    spi_init();                 // Initialize SPI driver
    uart2_init(9600, 16000000);  // Initialize UART for debugging/logging

    /* Start SPI full-duplex transfer */
    spi_transfer(tx, rx, sizeof(tx) - 1);

    /* Wait until SPI transfer completes */
    while (!spi_transfer_done());

    /* Check transfer status and report via UART */
    if (spi_getErr() == SPI_Err_None) {
        log_uart("SPI OK: ");
        log_uart((char *)rx);
    } else {
        log_uart("SPI ERROR\r\n");
    }

    /* Idle loop */
    while (1);
}
