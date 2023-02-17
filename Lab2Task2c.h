/* 
 * Ze Xu (Take ownership of your code by naming all files) 
 * 1879419 
 * 2/2/23
 * Task2c_header is the custom header file used for task2c
 */ 
#ifndef __task2c_header__  //Header guard
#define __task2c_header__ 


//to set up and change data for GPIO:LEDS,SW,etc
#define RCGCGPIO         (*((volatile uint32_t *)0x400FE608)) 
#define GPIOAMSEL_L      (*((volatile uint32_t *)0x40062528)) 
#define GPIODIR_L        (*((volatile uint32_t *)0x40062400)) 
#define GPIODEN_L        (*((volatile uint32_t *)0x4006251C)) 
#define GPIOAFSEL_L      (*((volatile uint32_t *)0x40062420)) 
#define GPIODATA_L      (*((volatile uint32_t *)0x400623FC)) 

#define GPIOAMSEL_N      (*((volatile uint32_t *)0x40064528)) 
#define GPIODIR_N        (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N        (*((volatile uint32_t *)0x4006451C)) 
#define GPIOAFSEL_N      (*((volatile uint32_t *)0x40064420)) 
#define GPIODATA_N       (*((volatile uint32_t *)0x400643FC)) 

// Timer0 Set up timer and change timer0
#define RCGCTIMER	 (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_TIMER0	 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_TIMER0	 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_TIMER0	 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_TIMER0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_TIMER0	 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_TIMER0	 (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_TIMER0	 (*((volatile uint32_t *)0x40030018))

// Timer1 set up and change timer1
#define GPTMCTL_TIMER1	 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_TIMER1	 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_TIMER1	 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_TIMER1 (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_TIMER1	 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_TIMER1	 (*((volatile uint32_t *)0x40031024))
#define GPTMIMR_TIMER1	 (*((volatile uint32_t *)0x40031018))


// interrupt set up to allow interrupts
#define INTERRUPT_EN1 (*((volatile uint32_t *)0xE000E104))
#define INTERRUPT_EN0 (*((volatile uint32_t *) 0xE000E100))
  
//Sets up the LEDS so they are working properly
void LED_init();

//Sets up the switches so they can be used
void extern_switch_init();

//Sets up timer to use as counter
void TimerInit();

//turn on green led
void LED_on_green(void);
//turn off green led
void LED_off_green(void);

// turn on yellow led
void LED_on_yellow(void);
//turn off yellow led
void LED_off_yellow(void);

//turn on red led
void LED_on_red(void);
//turn off red led
void LED_off_red(void);

#endif //header guard