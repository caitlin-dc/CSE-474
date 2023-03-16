//_____________________ Lab3.h _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * February 14, 2023
 * EE/CSE 474: Lab3 header created by student.
 */

#ifndef _LAB3_H_
#define _LAB3_H_

#include <stdint.h>

// ****************************** LEDS ******************************* //
#define GPIODIR_F               (*((volatile uint32_t *)0x4005D400))
#define GPIODIR_N               (*((volatile uint32_t *)0x40064400))

#define GPIODEN_F               (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N               (*((volatile uint32_t *)0x4006451C))

#define GPIODATA_F              (*((volatile uint32_t *)0x4005D3FC))
#define GPIODATA_N              (*((volatile uint32_t *)0x400643FC))
   
// ****************************** ADC ******************************** //
#define RCGCGPIO_0              (*((volatile uint32_t *)0x400FE608)) 
#define RCGCADC_0               (*((volatile uint32_t *)0x400FE638)) 
#define ADCACTSS_0              (*((volatile uint32_t *)0x40038000)) 
#define ADCCC_0                 (*((volatile uint32_t *)0x40038FC8))
#define GPIODEN_0               (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_0             (*((volatile uint32_t *)0x4005C420))
#define GPIOAMSEL_0             (*((volatile uint32_t *)0x4005C528))
#define ADCSSMUX3               (*((volatile uint32_t *)0x400380A0))
#define ADCSSEMUX3              (*((volatile uint32_t *)0x400380B8))
#define ADCIM_0                 (*((volatile uint32_t *)0x40038008))
#define ADCISC                  (*((volatile uint32_t *)0x4003800C))
#define ADCSSFIFO3              (*((volatile uint32_t *)0x400380A8))
#define ADCSSCTL3_0             (*((volatile uint32_t *)0x400380A4))
#define GPTMADCDEV_0            (*((volatile uint32_t *)0x40030070))
#define ADCEMUX                 (*((volatile uint32_t *)0x40038014))


// **************************** TIMER 0 ***************************** //
#define RCGCTIMER_0             (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0               (*((volatile uint32_t *)0x4003000C))                                                                                                 
#define GPTMCFG_0               (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0              (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0             (*((volatile uint32_t *)0x40030028))

// *************************** INTERRUPTS *************************** //
#define GPTMRIS_0               (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0               (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_0               (*((volatile uint32_t *)0x40030018))
#define NVIC_EN0                (*((volatile uint32_t *)0xE000E100))

// *************************** Port A ****************************** //
#define GPIOAFSEL_A             (*((volatile uint32_t *)0x40058420))
#define GPIOPCTL_A              (*((volatile uint32_t *)0x4005852C))
#define GPIODEN_A               (*((volatile uint32_t *)0x4005851C))
#define GPIOSLR_A               (*((volatile uint32_t *)0x40058518))
#define GPIODR2R_A              (*((volatile uint32_t *)0x40058500))

// ***************************** UART ****************************** //
#define RCGCUART             (*((volatile uint32_t *)0x400FE618)) //UART Clock

//Baud Rate Generator
#define UARTIBRD_2              (*((volatile uint32_t *)0x4000E024)) //Baud Rate Divisor - Int
#define UARTFBRD_2              (*((volatile uint32_t *)0x4000E028)) //Baud Rate Divisor - Fraction
#define UARTCC_2                (*((volatile uint32_t *)0x4000EFC8)) //Line Control

//Control and Status Unit
#define UARTLCRH_2              (*((volatile uint32_t *)0x4000E02C)) //Configure. To set up FIFO, enable FEN bit.
#define UARTCTL_2               (*((volatile uint32_t *)0x4000E030)) //Control

//Transmit Unit
#define UARTFR_2                (*((volatile uint32_t *)0x4000E018)) //Flag
#define UARTDR_2                (*((volatile uint32_t *)0x4000E000)) //Data  


#endif //_LAB3_H_