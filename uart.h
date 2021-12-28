/*
 * uart.h
 *
 *  Created on: Dec 19, 2021
 *      Author: selik
 */

#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdint.h>

void uart_init(void);
void uart_write(char * message, uint32_t msg_size);

#endif /* UART_H_ */
