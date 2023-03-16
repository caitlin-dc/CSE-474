//_____________________ Lab4_Task1a.c _____________________
/*
 * Caitlin DeShazo-Couchot and Ze Xu
 * Student ID: 2039775
 * March 2, 2023
 * EE/CSE 474: Lab 4 Task 1a Main Function
 */
#include <stdint.h>
#include "SSD2119_Display.h"
#include "tm4c1294ncpdt.h"

//Fills the screen with the color choice of red.
 int main(){
  
  LCD_Init();
  LCD_ColorFill(Color4[12]);
  while(1);
  return 0;
 }