//_____________________ Lab3_Inits_Task1a_2b.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * February 14, 2023
 * EE/CSE 474: Lab3 Inits code for 1a and 2b
 */

#include "PLL_Header.h"
#include "Lab3_Inits.h"

#include "lab3.h"
  
//Sets up the Phase Locked Loop
int PLL_Init(enum frequency freq) {
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

//Initialize the 4 on board LEDs by initializing the corresponding
void LED_Init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO_0 |= 0x1020;
  delay++;
  delay++;
  
  GPIODIR_F = 0x11;   // Set PF to output 
  GPIODEN_F = 0x11;   // Set PF to digital port 
    
  GPIODIR_N = 0x3;   // Set PN to output 
  GPIODEN_N = 0x3;   // Set PN to digital port 
}

//Initialize ADC0 SS3.
void ADCReadPot_Init(void) {
  volatile unsigned short delay = 0;
  
  //Enable the ADC0 clock
  RCGCADC_0 = 0x1; //Enables ADC0
  
  //Delay for RCGCADC 3 times (Refer to page 1073)
  delay++;
  delay++;
  delay++;
  
  //Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; 
  
  //Wait for the PLL to lock
  while (PLLSTAT != 0x1);
  
  //Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC_0 |= 0x1;
  
  //Enable clock to the appropriate GPIO Modules
  RCGCGPIO_0 |= 0x10;
  
  //Delay for RCGCGPIO
  delay++;
  delay++;
    
  //Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_0 |= 0x8;
  
  //Clear the GPIODEN bits for the ADC input pins
  GPIODEN_0 &= ~0x8;

  //Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_0 |= 0x8;
  
  //Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~0x8;

  //Select timer as the trigger for SS3
  ADCACTSS_0 |= 0x5000;
  
  //Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSEMUX3 &= ~0x1;
  ADCSSMUX3 &= ~0xF; //Pin AIN1 -- PE2. Analong-to-digital converter input 1

  //Configure ADCSSCTL3 register
  ADCSSCTL3_0 |= 0x6;//0b0110
  
  //Set the SS3 interrupt mask
  ADCIM_0 |= 0x8;
  
  //Set the corresponding bit for ADC0 SS3 in NVIC
  NVIC_EN0 |= 0x20000;
      
  //Enable ADC0 SS3
  ADCACTSS_0 |= 0x08;
}

//Initialize Timer0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void) {
  volatile unsigned short delay = 0;

  RCGCTIMER_0 |= 0x1;
  delay++;
  delay++;
  GPTMCTL_0    |= 0x0;       //Disable Timer 0
  GPTMCFG_0    |=  0x0;      //Configure 32 bit mode.
  GPTMTAMR_0   |= 0x2;       //Select periodic mode.
  GPTMTAMR_0   &= ~0x10;     //Count down
  GPTMTAILR_0   = 60000000;  //60,000,000
  GPTMCTL_0    |= 0x20;
  GPTMADCDEV_0 |= 0x1;
  GPTMICR_0    |= 0x1;
  GPTMCTL_0    |= 0x1;       //Enable Timer 0
}