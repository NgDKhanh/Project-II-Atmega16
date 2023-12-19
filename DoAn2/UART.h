/*
 * UART.h
 *
 * Created: 07/08/2023 16:22:06
 *  Author: admin
 */ 


#ifndef UART_H_
#define UART_H_

void UART_init(long USART_BAUDRATE);
unsigned char UART_RxChar();
void UART_TxChar(char ch);
void UART_SendString(char *str);



#endif /* UART_H_ */