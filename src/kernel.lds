#include "memory.h"

OUTPUT_ARCH( "riscv" )
ENTRY(init)

PHDRS {
      lo_rx PT_LOAD FLAGS (5); /* RX */
      lo_r  PT_LOAD FLAGS (4); /* R  */
      lo_rw PT_LOAD FLAGS (6); /* RW */
}

SECTIONS
{
  . = LOAD_ADDRESS;
  .text (LOAD_ADDRESS) :
  {
    *(.text.init)
    *(.text .text.*)
  } : lo_rx

  .rodata : { *(.rodata .rodata.*) } : lo_r
  .data   : { *(.data .data.*) } : lo_rw
  .bss    : { *(.bss .bss.*) } : lo_rw

  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}
