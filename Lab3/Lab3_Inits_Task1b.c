//_____________________ Lab3_Inits_Task1b.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * February 14, 2023
 * EE/CSE 474: Lab3 Inits for task 1b main initializations
 */

#include "PLL_Header.h"
#include "Lab3Inits.h"
#include "lab3.h"

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void SWITCHES_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.

  // YOUR CODE HERE
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x100; // GPIO port J
   delay++;
   delay++; // add 2 cycle delay

   GPIODEN_J |= 0x3;  // enable PJ0, PJ1
   GPIODIR_J &= ~0x3; // set PJO, PJ1 as input
   GPIOPUR_J |= 0x3;  // attach pull-up resistor to PJ0, PJ1
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
    volatile unsigned short delay = 0;

  // 2.1: Enable the ADC0 clock
     RCGCADC |= 0x1;

  // 2.2: Delay for RCGCADC (Refer to page 1073)
     delay++;
     delay++;

  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
    ADCCC |= 0x1;
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
    RCGCGPIO |= 0x10;
  // 2.7: Delay for RCGCGPIO
    delay++;
    delay++;
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
    GPIOAFSEL_E |= 0x8;
  // 2.9: Clear the GPIODEN bits for the ADC input pins
    GPIODEN_E &= ~0x8;
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
    GPIOAMSEL_E |= 0x8;
  // 2.11: Disable sample sequencer 3 (SS3)
    ADCACTSS &= ~0x8;
  // 2.12: Select timer as the trigger for SS3
    ADCEMUX |= 0x5000;
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
    ADCSSEMUX3 &= ~0x1;
    ADCSSMUX3 &= ~0xF;
  // 2.14: Configure ADCSSCTL3 register
    ADCSSCTL3 |= 0xE; 

  // 2.15: Set the SS3 interrupt mask
    ADCIM |= 0x8;
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
    NVIC_EN0 |= 1<<17;
  // 2.17: Enable ADC0 SS3
    ADCACTSS |= 0x8; // 2.17: Enable ADC0 SS3


}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  // YOUR CODE HERE
    volatile unsigned short delay = 0;
    RCGCTIMER |= 0x1; // GPTM timer0
    delay++;
    delay++;

    GPTMCTL_0 |= 0x0;       // timer0 A is disabled
    GPTMCFG_0 |= 0x0;        // select the 32-bit timer configuration
    GPTMTAMR_0 |= 0x2;       // periodic timer mode
    GPTMTAMR_0 &= ~0x10;     // the timer counts down
    GPTMTAILR_0 = 60000000;  // load the value 60,000,000

    GPTMCTL_0 |= 0x20; // timer0 A ADC trigger is enabled
    GPTMADCEV_0 |= 0x1;      // timer0 A time out event ADC trigger is enabled

    GPTMICR_0 |= 0x1;        // clear timed out
    GPTMCTL_0 |= 0x1;        // timer0 A is enabled
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler