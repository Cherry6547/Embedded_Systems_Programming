#include "spi.h"
#include "stm32f446re.h"
#include <stddef.h>

/* SPI status register bit definitions */
#define SPI_SR_BSY  (1 << 7)
#define SPI_SR_RXNE (1 << 0)
#define SPI_SR_TXE  (1 << 1)
#define SPI_SR_OVR  (1 << 6)
#define SPI_SR_MODF (1 << 5)

/* Internal driver variables */
static volatile uint8_t *tx_buff;
static volatile uint8_t *rx_buff;
static volatile uint8_t tx_len;
static volatile uint8_t rx_len;
static volatile uint8_t transfer_done;
static volatile SPI_State_t spi_state = SPI_READY;
static volatile SPI_ERR_State_t spi_err_state = SPI_Err_None;

/* Initialize SPI1 peripheral and GPIO pins */
void spi_init(void){
	RCC->AHB1ENR |= (1 << 0);    // Enable GPIOA clock
	RCC->APB2ENR |= (1 << 12);   // Enable SPI1 clock

	/* Configure PA4 as GPIO output (CS)
	   PA5, PA6, PA7 as alternate function (SPI) */
	GPIOA->MODER &= ~((3 << (2 * 5)) | (3 << (2 * 6)) |
	                  (3 << (2 * 7)) | (3 << (2 * 4)));
	GPIOA->MODER |=  ((2 << (2 * 5)) | (2 << (2 * 6)) |
	                  (2 << (2 * 7)) | (1 << (2 * 4)));

	GPIOA->ODR |= (1 << 4); // Pull CS high (inactive)

	/* Select AF5 for SPI pins */
	GPIOA->AFRL &= ~((0xF << (4 * 5)) | (0xF << (4 * 6)) | (0xF << (4 * 7)));
	GPIOA->AFRL |=  ((5 << (4 * 5)) | (5 << (4 * 6)) | (5 << (4 * 7)));

	/* Enable SPI1 interrupt in NVIC */
	NVIC->ISER[1] |= (1 << 3);

	/* Configure SPI:
	   - Master mode
	   - Software slave management enabled
	   - Internal slave select */
	SPI1->CR1 |= ((1 << 2) | (1 << 8) | (1 << 9));
}

/* Start SPI full-duplex transfer (interrupt-driven) */
uint8_t spi_transfer(uint8_t *tx, uint8_t *rx, uint8_t len){

	if((len == 0) || (tx == NULL) || (rx == NULL)){
		return 0;
	}

	if(spi_state == SPI_BSY){
		return 0;
	}

	transfer_done = 0;
	tx_buff = tx;
	rx_buff = rx;
	tx_len = len;
	rx_len = len;

	SPI1->CR1 |= (1 << 6);       // Enable SPI
	GPIOA->ODR &= ~(1 << 4);     // Pull CS low to start transfer

	/* Load first byte to kick off communication */
	SPI1->DR = *tx_buff;
	tx_buff++;
	tx_len--;

	/* Enable TXE and RXNE interrupts */
	SPI1->CR2 |= ((1 << 6) | (1 << 7));

	spi_state = SPI_BSY;
	spi_err_state = SPI_Err_None;

	return 1;
}

/* Check whether SPI is busy */
uint8_t spi_busy(void){
	return (spi_state == SPI_BSY);
}

/* Check if transfer is completed */
uint8_t spi_transfer_done(void){
	return transfer_done;
}

/* SPI1 interrupt service routine */
void SPI1_IRQHandler(void){

	/* Handle overrun error */
	if(SPI1->SR & SPI_SR_OVR){
		volatile uint8_t dummy;
		dummy = SPI1->DR;
		dummy = SPI1->SR;

		spi_err_state = SPI_Err_OVR;
		SPI1->CR2 &= ~((1 << 6) | (1 << 7)); // Disable SPI interrupts
		SPI1->CR1 &= ~(1 << 6);              // Disable SPI
		GPIOA->ODR |= (1 << 4);               // CS high
		spi_state = SPI_READY;
		transfer_done = 1;
		return;
	}

	/* Handle mode fault error */
	if(SPI1->SR & SPI_SR_MODF){
		volatile uint8_t dummy;
		dummy = SPI1->SR;

		SPI1->CR1 &= ~(1 << 6); // Disable SPI
		SPI1->CR1 |=  (1 << 6); // Re-enable SPI

		spi_err_state = SPI_Err_MODF;
		SPI1->CR2 &= ~((1 << 6) | (1 << 7));
		GPIOA->ODR |= (1 << 4);
		spi_state = SPI_READY;
		transfer_done = 1;
		return;
	}

	/* Receive data */
	if(SPI1->SR & SPI_SR_RXNE){
		*rx_buff = SPI1->DR;
		rx_buff++;
		rx_len--;

		if(rx_len == 0){
			while(SPI1->SR & SPI_SR_BSY);
			SPI1->CR2 &= ~((1 << 6) | (1 << 7));
			GPIOA->ODR |= (1 << 4); // CS high
			spi_state = SPI_READY;
			transfer_done = 1;
		}
	}

	/* Transmit data */
	if((SPI1->SR & SPI_SR_TXE) && (tx_len > 0)){
		SPI1->DR = *tx_buff;
		tx_buff++;
		tx_len--;

		if(tx_len == 0){
			SPI1->CR2 &= ~(1 << 7); // Disable TXE interrupt
		}
	}
}

/* Get last SPI error state */
SPI_ERR_State_t spi_getErr(void){
	return spi_err_state;
}

/* Get current SPI driver state */
SPI_State_t get_SpiState(void){
	return spi_state;
}
