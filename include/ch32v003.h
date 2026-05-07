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

/* RCC_CTLR bits */
#define RCC_HSION (1U << 0)
#define RCC_HSIRDY (1U << 1)
#define RCC_HSEON (1U << 16)
#define RCC_HSERDY (1U << 17)
#define RCC_HSEBYP (1U << 18)
#define RCC_CSSON (1U << 19)
#define RCC_PLLON (1U << 24)
#define RCC_PLLRDY (1U << 25)

/* RCC_APB2PCENR bits */
#define RCC_APB2PCENR_AFIOEN (1U << 0)
#define RCC_APB2PCENR_IOPAEN (1U << 2)
#define RCC_APB2PCENR_IOPCEN (1U << 4)
#define RCC_APB2PCENR_IOPDEN (1U << 5)
#define RCC_APB2PCENR_ADC1EN (1U << 9)
#define RCC_APB2PCENR_TIM1EN (1U << 11)
#define RCC_APB2PCENR_SPI1EN (1U << 12)
#define RCC_APB2PCENR_USART1EN (1U << 14)

/* ============================================================
   GPIO registers
   ============================================================ */
#define GPIOx_CFGLR(base) (*(volatile uint32_t *)((base) + 0x00))
#define GPIOx_INDR(base) (*(volatile uint32_t *)((base) + 0x08))
#define GPIOx_OUTDR(base) (*(volatile uint32_t *)((base) + 0x0C))
#define GPIOx_BSHR(base) (*(volatile uint32_t *)((base) + 0x10))
#define GPIOx_BCR(base) (*(volatile uint32_t *)((base) + 0x14))

/* Convenience macros for specific ports */
#define GPIOD_CFGLR GPIOx_CFGLR(GPIOD_BASE)
#define GPIOD_BSHR GPIOx_BSHR(GPIOD_BASE)
#define GPIOD_BCR GPIOx_BCR(GPIOD_BASE)

/* GPIO pin bit positions in BSHR/BCR (for set/reset) */
#define GPIO_BS(n) (1U << (n))
#define GPIO_BR(n) (1U << (n))

/* ============================================================
   Helper macro for pin configuration in CFGLR
   ============================================================ *
/* MODE: 00=input, 01=10MHz output, 10=2MHz output, 11=50MHz output */
/* CNF:  in input mode: 00=analog, 01=floating, 10=pull-up/down
         in output mode: 00=push-pull, 01=open-drain,
                         10=alt.func push-pull, 11=alt.func open-drain */

#define GPIO_CFG_OUTPUT_PP_10MHZ 0x1U
#define GPIO_CFG_OUTPUT_PP_2MHZ 0x2U
#define GPIO_CFG_OUTPUT_PP_50MHZ 0x3U

#define GPIO_CFG_SET(port_base, pin, config)                                   \
  do {                                                                         \
    uint32_t tmp = GPIOx_CFGLR(port_base);                                     \
    tmp &= ~(0xFU << ((pin) * 4));                                             \
    tmp |= ((config) & 0xFU) << ((pin) * 4);                                   \
    GPIOx_CFGLR(port_base) = tmp;                                              \
  } while (0)

/* ============================================================
   Utility macros for RCC peripheral enable/disable
   ============================================================ */
#define RCC_ENABLE_PERIPH(reg, bit) ((reg) |= (bit))
#define RCC_DISABLE_PERIPH(reg, bit) ((reg) &= ~(bit))

#endif /* CH32V003_H_ */

#endif // !CH32V003_H_
