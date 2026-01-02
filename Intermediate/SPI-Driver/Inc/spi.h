#ifndef SPI_H
#define SPI_H

#include <stdint.h>

/* SPI driver state */
typedef enum {
    SPI_READY,   // SPI is idle and ready for a new transfer
    SPI_BSY      // SPI is currently busy with an ongoing transfer
} SPI_State_t;

/* SPI error states */
typedef enum {
    SPI_Err_None = 0, // No error
    SPI_Err_OVR,      // Overrun error
    SPI_Err_MODF      // Mode fault error
} SPI_ERR_State_t;

/* Initialize SPI peripheral and related GPIOs */
void spi_init(void);

/* Start SPI full-duplex transfer (interrupt-driven)
 * tx  : pointer to transmit buffer
 * rx  : pointer to receive buffer
 * len : number of bytes to transfer
 */
uint8_t spi_transfer(uint8_t *tx, uint8_t *rx, uint8_t len);

/* Returns 1 if SPI is busy, 0 if ready */
uint8_t spi_busy(void);

/* Returns 1 when the current transfer is completed */
uint8_t spi_transfer_done(void);

/* Get the last SPI error status */
SPI_ERR_State_t spi_getErr(void);

/* Get current SPI state (READY or BUSY) */
SPI_State_t get_SpiState(void);

#endif /* SPI_H */
