################################
# Ignite - firmware (OpenSBI)
################################
.PHONY: all
all: firmware

.PHONY: clean
clean:
	rm -rf opensbi
	rm firmware.bin

opensbi/.git:
	git clone --depth 1 https://github.com/riscv-software-src/opensbi.git --branch v1.5
	cd opensbi && git apply ../fw_dynamic.patch

opensbi/build/platform/generic/firmware/fw_dynamic.bin: opensbi/.git
	# make CROSS_COMPILE=riscv-kaleidoscope-none-gnu- PLATFORM=generic
	make LLVM=1 PLATFORM=generic FW_JUMP_FDT_ADDR=0x82200000

firmware.bin: opensbi/build/platform/generic/firmware/fw_dynamic.bin
	cp opensbi/build/platform/generic/firmware/fw_dynamic.bin ./firmware.bin

.PHONY: opensbi
opensbi: firmware.bin

.PHONY: firmware
firmware: firmware.bin
