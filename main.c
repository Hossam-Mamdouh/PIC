/*
 * File:   main.c
 * Author: Hossam-Mamdouh
 *
 * Created on May 11, 2022, 10:32 AM
 */

#include <xc.h>
#include "config.h"   // Header file for configuration of PIC
#include "LCD.h"      // Header file for the LCD
#include "Keypad.h"   // Header file for the Keypad

// Global Variables
int Number_1, Number_2, Result;
unsigned char Operation;

// Functions Prototypes
void Calculations (int Number_1, int Number_2, unsigned char Operation);

void main(void) 
{
    LCD_Init();       // Initialize the LCD.
    Keypad_Init();    // Initialize the Keypad.
    LCD_Go_To(1,15);
    LCD_Display_Char ('0');
    __delay_ms(1000);
    LCD_Clear();
    
    while(1) 
    {
        Number_1 = Get_Number();
        Operation = Get_Operation();
        Number_2 = Get_Number();
      
        Calculations(Number_1, Number_2, Operation);    
    }
    
}

// Functions Definitions.
void Calculations (int Number_1, int Number_2, unsigned char Operation)
{
    if (Operation == '+')
    {
        Result = Number_1 + Number_2;
        LCD_Display_Intger(Result);
    } 
    
    if (Operation == '-')
    {
        Result = Number_1 - Number_2;
        LCD_Display_Intger(Result);  
    } 
    
    if (Operation == '*')
    {
        Result = Number_1 * Number_2;
        LCD_Display_Intger(Result);  
    }  
    
    if (Operation == '/')
    {
        Result = (Number_1 / Number_2);
        LCD_Display_Intger(Result);
        int temp = abs (Number_1 - Result*Number_2);
        LCD_Display_Char ('.');
        Result = ((10*temp) / Number_2);
        LCD_Display_Intger(Result);
    }   
}
