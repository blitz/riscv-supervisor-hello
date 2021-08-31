#pragma once


#if defined(BOARD_NEZHA)
#define LOAD_ADDRESS 0x41000000
#elif defined(BOARD_QEMU)
#define LOAD_ADDRESS 0x80200000
#else
#error "Please specify the board type."
#endif

