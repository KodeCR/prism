################################
# Spectra
################################
.PHONY: all
all: dhrystone coremark

.PHONY: clean
clean:
	rm dhrystone.elf coremark.elf

.PHONY: dhrystone
dhrystone: dhrystone.elf

dhrystone.elf: dhrystone/dhry_1.c dhrystone/dhry_2.c dhrystone/dhry.h
	clang -march=rv64im_zicsr -mabi=lp64 -mcmodel=medany -ffreestanding -nostdlib -T baremetal/baremetal.ld -O3 -g -Wall -Wextra -Wno-implicit-int -Wno-implicit-function-declaration -DTIME baremetal/riscv/entry.s baremetal/riscv/riscv.c baremetal/libc/libc.c baremetal/uart/uart.c dhry_1.c dhry_2.c -o dhrystone.elf
	mv dhrystone/dhrystone.elf .

run_dhrystone: dhrystone.elf
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel dhrystone.elf

.PHONY: whetstone
whetstone: whetstone.elf

whetstone.elf: whetstone/whetstone.c
	clang -march=rv64imafdc_zicsr -mabi=lp64 -mcmodel=medany -ffreestanding -nostdlib -T baremetal/baremetal.ld -O0 -g -Wall -Wextra -Wno-implicit-int -Wno-implicit-function-declaration -DTIME baremetal/riscv/entry.s baremetal/riscv/riscv.c baremetal/libc/libc.c baremetal/uart/uart.c whetstone.c -o whetstone.elf
	mv whetstone/whetstone.elf .

run_whetstone: whetstone.elf
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel whetstone.elf

.PHONY: coremark
coremark: coremark.elf

coremark/.git: coremark/riscv-baremetal
	cd coremark; \
	git init; \
	git remote add origin https://github.com/eembc/coremark.git; \
	git fetch; \
	git checkout d5fad6b

coremark.elf: coremark/.git
	make PORT_DIR=riscv-baremetal ITERATIONS=1
	mv coremark/coremark.elf .

.PHONY: run_coremark
run_coremark: coremark.elf
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel coremark.elf
