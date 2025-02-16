#include "intrinsics.h"
#include "msp430fr2355.h"
#include "sys/cdefs.h"
#include <msp430.h>
#include <stdbool.h>
#include <string.h>
#include <keypadTest.h>
//#include<LEDbar.h>
char pattern;
//const char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
//const char rowPins[4] = {BIT0, BIT1, BIT2, BIT3};
//const char colPins[4] = {BIT0, BIT1, BIT2, BIT3};

int main(void) {
    LEDbarInit();
    keypadInit();
    char code_entered[5] = "";
    int index_code = 0;
    bool unlock = false;

    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    P1DIR |= BIT0;  // P1.0 as output, used for heartbeat LED
    P1OUT &= ~BIT0;  // Clear P1.0

    P6DIR |= BIT6;  // Green LED feedback
    P6OUT &= ~BIT6;

    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO

    // Setup Timer B0
    TB0CTL |= TBCLR;  // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;  // Use ACLK
    TB0CTL |= MC__UP;  // Up counting mode
    TB0CCR0 = 32768;    // Compare value

    // Set up timer compare IRQs
    TB0CCTL0 &= ~CCIFG;  // Clear CCR0 flag
    TB0CCTL0 |= CCIE;  // Enable flag



    __enable_interrupt();


    lockKeypad(unlock_code);
    while(1) {          // Loop forever
        switch (pattern){
            case 'D':   clear();
                        lockKeypad(unlock_code);
                        pattern = NULL;
            case '0':   clear();
                        while(pattern == '0'){
                            pattern0();
                        }
                        break;
            case '1':   clear();
                        while(pattern == '1'){
                        pattern1();
                        break;
                        }
            default:    clear();
                        break;
        }
    }

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
                        
        }

    P1IFG &= ~BIT1;  // Clear the interrupt flag
    P1IFG &= ~BIT2;  // Clear the interrupt flag
    P1IFG &= ~BIT3;  // Clear the interrupt flag
    P1IFG &= ~BIT4;  // Clear the interrupt flag
}
