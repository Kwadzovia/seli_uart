/*
 * seli_uart.c
 *
 *  Created on: Dec. 4, 2021
 *      Author: seli
 */
#include "seli_uart.h"

int8_t uart_init(void){

    //1. Set UCSWRST (BIS.B #UCSWRST,&UCAxCTL1).
    UCA0CTLW0 = UCSWRST;

    //2. Initialize all eUSCI_A registers while UCSWRST = 1 (including UCAxCTL1).

    //Clock Settings for 9600 Baud
    UCA0CTLW0 |= UCSSEL_3; //1 MHz SMCLK
    UCA0BR0 = 6;
    UCA0MCTLW |= (UCOS16);
    UCA0MCTLW |= 0x2000 + 0x80;

    //3. Configure ports.
    P1DIR |= TX_PIN;
    P1DIR &= ~(RX_PIN);
    P1SEL0 |= TX_PIN + RX_PIN;
    P1SEL1 = 0;
    //P4REN |= RX_PIN;

    //4. Clear UCSWRST by software (BIC.B #UCSWRST,&UCAxCTL1).
    UCA0CTLW0 = ~(UCSWRST);

    //5. Enable interrupts (optional) using UCRXIE or UCTXIE.
    //UCA1IE |= UCSTTIE + UCTXCPTIE; //Transmit and Transmit Complete

    return 1;
}

int8_t uart_getChar(void){
    int8_t status = -1;

    //while(UCA1IFG & UCRXIFG){};
    //status = (UCA1RXBUF & UCRXBUF0);
    return status;
}

int8_t uart_putChar(int messageChar){
    int8_t status = -1;
    //while(!(UCA1IFG & UCTXIFG));
    UCA0TXBUF = (char) messageChar;
    status = 1;
    return status;
}
