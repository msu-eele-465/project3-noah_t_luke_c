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
int start4 = 0;
int start5 = 0;
int start6 = 0;
int start7 = 0;

int main(void) {
    LEDbarInit();
    keypadInit();
    __enable_interrupt();
    //lockKeypad(unlock_code);   
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
            case '4':   clear();
                        start4 = pattern4(start4);
                        break;
            case '5':   clear();
                        start5 = pattern5(start5);
                        break;
            case '6':   clear();
                        allOn();
                        start6 = pattern6(start6);
                        break;
            case '7':   clear();
                        start7 = pattern7(start7);
                        break;
            default:    break;
        }
    TB0CCTL1 &= ~CCIFG;
}



#pragma vector = PORT1_VECTOR
__interrupt void ISR_PORT1_S2(void) {
    char input = scanPad();
        switch(input){
            case 'D':   clear();
                        lockKeypad(unlock_code);
                        break;
            case '0':   pattern = '0';
                        clear();
                        pattern0();
                        break;
            case '1':   if(pattern == '1'){
                            start1 = 0;
                        }
                        clear();
                        start1 = pattern1(start1);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '1';
                        break;
            case '2':   if(pattern == '2'){
                            start2 = 0;
                        }
                        clear();
                        start2 = pattern2(start2);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '2';
                        break;
            case '3':   if(pattern == '3'){
                            start3 = 0;
                        }
                        clear();
                        start3 = pattern3(start3);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '3';
                        break;
            case '4':   if(pattern == '4'){
                            start4 = 0;
                        }
                        clear();
                        start4 = pattern4(start4);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '4';
                        break;
            case '5':   if(pattern == '5'){
                            start5 = 0;
                        }
                        clear();
                        start5 = pattern5(start5);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '5';
                        break;
            case '6':   if(pattern == '6'){
                            start6 = 0;
                        }
                        allOn();
                        start6 = pattern6(start6);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '6';
                        break;
            case '7':   if(pattern == '7'){
                            start7 = 0;
                        }
                        clear();
                        start7 = pattern7(start7);
                        TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;  // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CTL |= MC__UP;   // Start Up counting mode
                        pattern = '7';
                        break;
            case 'A':   TB0CTL &= ~MC__UP;  // Stop counting mode
                        TB0CTL |= TBCLR;    // Clear timer and dividers
                        __delay_cycles(2);
                        TB0CCR1 = TB0CCR1 - 8192;    
                        TB0CTL |= MC__UP;   // Start timer
                        break;
            case 'B':   TB0CCR1 = TB0CCR1 + 8192;
                        break;
                        
        }

    P1IFG &= ~BIT1;  // Clear the interrupt flag
    P1IFG &= ~BIT2;  // Clear the interrupt flag
    P1IFG &= ~BIT3;  // Clear the interrupt flag
    P1IFG &= ~BIT4;  // Clear the interrupt flag
}
