#include <msp430.h> 
#include <stdint.h>
#include <stdlib.h>

#include "seli_uart.h"

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	//Initialize Ports: PxDIR, PxREN, PxOUT, and PxIES
	P1DIR = 0x01;
	P1REN = 0x00;
	P1OUT = 0x01;
	uart_init();
	//Exit Low Power Mode
	PM5CTL0 &= ~(LOCKLPM5);
	_enable_interrupts();

	size_t waitVariable = 0;
	int temp = 0;
	//Main Loop
	while(1){
	    P1DIR ^= 0x01;
	    temp = uart_putChar('s');
	    for(waitVariable = 0; waitVariable < 20000; waitVariable++){} //Busy Wait
	}
	return 0;
}
