#include "uart.h"
#include "ch32v003.h"

//========macros=============//
#define USART1_BASE 0x40013800
#define USART1_SR (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CTRL1 (*(volatile uint32_t *)(USART1_BASE + 0x0C))

#define USART_CTRL1_UE
