#include <stdint.h>

/*------ Handlers ---------*/
void Reset_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Default_Handler(void);

/*-------- symbols in ld -------*/
extern uint32_t _estack;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _sidata;

/*---- main in main.c -------*/
extern int main(void);

/*--------  vector table --------*/
__attribute__((section(".vectors"))) const uint32_t vector_table[] = {
    (uint32_t)&_estack,          // 0x00
    (uint32_t)Reset_Handler,     // 0x04
    (uint32_t)NMI_Handler,       // 0x08
    (uint32_t)HardFault_Handler, // 0x0C
};

void Default_Handler(void) {
  while (1)
    ;
}

void Reset_Handler(void) {
  uint32_t *src, *dst;

  src = &_sidata;
  dst = &_data_start;
  while (dst < &_data_end) {
    *dst++ = *src++;
  }

  dst = &_bss_start;
  while (dst < &_bss_end) {
    *dst++ = 0;
  }

  main();
  while (1)
    ;
}
