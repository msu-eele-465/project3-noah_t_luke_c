#include <msp430.h>
#include <stdbool.h>

void init(void){
    P1DIR |=  BIT2;         // Set 1.2 output
    P1OUT |=  BIT2;        // Clear 1.2

    P3DIR &= ~BIT6;         // Set 3.6 input
    P3OUT &= ~BIT6;         // Clear 3.6
}


