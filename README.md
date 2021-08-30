# RISC-V Supervisor Hello World

To build:

```
% nix build -f . kernel
```

To run (with qemu >= 6.0):

```
% qemu-system-riscv64 -M virt -m 256M -serial stdio \
     -bios default -device loader,file=result/kernel.elf
# Or if direnv is available:
% boot -device loader,file=result/kernel.elf
```

The `addr=` parameter must equal the entry point of the kernel.

# Resources

- https://github.com/riscv/riscv-sbi-doc/blob/master/riscv-sbi.adoc
- https://riscv.org/wp-content/uploads/2015/01/riscv-calling.pdf
- https://wiki.qemu.org/Documentation/Platforms/RISCV
