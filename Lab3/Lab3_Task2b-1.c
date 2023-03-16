//_____________________ Lab3_Task2b.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * February 14, 2023
 * EE/CSE 474: Lab3 Task2b main function
 */

#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"
#include "PLL_HEADER.h"

#include "Lab3.h"

//Sets up the Universal Asynchronous Receiver/Transmitter (UART)
void UART_Init();

int main() {
  enum frequency freq = PRESET2; // Select system clock frequency to 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  UART_Init();
  while(1) {
    char c;
    while (!(UARTFR_2 & 0x40));
    c = UARTDR_2;
    UARTDR_2 = c;
    while(!(UARTFR_2 & 0x80));
  }
  return 0;
}

void UART_Init()
{
  volatile unsigned short delay = 0;
  
  //1.1. Enable the UART module using RCGCUART register.
  RCGCUART |= 0x4; //enable UART0
  delay++;
  delay++;
  delay++;
  
  //1.2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register.
  RCGCGPIO_0  |= 0x1; //enable Port A Clock via bit 0 in RCGCGPIO
  delay++;
  delay++;
  delay++;
  
  //1.3. Set the GPIOAFSEL bits for the appropriate pins (A0 and A1).
  GPIOAFSEL_A |= 0xC0; //Port P6 and P7. 
    
  // Addition
  GPIODEN_A |= 0xC0;
  
  // UART pins have a 2 mA drive
  GPIODR2R_A |= 0xC0;
  
  //1.4. Configure the GPIO current level and/or slew rate as specified.
  GPIOSLR_A |= 0xC0;
  
  //1.5. Configure the PMCn fields in GPIOPCTL register to assign the UART signals.
  //PAGE 787 or PAGE 1808, Table 26-5
  GPIOPCTL_A |= 0x11000000; //P6/P7
    
  //1.6. Disable the UART by clearing the UARTEN bit in the UARTCTL reigster.
  UARTCTL_2  &= ~0x1; //Clear bit 0 to clear UARTEN
  
  //1.7. Write the integer portion of the BRD to the UARTIBRD register.
  UARTIBRD_2  = 0x68;  //(16,000,000)/(16 * 9,600)
  
  //1.8. Write the fractional portion of the BRD to the UARTFBRD register.
  UARTFBRD_2  = 0xB;   //int((.166667) * 64 + 0.5)    
  
  
  //1.9. Write the desired serial parameters to the UARTLCRH register.
  UARTLCRH_2 |= 0x60;
  
  //1.10. Configure the UART Clock source by writing to the UARTCC register.
  UARTCC_2   |= 0x5; //Alternative Clock
    
  //1.11. Optional DMA: Not needed for Lab3.
    
  //1.12. Enable the UART by setting the UARTEN bit in teh UARTCTL register.
  UARTCTL_2  |= 0x1; // 0x1
}