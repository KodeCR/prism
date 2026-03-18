/* Ignite */
#ifndef RISCV_H
#define RISCV_H

// #include <sys/times.h>
typedef	unsigned long clock_t;
struct tms {
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
};

#define CSR_MCYCLE 0xb00
#define read_csr(csr) ({unsigned long __tmp; __asm__("csrr %0, %1" : "=r"(__tmp) : "i"(csr) ); __tmp;})

void handle_trap();
long time();
clock_t times(struct tms *t);

#endif /* RISCV_H */
