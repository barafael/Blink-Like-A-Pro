## Blinky Using DMA and Bit Banding (impossible)

As the bit banding region is only available for the CPU as master, the DMA cannot access it. Hence, this approach does not work.

>The Cortex®-M3 memory map includes two bit-band regions. These regions map each word in an alias region of memory to a bit in a bit-band region of memory. Writing to a word in the alias region has the same effect as a read-modify-write operation on the targeted bit in the bit-band region.
>In the STM32F10xxx both peripheral registers and SRAM are mapped in a bit-band region. This allows single bit-band write and read operations to be performed. The operations are only available for Cortex®-M3 accesses, not from other bus masters (e.g. DMA).

`RM0008 Reference manual on STM32F103xx (and other) advanced Arm®-based 32-bit MCUs`
