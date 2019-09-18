# Blink LEDs Like a Pro

A blinking LED is the "hello world" of embedded systems, as it is trivially implemented without much effort.
But beyond the basic blocking blinky, modern microcontrollers offer a dizzying variety of peripherals like timers and DMA controllers.
These allow us to overengineer our "blinky" to the maximum!

Along the way, we will learn how to utilize the advanced asynchronous capabilities of modern ARM MCUs.
These allow us to capture data from sensors or communication peripherals (almost) without interrupts or FIFOs.
Additionally, we will get a glimpse into MCU debugging techniques, state-of-the-art code generation tools, typestate programming, and basic RTOS use.
Finally, we will make use of our new knowledge to create an extremely efficient driver for individually addressable RGB LED strips.

The goal of this talk is to show some of the specialties and peculiarities of embedded software.
If you are new to embedded programming and want to see where it could go, if you wonder how embedded software is different from applications/other software, or if you are using Arduino but wonder just how much you are missing, this talk is for you!
