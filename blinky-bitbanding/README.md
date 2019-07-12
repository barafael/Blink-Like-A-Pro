## Blinking with Bit Banding

To access a single bit in a register, usually the entire register needs to be read and written. However, sometimes it is necessary to atomically set one bit.
In cortex MCUs, some memory regions can be read/written bit-by-bit by writing to aliased memory regions. This can be used to atomically set/reset single bits in registers.
