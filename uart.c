/*
 * uart.c
 *
 *  Created on: Dec 19, 2021
 *      Author: selik
 */

#include "uart.h"

uint32_t position = 0;
char * message_ptr;
uint32_t message_size = 0;

void uart_init(void){
    //SETUP FOR 57600 BPS

    //    The recommended eUSCI_A initialization/reconfiguration process is:
    //    1. Set UCSWRST (BIS.B #UCSWRST,&UCAxCTL1).
    UCA1CTLW0 |= UCSWRST;

    //    2. Initialize all eUSCI_A registers while UCSWRST = 1 (including UCAxCTL1).
    UCA1CTLW0 |= UCSSEL__SMCLK;
    UCA1BRW = 17;   //UCBRx = 17
    UCA1MCTLW = 0x4A00; //UCOS16 = 0 UCBRSx = 0x4A

    //    3. Configure ports.
    P4SEL0 |= BIT3 + BIT4;
    P4SEL1 &= ~(BIT3 + BIT4);

    //    4. Clear UCSWRST by software (BIC.B #UCSWRST,&UCAxCTL1).
    UCA1CTLW0 &= ~UCSWRST;

    //    5. Enable interrupts (optional) using UCRXIE or UCTXIE.
    //Interrupts enabled when transmitting

    return;
}

void uart_write(char * message, uint32_t msg_size){

    position = 0;           //Reset global message index
    UCA1IE |= UCTXCPTIE;    //Enable Transmit complete interrupt
    UCA1IFG &= ~UCTXCPTIFG; //Clear Interrupt Flag

    message_size = msg_size;
    message_ptr = message;
    UCA1TXBUF = *message_ptr; //Start Message transmission

    return;
}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(){
    if(position < message_size){
        position++;
        message_ptr++;
        UCA1TXBUF = *message_ptr;
    }
    else{
        UCA1IE &= ~UCTXCPTIE;    //Disable Transmit complete interrupt
    }
    UCA1IFG &= ~UCTXCPTIFG; //Clear Interrupt Flag
}



