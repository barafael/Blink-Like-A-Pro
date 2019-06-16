typedef unsigned long uint32_t;

/* Addresses common to Cortex-m */
#define FLASH_BASE     0x08000000
#define SRAM_BASE      0x20000000
#define PERIPH_BASE    0x40000000

/* STM32F103C8T6 has 20KiB of SRAM */
#define SRAM_SIZE      20 * 1024
#define SRAM_END       (SRAM_BASE + SRAM_SIZE)

/* STM32F103C8T6 RCC preipheral addresses */
#define RCC_BASE       (PERIPH_BASE + 0x21000)
#define RCC_APB2ENR    ((uint32_t*)(RCC_BASE + 0x18))

/* STM32F103C8T6 GPIO port C addresses */
#define GPIOC_BASE     (PERIPH_BASE + 0x11000)
#define GPIOC_MODER    ((uint32_t*)(GPIOC_BASE + 0x4))
#define GPIOC_ODR      ((uint32_t*)(GPIOC_BASE + 0xc))

/* Crude delay function */
void delay(uint32_t count) {
	for(int i = 0; i < count; i++) {
		__asm__("nop");
	}
}

int main() {
    /* Initialize APB2 (Advanced Peripheral Bus 2) */
	*RCC_APB2ENR = 0x10;
    /* Set GPIO port C pin 13 as output */
	*GPIOC_MODER |= 0x200000;

    /* Set and Reset Output Data Register of PC13 */
	while(1) {
		*GPIOC_ODR = 0x2000;
		delay(200000);
		*GPIOC_ODR = 0x0;
		delay(200000);
	}
}

/* Interrupt vector at start of flash (see linker script) */
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
	(uint32_t*)SRAM_END, // initial stack pointer
	(uint32_t*)main      // main as reset handler
};
