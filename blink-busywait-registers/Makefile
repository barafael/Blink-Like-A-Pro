TOOLCHAIN_PATH = /usr/bin

CC = $(TOOLCHAIN_PATH)/arm-none-eabi-gcc
OBJCPY = $(TOOLCHAIN_PATH)/arm-none-eabi-objcopy
GDB = $(TOOLCHAIN_PATH)/arm-none-eabi-gdb
 
C_CPU_FLAGS = -mcpu=cortex-m3 -mthumb 
C_DEBUG_FLAGS = -g
C_OTHER_FLAGS = -ffunction-sections -fdata-sections
C_OPTIMIZATION_FLAGS = -O0
C_LANGUAGE_FLAGS = -std=c11

CFLAGS = $(C_CPU_FLAGS) $(C_DEBUG_FLAGS) $(C_OTHER_FLAGS) $(C_OPTIMIZATION_FLAGS)
LD_FLAGS = -T memory.x -Wl,-Map=main.map -Wl,--gc-sections -nostartfiles
 
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

all: main.hex main.bin

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)
 
main.elf: $(OBJECTS)
	$(CC) -o $@ $(C_CPU_FLAGS) $(LD_FLAGS) $^
 
main.bin: main.elf
	$(OBJCPY) -O binary $^ $@
 
main.hex: main.elf
	$(OBJCPY) -O ihex $^ $@
 
clean:
	rm -rf *.o *.elf *.bin *.hex *.map
	
flash: main.bin
	st-flash write main.bin 0x08000000
