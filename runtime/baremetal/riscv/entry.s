/* Ignite */
.section .init

.equ syscon, 0x100000
.equ shutdown, 0x5555

.type _start, @function
.global _start
_start:
.cfi_startproc
.cfi_undefined ra
.option norvc

    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_pointer$
    csrw satp, zero

    # trap handler
    csrr  x1, mhartid
    la    t0, _trap_handler
    csrw  mtvec, t0
    csrw  mie, zero

    # clear bss
    la t5, __bss_start
    la t6, __bss_end
bss_clear:
    sd zero, (t5)
    addi t5, t5, 8
    bltu t5, t6, bss_clear

    # enable floating point
    csrr t0, misa
    li t1, 1 << 5
    and t0, t0, t1
    beq t0, x0, _no_fpu
    li t0, 0x00006000
    csrs mstatus, t0
_no_fpu:

    # call main
    mv s0, sp
    call main

syscon_exit:
    li a0, syscon
    li t0, shutdown
    sw t0, 0(a0)

# tohost_exit:
#     slli a0, a0, 1
#     ori a0, a0, 1

#     la t0, tohost
#     sd a0, 0(t0)

_end:
    wfi
    j _end

.balign 4
.option norvc 
_trap_handler:
    jal handle_trap
    j _halt

.cfi_endproc

# .align 4
# .globl tohost
# tohost: .dword 0
# .globl fromhost
# fromhost: .dword 0

.end
