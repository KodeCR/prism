/* Ignite */
ENTRY(_start);

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS {
	. = ORIGIN(ram);
	.text : ALIGN(4K) {
		*(.init);
		*(.text);
	} >ram
	.rodata : ALIGN(4K) {
		*(.rodata*);
		*(.eh_frame);
	} >ram
	.data : ALIGN(4K) {
		*(.data);
		PROVIDE( __global_pointer$ = . + (4K / 2) );
		*(.sdata);
	} >ram
	.bss : ALIGN(4K) {
		PROVIDE(__bss_start = .);
		*(.bss);
		PROVIDE(__bss_end = .);
	} >ram
	.heap (NOLOAD) : ALIGN(8) {
        PROVIDE( __heap_start = . );
		PROVIDE( __heap_end = __stack_start - 1 );
    } >ram
	.stack (NOLOAD) : ALIGN(16) { /* leave last 4M for fdt */
		. = ORIGIN(ram) + LENGTH(ram) - 4M - 4096;
        PROVIDE( __stack_start = . );
		. += 4096;
        PROVIDE( __stack_pointer$ = . );
		PROVIDE( __stack_end = . );
    } >ram
}