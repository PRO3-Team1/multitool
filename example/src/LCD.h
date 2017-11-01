#ifndef LCD_H
#define LCD_H


//Data pins and ports

//Pin 23
#define DATA0_PORT 2
#define DATA0_PIN 10

//Pin 24
#define DATA1_PORT 1
#define DATA1_PIN 12

//Pin 25
#define DATA2_PORT 1
#define DATA2_PIN 11

//Pin 26
#define DATA3_PORT 1
#define DATA3_PIN 7

//Pin 27
#define DATA4_PORT 1
#define DATA4_PIN 6

//Pin 28
#define DATA5_PORT 1
#define DATA5_PIN 5

//Pin 29
#define DATA6_PORT 1
#define DATA6_PIN 3

//Pin 30
#define DATA7_PORT 1
#define DATA7_PIN 2


// RS pin 31
#define RS_PORT 5
#define RS_PIN 3


// R/W pin 32
#define RW_PORT 5
#define RW_PIN 2

// Enable Configure pin 33
#define ENABLE_PORT 0
#define ENABLE_PIN 5



//0b00111000 . 8 bit , 2 line
#define FUNCTION_MODE 	0x38

//0b00001111
#define DISPLAY_MODE 	0xF

//0b00000001
#define CLEAR_MODE		0x1		

#define JUMP_LINE_0		0x80
#define JUMP_LINE_1		0xC0

void lcd_init(void); 
void char_to_LCD(char value); 
void string_to_LCD(char* string); 
void delay_ms(int number_of_seconds);
void set_line(int line);

#endif
