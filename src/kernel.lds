OUTPUT_ARCH( "riscv" )
ENTRY(init)

SECTIONS
{
  /* RAM is typically mapped here. */
  . = 0x80200000;
  .text           :
  {
    *(.text.init)
    *(.text .text.*)
  }

  .rodata : { *(.rodata .rodata.*) }
  .data   : { *(.data .data.*) }
  .bss    : { *(.bss .bss.*) }

  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}
