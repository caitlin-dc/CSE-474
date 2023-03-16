//_____________________ Lab4_Inits.h _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * March 2, 2023
 * EE/CSE 474: Lab4 Initializations header
 */

#ifndef __TASK1B_H__
#define __TASK1B_H__

// ************************ GPIO E AND J **************************** //
#define RCGCGPIO        (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_E       (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E       (*((volatile uint32_t *)0x4005C51C))
#define GPIODATA_E      (*((volatile uint32_t *)0x4005C3FC))
#define GPIOAMSEL_E     (*((volatile uint32_t *)0x4005C528))
#define GPIOAFSEL_E     (*((volatile uint32_t *)0x4005C420))
#define GPIODIR_J       (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J       (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J       (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J      (*((volatile uint32_t *)0x400603FC))

// **************************** TIMER 0 ***************************** //
#define RCGCTIMER       (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0       (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0       (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0      (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0     (*((volatile uint32_t *)0x40030028))

#define GPTMRIS_0       (*((volatile uint32_t *)0x4003001C))
#define GPTMADCEV_0     (*((volatile uint32_t *)0x40030070))
#define GPTMICR_0       (*((volatile uint32_t *)0x40030024))

// ****************************** ADC ******************************** //
#define RCGCADC         (*((volatile uint32_t *)0x400FE638))

#define ADCACTSS        (*((volatile uint32_t *)0x40038000))
#define ADCCC           (*((volatile uint32_t *)0x40038FC8))

#define ADCIM           (*((volatile uint32_t *)0x40038008))
#define ADCISC          (*((volatile uint32_t *)0x4003800C))

#define ADCSSFIFO3      (*((volatile uint32_t *)0x400380A8))
#define ADCSSCTL3       (*((volatile uint32_t *)0x400380A4))

#define ADCSSEMUX3      (*((volatile uint32_t *)0x400380B8))
#define ADCSSMUX3       (*((volatile uint32_t *)0x400380A0))

#define ADCEMUX         (*((volatile uint32_t *)0x40038014))

#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

// ************************* SWITCHES ******************************** //
unsigned long SW1_press();

unsigned long SW2_press();


#endif