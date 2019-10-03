# Intro
About me (studied here, work now)
Quick facts about my interests: systems software that does not (and must not) fail.
Quick funny rant about work place:
Frontend dev at MEN: show front plate of Sirti, AF2, BL72e etc.
Computers with 2010 intel atom that cost 35000 euros and weigh 12 kilograms
Large customers, SIL4 stuff, SIL2 stuff, SIL0 stuff. Some OS licenses are in the 10000s
FPGA Quartus 6-15, C++ considered modern (mostly C)
Shy away from implementing features (even safety features) because they would have to be certified
C++ vtables and other features reimplemented in C

Last talk here was about getting hardware to run. Now, I work at a company where people are paid to do this right for me.
So this talk is about embedded software.
Goal is not to teach C or C++, and goal is not to make you embedded developer in 45 minutes (that's a different talk).
Instead, goal is to give a quick safari about the topics I find important for getting started/intermediate level.

# Basic Blocking Blinky
* Show basic blinky (with registers/assembler/linker, bare minimum example) - this is a bit frightening, shows value of cubemx and HAL.
* Then use C and the ST HAL and CubeMX.
* Follow through HAL functions: what do they do? Set some registers.
* Debugger and SFR view ODR. Kill debugging pins from SFR view.

# In General: Memory Mapped Peripherals
* Usually, *0xcafebabe = 0x1 stores a 1 in memory
* But actually: what looks like a memory address might not be one!
* Some registers (addresses) have Special Functions (they are not memory cells)

# Examples
* Write 0x1 to 0xcafebeef turns LED on
* If 0xdadcraf7 == 0x32afcafe, then ADC sample can be read from 0x0ADCDA7A

# Nothing "makes sense"
* Memory Mapping: Arbitrary set of contracts
* Defined by cryptic names in data sheet, depending on how peripherals are connected (we will get to that)
  - Setting a bit in a register somewhere might brick your controller or set your rocket on fire
  (as opposed to just a SEGFAULT in other systems)
  - Other talk: Scary Introduction to Embedded Systems (Everything is globally mutable state)

Emphasize that we are using the processor to put bits in registers by showing a simple blocking UART with sermon.

# (Short Aside) Asynchronous Approaches
* delay is not good!
* Manual 'yield' does not scale too well
    - if (elapsedTime > 500) { doThing() }
    - essentially, manual collaborative multitasking
* RTOS, but then you have to deal with actual concurrency
    - At each blocking call, scheduler switches tasks
    - Show how simple setting up freertos is in CubeMX. Start a few tasks.
    - What is the benefit? Decoupling, and a cheap way to REDUCE power consumption (wfi, tickless wait).

# Asynchronous Timer Blinky
Theory: in the blinky example, what was HAL_Delay(millis)? Based on clock cycles? Could be, but not portable and inaccurate.
Instead: a timer is used. Explain counter, PERIOD, PRESCALER, equation.
Show timer config in Cube. Show Clock Tree in Cube.
Theory: interrupts. Discuss asynchronicity, how the real world is really asynchronous and parallel, and blocking waiting is bad when you want to do any work (might miss events).
Discuss interrupt priorities, preemption levels, NVIC? There is no back-preemption, without scheduler, hence stupid lock is safe.
Show interrupt on timer update event. Toggle LED. Main loop is empty! But processor is still busy shuffling bits around.
To emphasize, show reading the ADC with interrupts. Show value in STM Studio? Would need windows. Or segger system view?

# In General: Busses, Masters, Arbitration
* What happens really when we access a memory location?
* SRAM/Flash Memory and most Peripherals are attached to the same bus system
* CPU acts as a master (triggers bus transfers)
* Arbitration happens automatically in hardware (bus stalls, round robin)

Image: Bus Matrix

# Consequences
* Very often, data must be moved from some address to some other address
    - Especially for communication peripherals or for fast measurements
    - Peripheral to memory (sensor), memory to peripheral (actuator), memory to memory (memcpy)
* Often used with interrupts
* Many Load/Stores during an interrupt
-> Interrupt based systems actually do not have a big performance benefit! CPU still busy.

But wait - there is another master on the bus matrix!

# DMA Blinky
Theory: data pump. Can be connected by both ends to peripherals or memory.
Can increment both ends automatically.
Like memcpy, except that the processor does not move a finger! No interrupts, either.
Show timer triggering a DMA transfer to GPIOx->BSRR.
Example: DMA parallel port driver for displays.
Example: ws2812 driver. Show how C++ can be used together with HAL (friend functions, extern "C", handles, RAII).

# Code Generation Tools
Shout out to CubeMX. How do they do that?!
.svd file format: show snippet.
This looks almost like one could generate entire APIs from it.
-> svd2rust: generates type-safe HAL from svd files! Meaning that it is impossible to write to a read-only register, and many other benefits, at compile time.
embedded-hal: uses that autogenerated HAL and builds higher abstractions on it. These evaporate away (this is Rust).
Open new opportunities: Can be mocked, or simulated, great for testing and formal techniques.
Show the GPIO output pin example where a pin cannot be misused as in/output - this is typestate programming.
I see a lot of potential for Rust for systems software that must be highly robust and performant.
Damn it! I did it again. I turned a perfectly fine talk into a Rust commercial.
The downside is apparent: C is way simpler initially. The ecosystem is still changing rapidly. Rust is challenging to learn.

# Outro
We saw: memory mapping, RTOS, timers, interrupts, DMA, Outlook on software tools and Rust.
Questions?
