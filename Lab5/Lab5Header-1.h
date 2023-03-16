//_____________________ Lab5Header.h _____________________
/*
 * Caitlin DeShazo-Couchot  and Ze Xu
 * Student ID: 2039775
 * March 9, 2023
 * EE/CSE 474: Lab5 header function to dim lights.
 */

#ifndef _LAB5_H_
#define _LAB5_H_

#include <stdint.h>

// ********************** GPIO N and F (LEDs) ************************ //
#define RCGCGPIO_0              (*((volatile uint32_t *)0x400FE608)) 
#define GPIODIR_F               (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F               (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F              (*((volatile uint32_t *)0x4005D3FC))
#define GPIOAFSEL_F             (*((volatile uint32_t *)0x4005D420))
#define GPIOPCTL_F              (*((volatile uint32_t *)0x4005D52C))


#define GPIODIR_N               (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N               (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N              (*((volatile uint32_t *)0x400643FC))

// ********************* GPIO J (Switches) ************************** //
#define RCGCGPIO        (*((volatile uint32_t *)0x400FE608))
#define GPIODIR_J       (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J       (*((volatile uint32_t *)0x4006051C))
#define GPIOPUR_J       (*((volatile uint32_t *)0x40060510))
#define GPIODATA_J      (*((volatile uint32_t *)0x400603FC))

// ****************************** PWM ******************************** //
//PWMCC 
#define PWMCC (*((volatile uint32_t *)0x40028FC8))


//PWMnLOAD 
#define PWM0LOAD (*((volatile uint32_t *)0x40028050))

//PWMnCMPA
#define PWM0CMPA (*((volatile uint32_t *)0x40028058))


//PWMnCMPB
#define PWM0CPMB (*((volatile uint32_t *)0x4002005C))

//PWMENABLE
#define PWMENABLE (*((volatile uint32_t *)0x40028008))


//PWMnCTL
# define PWM0CTL (*((volatile uint32_t *)0x40028040))

//PWMnGENA
#define PWM0GENA (*((volatile uint32_t *)0x40028060))


//PWMnGENB
#define PWM0GENB (*((volatile uint32_t *)0x40028064))

//RCGCPWM
#define RCGCPWM (*((volatile uint32_t *)0x400FE640))

//SWITCHES
unsigned long SW1_press();

unsigned long SW2_press();

#endif //_LAB5_H_