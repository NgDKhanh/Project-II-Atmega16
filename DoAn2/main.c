/*
 * DoAn2.c
 *
 * Created: 04/08/2023 12:19:18
 * Author : admin
 */ 

/*  
   LCD16x2 8 bit AVR ATmega16 interface
   http://www.electronicwings.com
*/

#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <avr/interrupt.h>
#include <util/delay.h>			/* Include inbuilt defined Delay header file */
#include <stdlib.h>
#include <stdio.h>
#include "LCD.h"
#include "UART.h"
#include "DHT11.h"


//#define DHT11_PIN 4
uint8_t I_RH,D_RH,I_Temp,D_Temp,CheckSum;
char data[5];
unsigned char receivedChar;
volatile int mode = 0;
int count = 0;
char receiveBuffer[17];
int countBufferLen = 0;

/*Interrupt Service Routine for INT0*/
ISR(INT0_vect)
{
	mode = (mode + 1) % 2;
	_delay_ms(50);  	/* Software debouncing control delay */
}

void receiveDataToBuffer()
{
	while ((receivedChar = UART_RxChar()) != '\r')
	{
		UART_TxChar(receivedChar);
		receiveBuffer[countBufferLen++] = receivedChar;
	}
	countBufferLen = 0;
}

void measure_Task()
{
	if (mode == 1)
	{
		Request();		/* send start pulse */
		Response();		/* receive response */
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
	
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			LCD_String("Error");
		}
	
		else
		{
			LCD_String_xy(0, 0, "Humi:   ");
			itoa(I_RH,data,10);
			LCD_String_xy(0,7, data);
			LCD_String(".");
		
			itoa(D_RH,data,10);
			LCD_String(data);
			LCD_String("%");

			LCD_String_xy(1, 0, "Temp:   ");
			itoa(I_Temp,data,10);
			LCD_String_xy(1, 7, data);
			LCD_String(".");
		
			itoa(D_Temp,data,10);
			LCD_String(data);
			LCD_Char(0xDF);
			LCD_String("C ");
		}
		_delay_ms(1000);
	}
}

void receiveData_Task()
{
	if (mode == 0)
	{
		receiveDataToBuffer();
		LCD_String_xy(0, 0, receiveBuffer);
		receiveDataToBuffer();
		LCD_String_xy(1, 0, receiveBuffer);
	}
}

int main(void)
{
	DDRD |= 0<<PD2;			/* PORTD as input */
	PORTD |= 1<< PD2;		/* Make pull up high */
	
	GICR = 1<<INT0;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	sei();			/* Enable Global Interrupt */
	
	DDRB |= 1<<PB7;
	PORTB |= 0<<PB7;
	
	LCD_Init();			/* Initialize LCD */
	LCD_Clear();			/* Clear LCD */
	UART_init(9600);
	
	
	
	
	
	while(1)
	{
		receiveData_Task();
		measure_Task();
	}
}
