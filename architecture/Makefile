################################
# Prism
################################
.PHONY: all
all: prism

.PHONY: clean
clean:
	rm prism.dtb

prism.dtb: prism.dts
	dtc -I dts -O dtb prism.dts > prism.dtb

.PHONY: dromajo
dromajo: prism.dtb
	dromajo prism.cfg

.PHONY: qemu
qemu: prism.dtb
	qemu-system-riscv64 -machine virt -nographic -bios ../software/bsp/firmware.bin -kernel ../software/linux/kernel.bin -initrd ../software/linux/rootfs.cpio -virtfs local,path=.,mount_tag=hostshare,security_model=passthrough

.PHONY: prism
prism: dromajo