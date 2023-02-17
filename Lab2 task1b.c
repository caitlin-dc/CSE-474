#include <stdint.h> 
#include "task1b_header.h"

unsigned long power_button(void); 
unsigned long ped_button(void);

void LED_on_green(void); 
void LED_off_green(void);
void LED_on_yellow(void);
void LED_off_yellow(void);
void LED_on_red(void);
void LED_off_red(void);
void delay();

enum Traffic_States {GO, GO_OFF_TRANSITION, WARN, WARNING_TRANSITION, WARNING_OFF_TRANSITION, OFF, STOP, STOP_TRANSITION, STOP_OFF_TRANSITION} Traffic_States;

int light_cycle = 0;
int power_cycle = 0;
int walk_cycle = 0; 

void delay () {
   for (int i = 0; i < 1000000; i++);
}


  
void Traffic_LogicRedo() {
  switch(Traffic_States){
    case OFF:
      // power button being pressed
      if(power_button()){
        Traffic_States = STOP_TRANSITION;
        power_cycle = 0;
      }
      // power button not being pressed
      else{
        Traffic_States = OFF;
        power_cycle = 0;
      }
      break;
     
    case STOP_TRANSITION:
      // power button being pressed but 2 seconds has NOT elapsed
      if (power_button() && power_cycle < 2) {
        power_cycle++;
      }
      // power button being pressed and 2 seconds HAS elapsed, turn on system
      else if (power_button() && power_cycle >= 2) {
        Traffic_States = STOP;
        light_cycle = 0;
        power_cycle = 0;
        walk_cycle = 0;
      }
      // power button no longer being pressed and 2 seconds has NOT elapsed
      else {
        Traffic_States = OFF;
        power_cycle = 0;
      }
      break;
      
    case STOP:
      // turn off button being pressed, go to off transition state
      if (power_button()) {
        Traffic_States = STOP_OFF_TRANSITION;
        power_cycle = 0;
      }
      // 5 seconds has NOT elapsed, so continue counting
      else if (light_cycle < 5) {
        Traffic_States = STOP;
        light_cycle++;
      }
      // 5 seconds HAS elapsed, go to GO state
      else {
        Traffic_States = GO;
        light_cycle = 0;
      }
      break;
      
     case STOP_OFF_TRANSITION:
      // power button being pressed but 2 seconds has NOT elapsed
      if (power_button() && power_cycle < 2) {
        power_cycle++;
        light_cycle++;
      }
      // power button being pressed and 2 seconds HAS elapsed
      else if (power_button() && power_cycle >= 2) {
        power_cycle = 0;
        light_cycle = 0;
        walk_cycle = 0;
        Traffic_States = OFF;
      }
      // power button no longer being pressed and 2 seconds has NOT elapsed
      else {
        Traffic_States = STOP;
        light_cycle++;
        power_cycle = 0;
      }
      break;
      
    case GO:
      // turn off button being pressed, go to off transition state
      if (power_button()) {
        Traffic_States = GO_OFF_TRANSITION;
        power_cycle = 0;
      }
      // pedestrian button being pressed, go to warning transition state
      else if (ped_button()) {
        Traffic_States = WARNING_TRANSITION;
        walk_cycle = 0;
      }
      // 5 seconds has NOT elapsed, so continue counting 
      else if (light_cycle < 5) {
        Traffic_States = GO;
        light_cycle++;
      }
      // 5 seconds HAS elapsed, go to STOP state
      else {
        Traffic_States = STOP;
        light_cycle = 0;
      }
      break;
      
     case GO_OFF_TRANSITION:
      // power button being pressed but 2 seconds has NOT elapsed
      if (power_button() && power_cycle < 2) {
        power_cycle++;
        light_cycle++;
      }
      // power button being pressed and 2 seconds HAS elapsed
      else if (power_button() && power_cycle >= 2) {
        power_cycle = 0;
        light_cycle = 0;
        walk_cycle = 0;
        Traffic_States = OFF;
      }
      // power button no longer being pressed and 2 seconds has NOT elapsed
      else {
        Traffic_States = GO;
        light_cycle++;
        power_cycle = 0;
      }
      break;
      
    case WARNING_TRANSITION:
      // pedestrian button being pressed and 2 seconds has NOT elapsed
      if (ped_button() && walk_cycle < 2) {
        walk_cycle++;
        light_cycle++;
      }
      // pedestrian button being pressed and 2 seconds HAS elapsed
      else if (ped_button() && walk_cycle >= 2) {
        walk_cycle = 0;
        light_cycle = 0;
        power_cycle = 0;
        Traffic_States = WARN;
      }
      // pedestrian button no longer being pressed and 2 seconds has NOT elapsed
      else {
        Traffic_States = GO;
        light_cycle++;
        walk_cycle = 0;
      }
      break;
      
  case WARN:
     // turn off button being pressed, go to off transition state
     if (power_button()) {
       Traffic_States = WARNING_OFF_TRANSITION;
       power_cycle = 0;
     }
     // 5 seconds has NOT elapsed, so continue counting
     else if (light_cycle < 5) {
       light_cycle++;
       Traffic_States = WARN;
     }
     // 5 seconds HAS elapsed in WARN, go to STOP
     else {
       light_cycle = 0;
       Traffic_States = STOP;
     }
     break;
  
  case WARNING_OFF_TRANSITION:
    // power button being pressed but 2 seconds has NOT elapsed
    if (power_button() && power_cycle < 2) {
      power_cycle++;
      light_cycle++;
    }
    // power button being pressed and 2 seconds HAS elapsed
    else if (power_button() && power_cycle >= 2) {
      power_cycle = 0;
      light_cycle = 0;
      walk_cycle = 0;
      Traffic_States = OFF;
    }
    // power button no longer being pressed and 2 seconds has NOT elapsed
    else {
      light_cycle++;
      power_cycle = 0;
      Traffic_States = WARN;
    }
    break;
  }

  switch(Traffic_States){
    case OFF:
      LED_off_green();
      LED_off_red();
      LED_off_yellow();
      break;
  
    case STOP:
      LED_off_yellow();
      LED_off_green();
      LED_on_red();
      break;
      
    case WARN:
      LED_off_red();
      LED_off_green();
      LED_on_yellow();
      break;
      
    case GO:
      LED_off_yellow();
      LED_off_red();
      LED_on_green();
      break;
  }
}    
  
