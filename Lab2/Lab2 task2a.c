#include <stdint.h>
#include <stdio.h>
#include "task2a.h"

//Initializes all the values for the timer.
int count = 0;

void init_timer()
{
  RCGCTIMER     |=  0x1; 
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  GPTMCTL_0     &=  ~(0x1); //disables timer.
  GPTMCFG_0     =  0x00; //selects 32-bit timer.
  //GPTMTAMR_0    &= 0x0; //configure tamr bit
  GPTMTAMR_0    |=  0x2; //TAMR in periodic mode.
  GPTMTAMR_0    &= ~(0x10); //TACDIR count down to 0.
  GPTMTAILR_0   =  0xF42400; //16,000,000 value for 1Hz.  
  GPTMIMR_0 |= 0x1; //enable interrupt ( we want at position 19)
  INTERRUPT_EN0 |= 0x80000; //pos 19
  GPTMCTL_0     |=  0x1; //enables timer
  GPTMICR_0     |=  0x1; // make sure flag is clear

}

//Initializes all the directions and digital ports for lights.
void init_lights()
{
  RCGCGPIO |= 0x1020;    //Enables Port F, N.
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  GPIODIR_F |= 0x11;     //Set PF0 and PF4 to outputs
  GPIODIR_N |= 0x03;     //Set PN0 and PN1 to outputs
  GPIODEN_F |= 0x11;     //Set PF0 and PF4 to digital port
  GPIODEN_N |= 0x03;     //Set PN0 and PN1 to digital port
}


//Blinks lights F0, F4, N0, and N1 in sequential pattern using polling.
void timer0_handler() {
  printf("in handler");
  GPTMICR_0 |= 0x01; //reset timer
  count++;
  if(count == 1){
    GPIODATA_F = 0x00;
    GPIODATA_N = 0x01;
  }
  else if (count == 2){
    GPIODATA_F = 0x00;
    GPIODATA_N = 0x02;
    
  } else if (count == 3){
    GPIODATA_N = 0x00;
    GPIODATA_F = 0x01;
  } else if ( count == 4){
    GPIODATA_N = 0x00;
    GPIODATA_F = 0x10;
  }else{
    count = 0;
  }
}
  



//Runs the code.
int main(void)
{
  init_timer();
  init_lights();
  while (1){
    //printf("%d\n", GPTMRIS_0 & 0x1);
  }
  return 0;  
}
