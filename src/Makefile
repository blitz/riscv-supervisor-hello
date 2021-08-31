BOARD   ?= QEMU

TARGET  ?= output

CFLAGS  += -DBOARD_$(BOARD) -Os -g -fno-common -fomit-frame-pointer -mcmodel=medany -ffreestanding -nostdinc -march=rv64gc
LDFLAGS += -static -nostdlib


.PHONY: all
all: kernel.bin kernel.elf

.PHONY: clean
clean:
	rm -f kernel.bin kernel.elf kernel.ld

.PHONY: install
install: kernel.bin kernel.elf
	mkdir -p $(TARGET)
	install -m 0755 $^ $(TARGET)/

kernel.ld: kernel.lds memory.h
	$(CC) -xc -E -P $(CFLAGS) -o $@ $<

kernel.elf: kernel.ld start.S kernel.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -T $^

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@
