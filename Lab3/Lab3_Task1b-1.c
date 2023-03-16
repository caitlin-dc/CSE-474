//_____________________ Lab3_Task1b.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * February 14, 2023
 * EE/CSE 474: Lab3 Task1b main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdio.h>
#include <stdint.h>
#include "Lab3Inits.h"

#include "lab3.h"

uint32_t ADC_value;     //Stores ADC Value

//Checks if SW1 has been utilized
unsigned long SW1_press()

//Checks if SW2 has been utilized
unsigned long SW2_press()

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  SWITCHES_Init();
  
  //Change freq based on which sw is pressed
  while(1) {    
    if(SW1_press()){
      freq = PRESET3; //12MHz
      PLL_Init(freq);
      GPTMCTL_0 &= ~(0x1);
      GPTMTAILR_0 = 0xB71B00;
      GPTMCTL_0 |= 0x1; 
    } else if (SW2_press()){
      freq = PRESET1; //120MHz
      PLL_Init(freq);
      GPTMCTL_0 &= ~(0x1);
      GPTMTAILR_0 = 0x7270E00;
      GPTMCTL_0 |= 0x1; 
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
    ADCISC |= 0x8;
  // 4.2: Save the ADC value to global variable ADC_value
    ADC_value = ADCSSFIFO3 & 0xFFF;
    float temperature = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    printf("%f\n", temperature);
}

unsigned long SW1_press()
{ return !(GPIODATA_J & 0x1); }

unsigned long SW2_press()
{ return !(GPIODATA_J & 0x2); }