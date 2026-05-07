#include "ch32v003.h"

static void simple_delay(volatile uint32_t count) {
  while (count--) {
    __asm__ volatile("nop");
  }
}

int main(void) {
  // 1. Enable clock for GPIOD
  RCC_ENABLE_PERIPH(RCC_APB2PCENR, RCC_APB2PCENR_IOPDEN);

  // 2. Configure PD4 as push-pull output, 10 MHz
  GPIO_CFG_SET(GPIOD_BASE, 4, GPIO_CFG_OUTPUT_PP_10MHZ);

  // 3. Blink
  while (1) {
    GPIOD_BSHR = GPIO_BS(4); // set PD4 high
    simple_delay(500000);
    GPIOD_BCR = GPIO_BR(4); // set PD4 low
    simple_delay(500000);
  }

  return 0;
}
