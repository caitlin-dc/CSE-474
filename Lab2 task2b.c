#include <stdint.h> 
#include "task2b.h" 
 

int count = 0;

void GPIOInit() {
  volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x100;  // Enable PortJ GPIO 
    RCGCGPIO |= 0x1000;  // Enable PortN GPIO 

    delay++;           // Delay 2 more cycles before access Timer registers 
    delay++;           // Refer to Page. 756 of Datasheet for info 
     
    GPIODIR_N = 0x3;   // Set PN to output 
    GPIODEN_N = 0x3;   // Set PN to digital port 
    GPIODIR_J = 0x0;   // Set PJ to output 
    GPIODEN_J = 0x3;   // Set PJ to digital port 
    GPIOPUR_J = 0x3;   // Set PJ to pull-up resistor 
    GPIOIM_J = 0x0;   /* mask interrupt */
    GPIOIS_J &= ~0x3;  /* make bit 1, 0 edge sensitive */
    GPIOIBE_J &= ~0x3; /* trigger is controlled by IEV */
    GPIOIEV_J &= ~0x3;   /* falling edge trigger */
    GPIOICR_J |= 0x3;  /* clear any prior interrupt */
    GPIOIM_J |= 0x3;   /* unmask interrupt */
}


void TimerInit(){
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
  GPTMIMR_0 |= 0x1; //enable interrupt ( we want at position 50)
  INTERRUPT_EN1 |= 0x00080000; //pos 50
  INTERRUPT_EN0 |= 0x80000;
  GPTMCTL_0     |=  0x1; //enables timer
// GPTMICR_0     |=  0x1; // make sure flag is clear
}


void portj_handler() {
  if(GPIODATA_J == 0x01){ //SW2
    GPTMCTL_0 = 0x1; //turn on timer
    GPIODATA_N &= !(0x01); //turn off led
  } else if (GPIODATA_J == 0x02){ //SW1
    GPTMCTL_0 = 0x0; //turn off timer
    GPIODATA_N |= 0x01; //turn on led
    GPIODATA_N &= ~(0x02);
  } 
  GPIOICR_J |= 0x03; //clear interrupt
}

//blink led in loop
void timer0_handler() {
  GPTMICR_0 |= 0x01;
  count++;
  if(count == 1){
    //turn on led
    GPIODATA_N |= 0x02;
  } 
  else if(count == 2){
    //turn off led
    GPIODATA_N &= !(0x02);
  }
  else{
    count = 0;
  }
}

int main(void) 
{ 
  GPIOInit();
  TimerInit();
  while(1){
    
  }
}