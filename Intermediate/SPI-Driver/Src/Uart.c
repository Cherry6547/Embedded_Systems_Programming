#include "Uart.h"
#include "stm32f446re.h"
#include<stddef.h>


volatile static RB tx_rb;
volatile static RB rx_rb;
volatile static uint8_t tx_buff[256];
volatile static uint8_t rx_buff[256];


bool uart2_init(uint32_t baudrate, uint32_t sysclk){
	if((baudrate <= 0) || (sysclk <= 0)){
		return false;
	}
	RCC->AHB1ENR |= (1 << 0);
	RCC->APB1ENR |= (1 << 17);
	GPIOA->MODER &= ~((3 << (2 * 2)) | (3 << (2 * 3)));
	GPIOA->MODER |= (2 << (2 * 2)) | (2 << (2 * 3));
	GPIOA->AFRL &= ~((0xF << (4 * 2)) | (0xF << (4 * 3)));
	GPIOA->AFRL  |= (7 << (4 * 2)) | (7 << (4 * 3));
	NVIC->ISER[1] |= (1 << 6);
	USART2->BRR = (uint32_t)sysclk / baudrate ;
	USART2->CR1 &= ~((1 << 2) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 13));
	USART2->CR1 |= (1 << 2) | (1 << 3) | (1 << 5) | (1 << 13);

	RB_init(&tx_rb, tx_buff, 256U);
	RB_init(&rx_rb, rx_buff, 256U);
	return true;
}
bool uart2_write(uint8_t *buff, uint16_t len){
	if((buff == NULL) || (len == 0U)){
		return false;
	}
	for(uint16_t i = 0;i < len;i++){
		RB_write(&tx_rb, buff[i]);
	}
	USART2->CR1 |= (1 << 7);
	return true;
}

bool uart2_read(uint8_t *byte){
	if(RB_isempty(&rx_rb)){
		return false;
	}
	RB_read(&rx_rb, byte);
	return true;
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & (1 << 7)){
		uart2_tx_isr_handler();
	}
	if(USART2->SR & (1 << 5)){
		uart2_rx_isr_handler();
	}
}


void uart2_tx_isr_handler(){
	uint8_t byte;
	if(RB_read(&tx_rb, &byte)){
		USART2->DR = byte;
	}else{
		USART2->CR1 &= ~(1 << 7);
	}
}

void uart2_rx_isr_handler(){
	uint8_t data;
	data = USART2->DR;
	RB_write(&rx_rb, data); //reading the dr register will clear the rxne interrupt bit in the SR ;
}


void log_uart(const char *str)
{
    if (str == 0)
    {
        return;
    }

    while (*str != '\0')
    {
        uart2_write((uint8_t *)str, 1);
        str++;
    }
}
