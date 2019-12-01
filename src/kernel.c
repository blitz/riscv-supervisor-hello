extern void sbi_putchar(int c);

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
