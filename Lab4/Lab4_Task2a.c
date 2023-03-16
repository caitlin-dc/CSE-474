//_____________________ Lab4_Task2a.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * March 2, 2023
 * EE/CSE 474: Lab4 Task2a Main Code
 */
#include <stdint.h> 
#include <stdio.h>
#include "Task2aHeader.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "tm4c1294ncpdt.h"
#include "Task1b.h"
#include "Lab3Inits.h"



uint32_t ADC_value;
//Prototype
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

int main() 
{ 
  timer_init();
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LCD_Init();
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  Touch_Init();
  Traffic_States = OFF;
  
  //Create leds and sw on lcd
  LCD_DrawFilledRect(0, 190, 50, 50, Color4[9]);
  LCD_DrawFilledRect(180, 190, 50, 50, Color4[10]);
  LCD_SetCursor(10, 215);
  LCD_Printf("Power");
  LCD_SetCursor(200, 215);
  LCD_Printf("Ped");

  while(1){
    Traffic_LogicRedo();
    while ((GPTMRIS_TIMER0 & 0x1) != 0x1) {}
    GPTMICR_TIMER0 |= 0x1;
  }
  
} 
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
  
// turn on red circle connected to LCD display 
void LED_on_red(void) 
{ 
    LCD_DrawFilledCircle(50,  100, 20, Color4[12]);

} 
 
// turn off red circle connected to LCD display
void LED_off_red(void) 
{ 
    LCD_DrawFilledCircle(50,  100, 20, Color4[0]);

}

// turn on yellow circle connected to LCD display
void LED_on_yellow(void) 
{ 
    LCD_DrawFilledCircle(150, 100, 20, Color4[14]);

} 
 
// turn off yellow circle connected to LCD display
void LED_off_yellow(void)  
{ 
    LCD_DrawFilledCircle(150, 100, 20, Color4[0]);

}

// turn on green circle connected to LCD display
void LED_on_green(void) 
{ 
    LCD_DrawFilledCircle(250, 100, 20, Color4[10]);

} 
 
// turn off green circle connected to LCD display 
void LED_off_green(void)  
{ 
    LCD_DrawFilledCircle(250, 100, 20, Color4[0]);

}
 
unsigned long power_button(void) 
{ 
  unsigned long boolean = (((float)Touch_ReadX() > 650)&& ((float)Touch_ReadX() < 960) && ((float)Touch_ReadY() > 600) && ((float)Touch_ReadY() < 850));
  return boolean;
} 

unsigned long ped_button(void) 
{ 
  return (((float)Touch_ReadX() > 1500)&& ((float)Touch_ReadX() < 1750) && ((float)Touch_ReadY() > 600) && ((float)Touch_ReadY() < 850));
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

void ADC0SS3_Handler(void)
{                           
  ADCISC |= 0x8;          // clear the ADC0 interrupt flag
  ADC_value = ADCSSFIFO3 & 0xFFF;
    
}
