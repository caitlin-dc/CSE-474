//_____________________ Lab4_Task2b.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * March 2, 2023
 * EE/CSE 474: Lab4 Task2b Main Code
 */

#include "FreeRTOS.h"
#include "task.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "PLL_Header.h"
#include "tm4c1294ncpdt.h"
#include "Lab4_Inits.h"
#include "Lab4_Header.h"
#include "Lab4_Task1b.h"
#include "Lab3_Inits.h"



//States
  enum Traffic_States {go, stop, warn, off} Traffic_States;

// Global variables are flags
int pedestrian_status = 0;
int onoff_status = 0;

//PROTOTYPE

// Task function that checks the state of the virtual pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the virtual pedestrian button for 2 seconds,
// it will set the global flag indicating the virtual pedestrian button
// has been pressed.
void Pedestrian(void *p);
  
// Task function that checks the state of the virtual onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the virtual traffic light has been
// lighting on. It will update the state of the traffic light system
// every 5 seconds or once there's virtual button input.
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);

LED_on_red(void)
LED_off_red(void)
LED_on_green(void)
LED_off_green(void)
LED_on_yellow(void)
LED_off_yellow(void)
unsigned long power_button(void) 
unsigned long ped_button(void) 


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}



// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by initialize the display and touch
  // functionalities of your SSD2119 touch display assembly. You may
  // also want to initialize (draw) your virtual buttons here.
  // Moreover, initialize the PLL to set the system clock to 60 MHz.
  LCD_Init();
  Touch_Init();
  PLL_Init(PRESET2);
  
  //Create leds and sw on lcd
  LCD_DrawFilledRect(0, 190, 50, 50, Color4[9]);
  LCD_DrawFilledRect(180, 190, 50, 50, Color4[10]);
  LCD_SetCursor(10, 215);
  LCD_Printf("Power");
  LCD_SetCursor(200, 215);
  LCD_Printf("Ped");


  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL, 2 , NULL);
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, 1 , NULL);
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, 0 , NULL);

  // Start the scheduler. This should not return.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}
}

void StartStop(void *p) {
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  curr_onoff_tick_time = xTaskGetTickCount();

  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
  while (1) {
    curr_onoff_tick_time = xTaskGetTickCount();

    // Check whether the virtual button is pressed.
    //
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if (power_button()) {
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 2000) {
        // Set the global flag
        onoff_status = 1;
        // Clear the timer
        prev_onoff_tick_time = curr_onoff_tick_time;
      }
      else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      onoff_status = 0;
      // Clear the timer
      prev_onoff_tick_time = curr_onoff_tick_time;      
    }

    vTaskDelay(1);
  }
}

void Pedestrian(void *p) {
  static int curr_ped_tick_time = 0;
  static int prev_ped_tick_time = 0;

  // Complete the implementation of this task function.
  // It checks whether the virtual pedestrian button has been pressed
  // for 2 seconds and update the global flag accordingly.
  while (1) {
    curr_ped_tick_time = xTaskGetTickCount();
    if(ped_button()){
      if (curr_ped_tick_time - prev_ped_tick_time >= 2000)
      {                                          // switch pressed for 2 seconds
        pedestrian_status = 1;                   // Set the global flag
        prev_ped_tick_time = curr_ped_tick_time; // Clear the timer
      }
      else
      {
        pedestrian_status = 0; // Clear the global flag
      }
    }
    else
    {
      pedestrian_status = 0;                   // Clear the global flag
      prev_ped_tick_time = curr_ped_tick_time; // Clear the timer
    }
      
    vTaskDelay(1);
  }
}

void Control(void *p) {
  static int curr_light_tick_time = 0;
  static int prev_light_tick_time = 0;


  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_light_tick_time = xTaskGetTickCount();

    // If the one of the virtual lights been lighting up for 5 or more
    // seconds, or if any of the virtual button flags has been set, switch
    // to the corresponding next state and reset the light tick.
    if (curr_light_tick_time - prev_light_tick_time >= 5000 || (onoff_status) || (pedestrian_status)) {  // replace this condition checking with something else
      // Reset the light tick
        prev_light_tick_time = curr_light_tick_time;
      // Switch to next state
        FSM();
        
    } 

    vTaskDelay(1);
  }
}

void FSM(void) {
  // STEP 6
  //
  // Add your FSM implementation here.
  // This function will be called by the control task function.
  switch(Traffic_States){
    case off:
      if(onoff_status){
        Traffic_States = stop;
      }
     break;
     
    case stop:
      if(onoff_status) {
        Traffic_States = off;
      } else {
        Traffic_States = go;
      }
    break;
    
    case go:
      if(onoff_status){
        Traffic_States = off;
      } else if (pedestrian_status){
        Traffic_States = warn;
      } else {
        Traffic_States = stop;
      }
    break;
    
  case warn:
    if(onoff_status) {
      Traffic_States = off;
    } else {
      Traffic_States = stop;
    } 
    break;
  }
  
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
      
    case warn:
      LED_off_red();
      LED_off_green();
      LED_on_yellow();
      break;
      
    case go:
      LED_off_yellow();
      LED_off_red();
      LED_on_green();
      break;
  }

}

void LED_on_red(void) 
{ 
    //GPIODATA_L |= 0x4; 
    LCD_DrawFilledCircle(50,  100, 20, Color4[12]);

} 
 
// turn off LED connected to PL2
void LED_off_red(void) 
{ 
    //GPIODATA_L &= ~0x4; 
    LCD_DrawFilledCircle(50,  100, 20, Color4[0]);

}

// turn on LED connected to PL3 
void LED_on_yellow(void) 
{ 
    //GPIODATA_L |= 0x8; 
    LCD_DrawFilledCircle(150, 100, 20, Color4[14]);

} 
 
// turn off LED connected to PL3
void LED_off_yellow(void)  
{ 
    //GPIODATA_L &= ~0x8; 
    LCD_DrawFilledCircle(150, 100, 20, Color4[0]);

}

// turn on LED connected to PL4
void LED_on_green(void) 
{ 
    //GPIODATA_L |= 0x10;
    LCD_DrawFilledCircle(250, 100, 20, Color4[10]);

} 
 
// turn off LED connected to PL4 
void LED_off_green(void)  
{ 
    //GPIODATA_L &= ~0x10; 
    LCD_DrawFilledCircle(250, 100, 20, Color4[0]);

}

//Checks if power is on or off
unsigned long power_button(void) 
{ 
  //return (GPIODATA_L & 0x2); // 0x2 (pressed) or 0 (not pressed) 
  unsigned long boolean = (((float)Touch_ReadX() > 650)&& ((float)Touch_ReadX() < 960) && ((float)Touch_ReadY() > 600) && ((float)Touch_ReadY() < 850));
  //printf("%d", boolean);
  return boolean;
} 
//Checks if pedestrian button has been pressed or not
unsigned long ped_button(void) 
{ 
  //return (GPIODATA_L & 0x1);// 0x1 (pressed) or 0 (not pressed) 
  return (((float)Touch_ReadX() > 1500)&& ((float)Touch_ReadX() < 1750) && ((float)Touch_ReadY() > 600) && ((float)Touch_ReadY() < 850));
} 
