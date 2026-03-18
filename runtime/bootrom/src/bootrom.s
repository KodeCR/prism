/* Ignite */
.section .text

.option nopic
.option norvc

.globl _reset
_reset:
    csrr a0, mhartid
    la a1, dtb
    la a2, fdi
    ld t0, start_addr
    jr t0

# .section .rodata
.align 4
fdi:
fdi_magic:      .8byte 0x4942534f  # OSDI
fdi_version:    .8byte 0x2         # v2
fdi_next_addr:  .8byte 0x80200000  # RAM+2MB*1core
fdi_next_mode:  .8byte 0x1         # S-mode
fdi_options:    .8byte 0x2
fdi_boot_hart:  .8byte 0x0

start_addr:     .dword __start_addr$

.align 8
dtb:
#ifdef BOOTROM_FDT
  .incbin BOOTROM_FDT
#endif