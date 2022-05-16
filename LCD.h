/*
 * LCD.h
 *
 * Created: 11/05/2022 10:14:56 am
 * Author: Hossam-Mamdouh
 */ 

#ifndef LCD_H_
#define LCD_H_

// LCD HW Pins
#define RS LATCbits.LATC0
#define RW LATCbits.LATC1
#define E  LATCbits.LATC2

#define LCD_DATA_PORT_DIR  TRISD
#define LCD_DATA_PORT      LATD

// LCD Commands
#define Eight_bit_Mode		 0x38
#define Init_Four_bit_Mode   0x32
#define Four_bit_Mode		 0x28
#define Clear                0x01
#define Cursor_OFF           0x0C
#define Cursor_ON            0x0E
#define Cursor_Location      0x80


// Functions Prototypes
void LCD_Init(void);
void LCD_Command(unsigned char Command);
void LCD_Display_Char(char Data);
void LCD_Display_String(char* Data);
void LCD_Go_To(unsigned char Row,unsigned char Column);
void LCD_Display_Intger(int Data);
void LCD_Clear(void);
char* itoa(int value, char* buffer, int base);
char* reverse(char *buffer, int i, int j);
void swap(char *x, char *y);


// Functions Definitions.
void LCD_Init(void)
{
	// Configure the Data pins (D4 --> D7) as Output pins.
	LCD_DATA_PORT_DIR = 0x00;
    
    TRISCbits.RC0 = 0; // Set RS pin as Output pin 
    TRISCbits.RC1 = 0; // Set RW pin as Output pin 
    TRISCbits.RC2 = 0; // Set E  pin as Output pin 
    
	// Send for 4 bit initialization of LCD.
	LCD_Command(Init_Four_bit_Mode);
	// use 2-line lcd + 4-bit Data Mode + 5*8 dot display Mode.
	LCD_Command(Four_bit_Mode);
	//Set Cursor OFF.
	LCD_Command(Cursor_OFF);
	// Clear LCD at the beginning.
	LCD_Command(Clear);
}

void LCD_Command(unsigned char Command)
{
	// Instruction Mode (RS = 0).
	RS = 0;
	// Writing to LCD (RW = 0).
	RW = 0;
    __delay_ms(5); 
	// Enable LCD (E = 1).
	E = 1;
	__delay_ms(5); 
	
    // Send the Upper 4 bits of the required Command to the data bus (D4 --> D7)
	LCD_DATA_PORT = (Command & 0xF0);
	__delay_ms(5);
	// Disable LCD (E = 0).
	E = 0;
	__delay_ms(5); 
		
	// Send the Lower 4 bits of the required Command to the data bus (D4 --> D7)
	// Enable LCD (E = 1).
	E = 1;
	__delay_ms(5); 
	LCD_DATA_PORT = ((Command << 4) & 0xF0);
	__delay_ms(5);
	// Disable LCD (E = 0).
	E = 0;
	__delay_ms(5);

}

void LCD_Display_Char(char Data)
{
	// Data Mode (RS = 1).
	RS = 1;
	// Writing to LCD (RW = 0).
	RW = 0;
	__delay_ms(5);
	
	// Send the Upper 4 bits of the required Data to the data bus (D4 --> D7)
	// Enable LCD (E = 1).
	E = 1;
	__delay_ms(5);
	LCD_DATA_PORT = (Data & 0xF0);
	__delay_ms(5);
	// Disable LCD (E = 0).
    E = 0;
	__delay_ms(5);
		
	// Send the Lower 4 bits of the required Data to the data bus (D4 --> D7)
	// Enable LCD (E = 1).
    E = 1;
	__delay_ms(5);
	LCD_DATA_PORT = ((Data << 4) & 0xF0);
	__delay_ms(5);
	// Disable LCD (E = 0).
	E = 0;
	__delay_ms(5);
}

void LCD_Display_String(char* Data)
{
	unsigned char i = 0;
	while(Data[i] != '\0')
	{
		LCD_Display_Char(Data[i]);
		i++;
	}
}

void LCD_Go_To(unsigned char Row,unsigned char Column)
{
	unsigned char Address;
	// First, calculate the required Address.
	switch(Row)
	{
		case 0:
		Address = Column;
		break;
		case 1:
		Address = Column + 0x40;
		break;
	}
	LCD_Command(Address | Cursor_Location);
}

void LCD_Display_Intger(int Data)
{
	char Buffer[16];             // String to hold the ASCII result.
	itoa(Data , Buffer , 10);    // 10 for decimal.
	LCD_Display_String(Buffer);
}

void LCD_Clear(void)
{
	// Clear LCD.
	LCD_Command(Clear);
}

// Iterative function to implement itoa() function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if((base < 2) || (base > 32)) 
    {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) 
        {
            buffer[i++] = 65 + (r - 10);
        }
        else 
        {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) 
    {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) 
    {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

// Function to swap two numbers
void swap(char *x, char *y) 
{
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i?j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}

#endif /* LCD_H_ */