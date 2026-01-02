#ifndef STM32F446RE_H
#define STM32F446RE_H

#include <stdint.h>

//
// ========================= BASE ADDRESSES =========================
//
#define PERIPH_BASE           0x40000000UL
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)

#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800UL)
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2000UL)
#define SPI1_BASE			  (0x40013000)
#define SPI2_BASE			  (0x40003800)
#define USART1_BASE  0x40011000UL
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
#define USART3_BASE  0x40004800UL
#define UART4_BASE   0x40004C00UL
#define UART5_BASE	 0x40005000UL
#define USART6_BASE  0x40011400UL

//
// ========================= RCC =========================
//
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *) RCC_BASE)

//
// ========================= SPI =========================
//
typedef struct
{
    volatile uint32_t CR1;     /* Control register 1      */
    volatile uint32_t CR2;     /* Control register 2      */
    volatile uint32_t SR;      /* Status register         */
    volatile uint32_t DR;      /* Data register           */
    volatile uint32_t CRCPR;   /* CRC polynomial register */
    volatile uint32_t RXCRCR;  /* RX CRC register         */
    volatile uint32_t TXCRCR;  /* TX CRC register         */
    volatile uint32_t I2SCFGR; /* I2S configuration reg   */
    volatile uint32_t I2SPR;   /* I2S prescaler register  */
} SPI_RegDef_t;

/* SPI peripheral base addresses */
#define SPI1_BASEADDR     (APB2PERIPH_BASE + 0x3000UL)
#define SPI2_BASEADDR     (PERIPH_BASE + 0x3800UL)
#define SPI3_BASEADDR     (PERIPH_BASE + 0x3C00UL)

/* SPI peripheral definitions */
#define SPI1   ((volatile SPI_RegDef_t *) SPI1_BASEADDR)
#define SPI2   ((volatile SPI_RegDef_t *) SPI2_BASEADDR)
#define SPI3   ((volatile SPI_RegDef_t *) SPI3_BASEADDR)

//
// ========================= GPIO =========================
//
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)


typedef struct {
    volatile uint32_t ISER[8];   // Interrupt Set Enable registers
    volatile uint32_t ICER[8];   // Interrupt Clear Enable registers
    volatile uint32_t ISPR[8];   // Interrupt Set Pending
    volatile uint32_t ICPR[8];   // Interrupt Clear Pending
    volatile uint32_t IPR[60];   // Interrupt Priority
} NVIC_TypeDef;

#define NVIC ((NVIC_TypeDef *)0xE000E100)
//
// ========================= TIM2 =========================
//
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t BDTR;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
} TIM_TypeDef;

#define TIM2 ((TIM_TypeDef *) TIM2_BASE)

//
// ========================= ADC1 =========================
//
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    volatile uint32_t JOFR1;
    volatile uint32_t JOFR2;
    volatile uint32_t JOFR3;
    volatile uint32_t JOFR4;
    volatile uint32_t HTR;
    volatile uint32_t LTR;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t JSQR;
    volatile uint32_t JDR1;
    volatile uint32_t JDR2;
    volatile uint32_t JDR3;
    volatile uint32_t JDR4;
    volatile uint32_t DR;
} ADC_TypeDef;

#define ADC1 ((ADC_TypeDef *) ADC1_BASE)

//
// ========================= USART2 =========================
//
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

#define USART1 ((USART_TypeDef *) USART1_BASE)
#define USART2 ((USART_TypeDef *) USART2_BASE)
#define USART3 ((USART_TypeDef *) USART3_BASE)
#define UART4  ((USART_TypeDef *) UART4_BASE)
#define UART5  ((USART_TypeDef *) UART5_BASE)
#define USART6 ((USART_TypeDef *) USART6_BASE)

#endif /* STM32F446RE_H */
