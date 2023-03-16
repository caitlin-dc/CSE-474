//_____________________ Lab4_Task1c.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * March 2, 2023
 * EE/CSE 474: Lab4 Task1c Main Code
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

//do touch on adc1
#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"
#include "Lab4_Task1b.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "PLL_Header.h"

//Prototype
void ADC0SS3_Handler(void)
unsigned long SW1_press()
unsigned long SW2_press()

//Constants
uint32_t ADC_value;
int frq;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  frq = 60;
  PLL_Init(freq);               // Set system clock frequency to 60 MHz
  LCD_Init();
  ADCReadPot_Init();            // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init();        // Initialize Timer0A to trigger ADC0
  SWITCHES_Init();
  Touch_Init();
  LCD_DrawFilledRect(0, 190, 50, 50, Color4[9]);
  LCD_DrawFilledRect(180, 190, 50, 50, Color4[10]);
  LCD_SetCursor(25, 215);
  LCD_Printf("SW1");
  LCD_SetCursor(205, 215);
  LCD_Printf("SW2");
  
  //Change freq based on which sw is pressed
  while(1) {    
    
    LCD_SetCursor(0,0);

    LCD_PrintFloat((float)Touch_ReadX());
    LCD_PrintChar('\n');
    LCD_PrintFloat((float)Touch_ReadY());
    LCD_PrintChar('\n');

    float temp_C = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    float temp_F = (float) temp_C * 9 / 5 + 32;
    LCD_PrintString("Current temperature is "); //remember to initialize evertyhing
    LCD_PrintFloat(temp_C);
    LCD_PrintString(" C, ");
    LCD_PrintFloat(temp_F);
    LCD_PrintString(" F. \n");
    LCD_PrintString("Current clock frequency is ");
    LCD_PrintInteger(frq);
    LCD_PrintString(" MHz.");
    if( ((float)Touch_ReadX() > 650)&& ((float)Touch_ReadX() < 960) && ((float)Touch_ReadY() > 600) && ((float)Touch_ReadY() < 850)){
      freq = PRESET3; //12mill
      frq = 12;
      PLL_Init(freq);
      GPTMCTL_0 &= ~(0x1);
      GPTMTAILR_0 = 0xB71B00;
      GPTMCTL_0 |= 0x1; 
    } else if ( ((float)Touch_ReadX() > 1500)&& ((float)Touch_ReadX() < 1750) && ((float)Touch_ReadY() > 600) && ((float)Touch_ReadY() < 850)){
      freq = PRESET1; //120mill
      frq = 120;
      PLL_Init(freq);
      GPTMCTL_0 &= ~(0x1);
      GPTMTAILR_0 = 0x7270E00;
      GPTMCTL_0 |= 0x1; 
    }
     LCD_SetCursor(0,0);
  }
  return 0;
}

//Handles the ADC Selective Select 3 as well as ISR
void ADC0SS3_Handler(void) {
    ADCISC |= 0x8;
    ADC_value = ADCSSFIFO3 & 0xFFF;
}

//SW1 Press
unsigned long SW1_press()
{ return !(GPIODATA_J & 0x1); }

//SW2 Press
unsigned long SW2_press()
{ return !(GPIODATA_J & 0x2); }

//960 750