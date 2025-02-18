#include "intrinsics.h"
#include "msp430fr2355.h"
#include "sys/cdefs.h"
#include <msp430.h>
#include <stdbool.h>
#include <string.h>
#include <keypadTest.h>

char pattern;
int start1 = 0;
int start2 = 0;
int start3 = 0;

int main(void) {
    LEDbarInit();
    keypadInit();
    __enable_interrupt();
    lockKeypad(unlock_code);   
    while(1) {}          // Loop forever
    return 0;
}



//------------------------------------------------------------------------------
//           Interrupt Service Routines
//------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void) {
    P1OUT ^= BIT0;  // Toggle LED
    TB0CCTL0 &= ~CCIFG;  // Clear the interrupt flag
}


#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_CCR1(void) {
    switch (pattern){
            case 'D':   clear();
                        lockKeypad(unlock_code);
                        pattern = NULL;
            case '0':   clear();
                        pattern0();
                        break;
            case '1':   clear();
                        start1 = pattern1(start1);
                        break;
            case '2':   clear();
                        start2 = pattern2(start2);
                        break;
            case '3':   clear();
                        start3 = pattern3(start3);
                        break;
            default:    clear();
                        break;
        }
    TB0CCTL1 &= ~CCIFG;
}


#pragma vector = PORT1_VECTOR
__interrupt void ISR_PORT1_S2(void) {
    char input = scanPad();
        switch(input){
            case 'D':   pattern = 'D';
                        break;
            case '0':   pattern = '0';
                        break;
            case '1':   pattern = '1';
                        break;
            case '2':   if(pattern == '2'){
                            start2 = 0;
                        }
                        pattern = '2';
                        break;
            case '3':   if(pattern == '3'){
                            start3 = 0;
                        }
                        pattern = '3';
                        break;
            case 'A':   TB0CCR1 = TB0CCR1 - 8192;
                        break;
            case 'B':   TB0CCR1 = TB0CCR1 + 8192;
                        break;
                        
        }

    P1IFG &= ~BIT1;  // Clear the interrupt flag
    P1IFG &= ~BIT2;  // Clear the interrupt flag
    P1IFG &= ~BIT3;  // Clear the interrupt flag
    P1IFG &= ~BIT4;  // Clear the interrupt flag
}
