/*
 * Keypad.h
 *
 * Created: 21/04/2022 12:17:27 am
 * Author: Hossam-Mamdouh
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <xc.h>

#define N_col 4
#define N_row 4

unsigned char col, row;
static int Number;
int Final_Number = 0;
static unsigned char Key, Action;

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT  PORTB 
#define KEYPAD_PORT_IN   PORTB
#define KEYPAD_PORT_DIR  TRISB

// Functions Prototypes
void Keypad_Init(void);
unsigned char Keypad_Get_Key(void);
int Get_Number(void);
unsigned char Get_Operation(void);

// Functions Definitions.
 void Keypad_Init(void)
 {
     KEYPAD_PORT_DIR = 0x0F;
     KEYPAD_PORT_OUT = 0x00;
 }
 
unsigned char Keypad_Get_Key(void)
{
	while (1)
    {   
		for(row=0;row<4;row++) /* loop for rows */
		{
		    for(col=0;col<4;col++) /* loop for columns */
		    {  
			   if (row == 0)
			   {
				   KEYPAD_PORT_OUT = 0x10; 
				   switch (KEYPAD_PORT_IN & 0x0F)
				   {
					  case 0x01:
                      LCD_Display_Char('1');
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 1;
					  break;

					  case 0x02:
                      LCD_Display_Char('2');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 2;
					  break;
                  
					  case 0x04:
                      LCD_Display_Char('3');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 3;
					  break;
                  
					  case 0x08:
                      LCD_Display_Char('+');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 'A';
					  break;  
				   }
			   }
           
			  if (row == 1)
              {   
				   KEYPAD_PORT_OUT = 0x20;
				   switch (KEYPAD_PORT_IN & 0x0F)
				   {
					  case 0x01:
					  LCD_Display_Char('4');
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
                      return 4;
					  break;

					  case 0x02:
                      LCD_Display_Char('5');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 5;
					  break;
                  
					  case 0x04:
                      LCD_Display_Char('6');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 6;
					  break;
                  
					  case 0x08:
                      LCD_Display_Char('-'); 
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 'B';
					  break;  
				   }
			   }
                  
			   if (row == 2)
		       {
				   KEYPAD_PORT_OUT = 0x40; 
				   switch (KEYPAD_PORT_IN & 0x0F)
				   {
					  case 0x01:
                      LCD_Display_Char('7');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 7;
					  break;

					  case 0x02:
                      LCD_Display_Char('8');
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 8;
					  break;
                  
					  case 0x04:
                      LCD_Display_Char('9'); 
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 9;
					  break;
                  
					  case 0x08:
                      LCD_Display_Char('*'); 
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 'C';
					  break;  
				   }
               }   
                if (row == 3)
		        {
				   KEYPAD_PORT_OUT = 0x80; 
				   switch (KEYPAD_PORT_IN & 0x0F)
				   {
					  case 0x01:
					  return '*';
					  break;

					  case 0x02:
                      LCD_Display_Char('0'); 
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 0;
					  break;
                  
					  case 0x04:
                      LCD_Display_Char('='); 
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return '#';
					  break;
                  
					  case 0x08:
                      LCD_Display_Char('/');  
                      while ((KEYPAD_PORT_IN &0x0F) > 0);
					  return 'D';
					  break;  
				   }     
			   }
			}
		}
    }        
}

int Get_Number(void)
{
    while(1)
    {   
        Key = Keypad_Get_Key();
        if  ((Key == 'A') || (Key == 'B') || (Key == 'C') || (Key == 'D') || (Key == '#')) break;
        
        if (Key == '*')
        {
            LCD_Clear();
        }
        else if (Key == 1)
        {   
           if(Number == 0) Number = 1;  
           else Number = Number*10 + 1;
        }
        else if (Key == 2)
        {   
           if(Number == 0) Number = 2; 
           else Number = Number*10 + 2; 
        }
        else if (Key == 3)
        {   
           if(Number == 0) Number = 3; 
           else Number = Number*10 + 3;  
        }
        else if (Key == 4)
        {   
           if(Number == 0) Number = 4; 
           else Number = Number*10 + 4;  
        }
          
        else if (Key == 5)
        {   
           if(Number == 0) Number = 5; 
           else Number = Number*10 + 5;  
        }
        
        else if (Key == 6)
        {   
           if(Number == 0) Number = 6; 
           else Number = Number*10 + 6;  
        }
        else if (Key == 7)
        {   
           if(Number == 0) Number = 7; 
           else Number = Number*10 + 7;  
        }
        else if (Key == 8)
        {   
           if(Number == 0) Number = 8; 
           else Number = Number*10 + 8;  
        }
        else if (Key == 9)
        {   
           if(Number == 0) Number = 9; 
           else Number = Number*10 + 9;  
        }
        
       else if (Key == 0)
        {   
           if(Number == 0) Number = 0; 
           else Number = Number*10 + 0;  
        } 
    } 
   
    Final_Number = Number;
    Number =0;
    
    if (Key == 'A')
    {
        Action = '+';
       
        return Final_Number;        
    }
        
    else if (Key == 'B')
    {
        Action = '-';
        return Final_Number;       
    } 
        
    else if (Key == 'C')
    {
        Action = '*';
        return Final_Number;       
    }
        
    else if (Key == 'D')
    {
        Action = '/';
        return Final_Number;        
    }
    
    else if (Key == '#')
    {
        Action = '=';
        return Final_Number;        
    }
}

unsigned char Get_Operation(void)
{
    return Action;
}
#endif /* KEYPAD_H_ */