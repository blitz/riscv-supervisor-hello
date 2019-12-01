# RISC-V Supervisor Hello World

To build:

```
% nix build -f . kernel
```

To run (with qemu >= 4.1):

```
% qemu-system-riscv64 -M virt -m 256M -serial stdio \
     -bios default -device loader,file=result/kernel,addr=0x80200000
# Or if lorri/direnv is available:
% boot -device loader,file=result/kernel,addr=0x80200000
```

The `addr=` parameter must equal the entry point of the kernel.