#ifndef __HEADER2_H__
#define __HEADER2_H__

//For all of these steps use the 16/32 Timer O

//0. Header from Lab 1, Task 1a. Switches unneeded.
#define RCGCGPIO (*((volatile uint32_t *) 0x400FE608))

#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))

#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))

#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

//1. Enable the appropriate TIMERn bit in the RCGCTIMER register.
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

//2. Disable the timer using the GPTMCTL register.
#define GPTMCTL_0   (*((volatile uint32_t *)0x4003000C))

//3. Write 0x0000.0000 to the GPTMCFG register.

//4. Select 32-bit mode using the GPTMCFG register.
#define GPTMCFG_0   (*((volatile uint32_t *)0x40030000)) 
//Set to 0x0 in main for 32 bit timer configuration.

//5. Configure the TAMR bit of the GPTMTAMR register to be in periodic timer mode.
#define GPTMTAMR_0  (*((volatile uint32_t *)0x40030004))
//Set TAMR to 0x2 for periodic mode. Access TAMR accessing both 0 and 1 bit.

//6. Configure the TACDIR bit of the GPTMTAMR register to count down.

//7. Load the value 16,000,000 into the GPTMTAILR to achieve a 1Hz blink rate
//using the 16MHz oscillator.
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
//Load value 16,000,000 - 0x00F42400.

//8. If using interrupts, configure the GPTMIMR register.
#define GPTMIMR_0   (*((volatile uint32_t *)0x40030018))

//9. Enable the timer using the GPTMCTL register.

//10. Poll a GPTM. From lecture slides, ICR clears flag. RIS monitors flag.
#define GPTMRIS_0  (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0  (*((volatile uint32_t *)0x40030024)) 

//11. INTERRUPT_EN
#define INTERRUPT_EN0 (*((volatile uint32_t *) 0xE000E100))
#endif //__HEADER2_H__
