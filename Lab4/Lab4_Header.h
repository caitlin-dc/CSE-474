//_____________________ Lab4_Header.h _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * March 2, 2023
 * EE/CSE 474: Lab 4 Header file with initializations
 */

#ifndef __HEADER1_H__ 
#define __HEADER1_H__ 

// ************************ GPIO Main Inits ************************ //
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

// ************************ Timer 0 ******************************* //
#define RCGCTIMER	 (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_TIMER0	 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_TIMER0	 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_TIMER0	 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_TIMER0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_TIMER0	 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_TIMER0	 (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_TIMER0	 (*((volatile uint32_t *)0x40030018))
#define GPIOAFSEL_N      (*((volatile uint32_t *)0x40064420)) 
#define GPIODATA_N       (*((volatile uint32_t *)0x400643FC)) 

// ************************ Timer 1 ******************************* //
#define GPTMCTL_TIMER1	 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_TIMER1	 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_TIMER1	 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_TIMER1 (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_TIMER1	 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_TIMER1	 (*((volatile uint32_t *)0x40031024))
#define GPTMIMR_TIMER1	 (*((volatile uint32_t *)0x40031018))

// ************************ Timer 2 ******************************* //
#define GPTMCTL_TIMER1	 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_TIMER1	 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_TIMER1	 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_TIMER1 (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_TIMER1	 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_TIMER1	 (*((volatile uint32_t *)0x40031024))
#define GPTMIMR_TIMER1	 (*((volatile uint32_t *)0x40031018))
  
#endif
