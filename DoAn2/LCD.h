/*
 * LCD.h
 *
 * Created: 07/08/2023 15:53:13
 *  Author: admin
 */ 


#ifndef LCD_H_
#define LCD_H_


void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char char_data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void LCD_Clear(void);


#endif /* LCD_H_ */