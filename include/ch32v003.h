#ifndef CH32V003_H_
#define CH32V003_H_

#include <stdint.h>

/* ============================================================
   Base addresses of peripheral blocks
   ============================================================ */
#define RCC_BASE 0x40021000U
#define GPIOD_BASE 0x40011400U
#define GPIOA_BASE 0x40010800U
#define GPIOC_BASE 0x40011000U

/* ============================================================
   RCC registers (Reset and Clock Control)
   ============================================================ */
#define RCC_CTLR (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR0 (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_INTR (*(volatile uint32_t *)(RCC_BASE + 0x08))
#define RCC_APB2PRSTR (*(volatile uint32_t *)(RCC_BASE + 0x0C))
#define RCC_APB1PRSTR (*(volatile uint32_t *)(RCC_BASE + 0x10))
#define RCC_AHBPCENR (*(volatile uint32_t *)(RCC_BASE + 0x14))
#define RCC_APB2PCENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1PCENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))
#define RCC_RSTSCKR (*(volatile uint32_t *)(RCC_BASE + 0x24))

#endif // !CH32V003_H_
