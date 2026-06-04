.section .vectors, "ax"
.align 2
.global _start
_start:
  .word _estack # 0x00
  .word Reset_Handler # 0x04
  .word NMI_Handler # 0x08
  .word HardFault_Handler # 0x0C
  
.section .text.Reset_Handler, "ax"
.align 2
.global Reset_Handler
.type Reset_Handler, @function
Reset_Handler:
  la sp, _estack
  la a0, _sidata
  la a1, _data_start
  la a2, _data_end
  beq a1, a2, 2f
1:
  lw a3, 0(a0)
  sw a3, 0(a1)
  addi a0, a0, 4
  addi a1, a1, 4
  bltu a1, a2, 1b
2:
  la a0, _bss_start
  la a1, _bss_end
  beq a0, a1, 2f
1:
  sw zero, 0(a0)
  addi a0, a0, 4
  bltu a0, a1, 1b
2:
  call main
  j Default_Handler


.weak NMI_Handler
.weak HardFault_Handler
.weak Default_Handler

.section .text.Default_Handler, "ax"
.align 2
.global Default_Handler
.type Default_Handler, @function
Default_Handler:
  j Default_Handler

.set NMI_Handler, Default_Handler
.set HardFault_Handler, Default_Handler
