/*
 * LCD.h
 *
 * Created: 07/08/2023 15:21:01
 *  Author: admin
 */ 


#ifndef LCD_H_
#define LCD_H_

/* Send command to LCD */
void LCD_Command(unsigned char cmnd);

/* LCD data write function */
void LCD_Char (unsigned char char_data);

/* LCD Initialize function */
void LCD_Init (void);

/* Send string to LCD function */
void LCD_String (char *str);

/* Send string to LCD with xy position */
void LCD_String_xy (char row, char pos, char *str);		

/* Clear screen */
void LCD_Clear()			



#endif /* INCFILE1_H_ */