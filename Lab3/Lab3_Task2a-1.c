//_____________________ Lab3_Task2a.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * February 14, 2023
 * EE/CSE 474: Lab3 Task2a main function
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "task2ainits.h"

#include "lab3.h"

uint32_t ADC_value;     //Stores ADC Value
int TempUpdated = 0;    //Stores updated temperature value

//Sets up the Analog-to-Digital Module 3
void ADC0SS3_Handler(void)

int main(void) {
  enum frequency freq = PRESET2;// Select system clock frequency to 60 MHz
  PLL_Init(freq);               // Set system clock frequency to 60 MHz
  SWITCHES_Init();              // Initialize the 2 on-board SWs (GPIO)
  ADCReadPot_Init();            // Initialize ADC0 to read from temperature sensor
  TimerADCTriger_Init();        // Initialize Timer0A to trigger ADC0
  UART_Init();                  // Initialize UART0 to communicate with computer
  float temperature;
  
  //array big enough to store chars
  //for loop goes through the entire array so it can get all the values
  //sprint allows us to see this on putty
  while (1) {
    TempUpdated = 0;
    char str[10];   // store output make sure its big enough
    temperature = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    printf("%.2f\n", temperature); //see in terminal
    sprintf(str, "%.2f\n", temperature); //see on putty
    for (int i = 0; i < 10; i++) {
      UARTDR_0 = str[i];
    }
    while (TempUpdated != 1);
  }
  return 0;
}

void ADC0SS3_Handler(void) {
   ADCISC |= 0x8; // clear the interrupt flag
   GPTMICR_0 |= 0x1; // clear timer interrupt flag
   ADC_value = ADCSSFIFO3 & 0xFFF; // save adc value to global variable
   TempUpdated = 1;
}


