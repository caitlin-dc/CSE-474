//_____________________ Lab5_Inits.h _____________________
/*
 * Caitlin DeShazo-Couchot  and Ze Xu
 * Student ID: 2039775
 * March 9, 2023
 * EE/CSE 474: Lab5 initializations for the code..
 * Reused from Lab3 the only changes was adding in the initializations for the PWM Init.
 */

#include "PLL_HEADER.h"
#include "Lab5_Inits.h"
#include "Lab5Header.h"

//Sets up the PLL.
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

//Sets up the LEDs.
void LED_Init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO_0 |= 0x1020;
  delay++;
  delay++;
  
  GPIODIR_F = 0x11;  // Set PF to output 
  GPIODEN_F = 0x11;  // Set PF to digital port 
    
  GPIODIR_N = 0x3;   // Set PN to output 
  GPIODEN_N = 0x3;   // Set PN to digital port 
}

//Sets up the switches.
void SWITCHES_Init(void) {
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x100; // GPIO port J
   delay++;
   delay++;           // add 2 cycle delay

   GPIODEN_J |= 0x3;  // enable PJ0, PJ1
   GPIODIR_J &= ~0x3; // set PJO, PJ1 as input
   GPIOPUR_J |= 0x3;  // attach pull-up resistor to PJ0, PJ1
}

//Sets up the PWM.
void PWM_Init(void) {
  volatile unsigned short delay = 0;
  RCGCPWM |= 0x1; // Enable PWM0 clock
  RCGCGPIO |= 0x20; //Enable Port F 
  delay++;
  delay++; // Delay for two clock cycles
  
  GPIOAFSEL_F |=  0x01;
  GPIOPCTL_F |=  0x6;
  GPIODIR_F |=  0x01;
  GPIODEN_F |= 0x01;

  
  PWMCC |= 0x100; 
  PWMCC |= 0x5;    
  
  PWM0CTL = 0x0;
  PWM0GENA |= 0x8C;  //countdown mode
  
  PWM0LOAD = 0xFFFF;
  
  PWM0CMPA = 0x63;
  PWM0CTL |= 0x1;               
 
  PWMENABLE |= 0x3;
   
}