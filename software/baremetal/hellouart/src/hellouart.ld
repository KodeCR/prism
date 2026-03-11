ENTRY(_start);
 
SECTIONS {
	. = 0x80000000;
	.text : ALIGN(4K) {
		*(.init);
		*(.text);
	}
	.rodata : ALIGN(4K) {
		*(.rodata*);
		*(.eh_frame);
	}
	.data : ALIGN(4K) {
		*(.data);
		*(.sdata);
	}
	.bss : ALIGN(4K) {
		PROVIDE(__bss_start = .);
		*(.bss);
		. += 4096;
		PROVIDE(__stack_pointer$ = .);
		. += 4096;
		PROVIDE(__global_pointer$ = .);
		PROVIDE(__bss_end = .);
	}
}