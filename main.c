#include <msp430.h> 

#include "uart.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	uart_init();
	PM5CTL0 &= ~(LOCKLPM5);
	__enable_interrupt();


	char message[] = "Hello World\n";
	while(1){

	    uart_write(message,(uint32_t)sizeof(message));
	    __delay_cycles(5000);

	}
	return 0;
}
