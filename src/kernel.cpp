extern "C" void sbi_putchar(int c);
extern "C" void start();

static void print(const char *str)
{
  for (;*str;str++) {
    sbi_putchar(*str);
  }
}

void start()
{
  print("\nHello World!\n");
}
