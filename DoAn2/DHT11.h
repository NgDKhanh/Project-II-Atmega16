/*
 * DHT11.h
 *
 * Created: 07/08/2023 16:45:47
 *  Author: admin
 */ 


#ifndef DHT11_H_
#define DHT11_H_

#include <stdint.h>

void Request();				/* Microcontroller send start pulse/request */
void Response();				/* receive response from DHT11 */
uint8_t Receive_data();			/* receive data */



#endif /* DHT11_H_ */