void LED_init(void) 
{ 
    volatile unsigned short delay = 0; 
    //RCGCGPIO |= 0x04;              // activate clock for Port C 
    //delay++; 
    //delay++; 
 
    //GPIOAMSEL_C &= ~0x10;          // disable analog function of PC4 
    //GPIODIR_C |= 0x10;             // set PC4 to output 
    //GPIOAFSEL_C &= ~0x10;          // set PC4 regular port function 
    //GPIODEN_C |= 0x10;             // enable digital output on PC4 
    
    // make one for PL2 - PL4
    RCGCGPIO |= 0x400; //activate clock for Port L correct for sure
    delay++;
    delay++;
      
    GPIOAMSEL_L &= ~0x1C;
    GPIODIR_L |= 0x1C;
    GPIOAFSEL_L &= ~0x1C;
    GPIODEN_L |= 0x1C;
    
      
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
 
unsigned long power_button(void) 
{ 
  return (GPIODATA_L & 0x2); // 0x2 (pressed) or 0 (not pressed) 
} 

unsigned long ped_button(void) 
{ 
  return (GPIODATA_L & 0x1);// 0x1 (pressed) or 0 (not pressed) 
} 

//initialize timer 
void timer_init (void) {
  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x01; //enable timer bit
  delay++;
  delay++;
  
  GPTMCTL_TIMER0 &= 0x00; //disable timer
  GPTMCFG_TIMER0 &= 0x00; //32 bit mode
  GPTMTAMR_TIMER0 |= 0x02; //periodic timer and countdown mode
  GPTMTAILR_TIMER0 = 0xF42400; //1Hz
  GPTMCTL_TIMER0 |= 0x01; //enable timer
}
       
int main() 
{ 
  LED_init();
  extern_switch_init();
  timer_init();
  Traffic_States = OFF;
  while(1){
    Traffic_LogicRedo();
    while ((GPTMRIS_TIMER0 & 0x1) != 0x1) {}
    GPTMICR_TIMER0 |= 0x1;
  }
  
} 

