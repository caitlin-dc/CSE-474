/* 
 * Ze Xu (Take ownership of your code by naming all files) 
 * 1879419 
 * 2/2/23
 * Task2c of Lab2 was to make a Traffic Light using timer interrupts
 */ 
#include <stdint.h> 
#include "task2_header.h"

//FUNCTION PROTOTYPES;

//power button to turn on system
unsigned long power_button(void);

//turn on pedestrian button
unsigned long ped_button(void);

//turn on green led
void LED_on_green(void);
//turn off green led
void LED_off_green(void);

// turn on yellow led
void LED_on_yellow(void);
//turn off yellow led
void LED_off_yellow(void);

//turn on red led
void LED_on_red(void);
//turn off red led
void LED_off_red(void);

//initialize LED
void LED_init(void)

//enumumerate the states
enum Traffic_States {go, warn, off, stop} Traffic_States;

//global variables for counting
int power = 0;
int ped = 0;

int main() 
{ 
  LED_init();
  extern_switch_init();
  TimerInit();
  Traffic_States = off; //sets initial state to off
  //calls upon trafficlight FSM
  while(1){
    Traffic_LogicRedo();
  }
  
} 

//transitions between each state
void Traffic_LogicRedo(int power, int ped) {
  switch(Traffic_States){
    case off: //off state
      if(power_button()){
        Traffic_States = stop;
      } else{
        Traffic_States = off;
      }
     break;
     
    case stop: //stop state
      if(power_button()) {
        Traffic_States = off;
      } else {
          Traffic_States = go;
      }
    break;
    
    case go: //go state
      if(power_button()){
        Traffic_States = off;
      } else if (ped_button()){
        Traffic_States = warn;
      } else {
        Traffic_States = stop;
      }
    break;
    
  case warn: //warn state
    if(power_button()) {
      Traffic_States = off;
    } else {
      Traffic_States = stop;
    } 
    break;
  }
  
  //state actions for each state
  switch(Traffic_States){
    case off:
      LED_off_green();
      LED_off_red();
      LED_off_yellow();
      break;
  
    case stop:
      LED_off_yellow();
      LED_off_green();
      LED_on_red();
      break;
      
    case go:
      LED_off_yellow();
      LED_off_red();
      LED_on_green();
    break;
    
    case warn:
      LED_off_green();
      LED_off_red();
      LED_on_yellow();
    break;
  }
}  
  
  
  


//initialize LED
void LED_init(void) 
{ 
    volatile unsigned short delay = 0;   
    // make one for PL2 - PL4
    RCGCGPIO |= 0x400; //activate clock for Port L correct for sure
    delay++;
    delay++;
      
    GPIOAMSEL_L &= ~0x1C; //diable analog function from PL2-4
    GPIODIR_L |= 0x1C; //SET PL2-4 to output
    GPIOAFSEL_L &= ~0x1C; //SET PL2-4 regular port function
    GPIODEN_L |= 0x1C; //enable digital output on PL2-4
    
      
} 
 
// turn on LED connected to PL2 
void LED_on_red(void) 
{ 
    GPIODATA_L |= 0x4; 
} 
 
// turn off LED connected to PL2
void LED_off_red(void) 
{ 
    GPIODATA_L &= ~0x4; 
}

// turn on LED connected to PL3 
void LED_on_yellow(void) 
{ 
    GPIODATA_L |= 0x8; 
} 
 
// turn off LED connected to PL3
void LED_off_yellow(void)  
{ 
    GPIODATA_L &= ~0x8; 
}

// turn on LED connected to PL4
void LED_on_green(void) 
{ 
    GPIODATA_L |= 0x10; 
} 
 
// turn off LED connected to PL4 
void LED_off_green(void)  
{ 
    GPIODATA_L &= ~0x10; 
}

//initialize switch
void extern_switch_init(void)  
{ 
   //PL0-1
    volatile unsigned short delay = 0; 
    RCGCGPIO |= 0x400; //activate clock for Port L
    delay++; 
    delay++; 
    GPIOAMSEL_L &= ~0x3;  // Disable PL0-1 analog function 
    GPIOAFSEL_L &= ~0x3;  // Select PL0-1 regular port function 
    GPIODIR_L &= ~0x3;    // Set PL0-1 to input direction 
    GPIODEN_L |= 0x3;     // Enable PL0-1 digital function 
} 
 
//turn on power
unsigned long power_button(void) 
{ 
  return (GPIODATA_L & 0x2); // 0x2 (pressed) or 0 (not pressed) 
} 

//turn on pedestrian button
unsigned long ped_button(void) 
{ 
  return (GPIODATA_L & 0x1);// 0x1 (pressed) or 0 (not pressed) 
} 


//2 sec timer 
void Timer0_Handler(){
  RCGCTIMER     |=  0x1; 
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  GPTMCTL_TIMER0 &= 0x00; //disable timer
  GPTMCFG_TIMER0 &= 0x00; //32 bit mode
  GPTMTAMR_TIMER0 |= 0x02; //periodic timer and countdown mode
  GPTMTAILR_TIMER0 = 0x1E84800; //2Hz
  GPTMCTL_TIMER0 |= 0x01; //enable timer
}

//5sec timer
void Timer1_Handler(){
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  GPTMCTL_TIMER1 &= 0x00; //disable timer
  GPTMCFG_TIMER1 &= 0x00; //32 bit mode
  GPTMTAMR_TIMER1 |= 0x02; //periodic timer and countdown mode
  GPTMTAILR_TIMER1 = 0x4C4B400; //1Hz
  GPTMCTL_TIMER1 |= 0x01; //enable timer
}


