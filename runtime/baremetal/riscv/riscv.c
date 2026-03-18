/* Ignite */
#include "riscv.h"
#include "../libc/libc.h"

void handle_trap() {
    unsigned long mcause, mepc;
    __asm__ volatile("csrr %0, mcause" : "=r"(mcause));
    __asm__ volatile("csrr %0, mepc" : "=r"(mepc));
    printf("Exception - mcause: %lu, mepc: %lu\n", mcause, mepc);
}

long time() {
    unsigned long t;
    t = read_csr(CSR_MCYCLE);
    // return (t/1000000);
    return t;
}

clock_t times(struct tms *t) {
    clock_t n;
    n = read_csr(CSR_MCYCLE);
    t->tms_utime = n;
    t->tms_stime = n;
    t->tms_cutime = 0;
    t->tms_cstime = 0;
    return n;
}
