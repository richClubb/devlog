MEMORY {
    flash : origin = 0x10000000, len = 64k
    ram : origin = 0x20000000, len = 8k

}

SECTIONS {
    .text : {
        *(.text);
    } > flash
}