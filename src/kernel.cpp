#include "memory.h"

extern "C" void sbi_putchar(int c);
extern "C" void sbi_shutdown(void);
extern "C" void start();

namespace {

  using mword_t = unsigned long;
  static_assert(sizeof(mword_t) == sizeof(void *));

  constexpr unsigned long PAGE_SHIFT {12};
  constexpr unsigned long PAGE_SIZE  {1UL << PAGE_SHIFT};

  void print(const char *str)
  {
    for (;*str;str++) {
      sbi_putchar(*str);
    }
  }

  enum {
	CSR_SATP = 0x180U,
  };

  enum {
	SATP_MODE_SV39 = 8UL << 60,
  };

  template <mword_t CSR>
  void write_csr(mword_t value)
  {
    asm volatile ("csrw %[csr], %[val]"
		  :
		  : [csr] "i" (CSR), [val] "r" (value)
		  : "memory");
  }

  void sfence_vma()
  {
    // This flushes everything for now.
    asm volatile ("sfence.vma x0, x0");
  }

  alignas(PAGE_SIZE) mword_t pt_lvl0[512];

  enum {
	PTE_V = 1UL << 0,
	PTE_R = 1UL << 1,
	PTE_W = 1UL << 2,
	PTE_X = 1UL << 3,
	PTE_U = 1UL << 4,
	PTE_G = 1UL << 5,
	PTE_A = 1UL << 6,
	PTE_D = 1UL << 7,
  };
}



void start()
{
  print("\n>>> Reached C++ code. :-)\n");

  // An identity mapped 1 GB page at the load address.
  //
  // Setting A/D is important for hardware that generates page faults
  // when these are not set.
  pt_lvl0[LOAD_ADDRESS >> 30] = PTE_V | PTE_R | PTE_W | PTE_X | PTE_A | PTE_D | ((LOAD_ADDRESS >> 30) << 28);

  sfence_vma();
  write_csr<CSR_SATP>(SATP_MODE_SV39 | (reinterpret_cast<mword_t>(pt_lvl0) >> PAGE_SHIFT));

  print(">>> Paging enabled.\n\n");
  sbi_shutdown();
}
