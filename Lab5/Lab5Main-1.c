//_____________________ Lab5Main.c _____________________
/*
 * Caitlin DeShazo-Couchot  and Ze Xu
 * Student ID: 2039775
 * March 9, 2023
 * EE/CSE 474: Lab5 main function to dim lights.
 */

#include <stdio.h>
#include <stdint.h>
#include "Lab5_Inits.h"
#include "Lab5Header.h"

//Prototype.
void ADC0SS3_Handler(void);
unsigned long SW1_press();
unsigned long SW2_press();

//Pressing between two switches changes the duty cycle
int main(void) {
  // Select system clock frequency preset
  PLL_Init(20); 
  LED_Init();
  SWITCHES_Init();
  PWM_Init();
  while(1) {  
    //Change the pattern of LEDs based on the duty cycle
    if (SW1_press()) {
      PWM0CMPA = 30000; //low duty cycle
    } else if (SW2_press()) {
       PWM0CMPA = 10000; //high duty cycle
    }
  }
  return 0;
}

//SW1 Press
unsigned long SW1_press()
{
  return !(GPIODATA_J & 0x1);
}

//SW2 Press
unsigned long SW2_press()
{
  return !(GPIODATA_J & 0x2);
}