/* Ignite */
ENTRY(_reset);
SECTIONS {
    .text : { 
        PROVIDE(__start_addr$ = 0x80000000);
        *(.text);
    }
}
