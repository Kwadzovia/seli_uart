/*
 * seli_uart.
 *
 *  Created on: Dec. 4, 2021
 *      Author: seli
 */

#ifndef SELI_UART_H_
#define SELI_UART_H

#include <msp430.h>
#include <stdlib.h>
#include <stdint.h>

#define TX_PIN 0x80
#define RX_PIN 0x40

int8_t uart_init(void);
int8_t uart_getChar(void);

int8_t uart_send();//read up on string buffers
int8_t uart_putChar(int messageChar);

#endif /* SELI_UART_H_ */
