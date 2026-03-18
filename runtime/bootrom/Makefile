################################
# Ignite - bootrom
################################
.PHONY: all
all: bootrom.bin

.PHONY: clean
clean:
	rm -rf build bootrom.bin

build/bootrom.o: src/bootrom.s
	mkdir -p build
	# riscv-kaleidoscope-none-as -march=rv64i_zicsr -mabi=lp64 -c src/bootrom.s -o build/bootrom.o
	clang -march=rv64i_zicsr -x assembler-with-cpp -c src/bootrom.s -o build/bootrom.o

build/bootrom.elf: src/bootrom.ld build/bootrom.o
	# riscv-kaleidoscope-none-ld -melf64lriscv -nostdlib -T src/bootrom.ld build/bootrom.o -o build/bootrom.elf
	clang -march=rv64i_zicsr -nostdlib -T src/bootrom.ld build/bootrom.o -o build/bootrom.elf

bootrom.bin: build/bootrom.elf
	# riscv-kaleidoscope-none-objcopy -O binary build/bootrom.elf bootrom -j .text
	llvm-objcopy -O binary build/bootrom.elf bootrom.bin -j .text