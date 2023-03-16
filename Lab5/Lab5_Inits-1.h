//_____________________ Lab5_Inits.h _____________________
/*
 * Caitlin DeShazo-Couchot  and Ze Xu
 * Student ID: 2039775
 * March 9, 2023
 * EE/CSE 474: Lab5 initializations header. Added PWM to initializations
 */

// NOTE: All necessary functions for Task 1a have been declared in
// this header file, and thus you should not modify it for task 1a.
// However, you may modify it if you want to reuse it for other tasks.

#ifndef _Lab5_Inits_H_
#define _Lab5_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes the 4 onboard LEDs.
void LED_Init(void);

//Initializes SWITCHES
void SWITCHES_Init(void);

//Initializes PWM
void PWM_Init(void);

#endif  // _Lab5_Inits_H_