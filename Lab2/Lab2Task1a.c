#include <stdint.h>
#include "lab2a.h"

//Initializes all the values for the timer.
void init_timer(void)
{
  RCGCTIMER      =  0x01; 
  GPTMCTL_0     &=  0x00; //disables timer.
  GPTMCFG_0      =  0x00; //selects 32-bit timer.
  GPTMTAMR_0     =  0x02; //TAMR in periodic mode.
  GPTMTAMR_0    &= ~(0x10);//TACDIR count down to 0.
  GPTMTAILR_0    =  0x00F42400; //16,000,000 value for 1Hz.  
  GPTMCTL_0     |=  0x01; //enables timer
}

//Initializes all the directions and digital ports for lights.
void init_lights(void)
{
  RCGCGPIO  |= 0x1020;    //Enables Port F.
  GPIODIR_F |= 0x11;     //Set PF0 and PF4 to outputs
  GPIODIR_N |= 0x03;     //Set PN0 and PN1 to outputs
  GPIODEN_F |= 0x11;     //Set PF0 and PF4 to digital port
  GPIODEN_N |= 0x03;     //Set PN0 and PN1 to digital port
}

//Polls by checking when bit reaches 0 and reseting the flag when so.
int poll(void)
{
  while (1) {
  if (GPTMRIS_0 & 0x1 == 0x1) {
    GPTMICR_0 |= 0x1;
    return 1;
  }
  else {
    return 0;
    }
  }
}

//Blinks lights F0, F4, N0, and N1 in sequential pattern using polling.
void blinking(void) {
  GPIODATA_N = 0x00;
  GPIODATA_F = 0x01;
    while(!poll());
  GPIODATA_F = 0x10;
    while(!poll());
  GPIODATA_F = 0x0;
  GPIODATA_N = 0x01;
    while(!poll());
  GPIODATA_N = 0x02;
    while(!poll());
}

//Runs the code.
int main(void)
{
  init_timer();
  init_lights();
  while (1){
     blinking();
  }
  return 0;  
}

