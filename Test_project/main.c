#include "intrinsics.h"
#include "msp430fr2355.h"
#include "sys/cdefs.h"
#include <msp430.h>
#include <stdbool.h>
#include <string.h>
#include <keypadTest.h>

#define unlock_code "1738"
//const char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
//const char rowPins[4] = {BIT0, BIT1, BIT2, BIT3};
//const char colPins[4] = {BIT0, BIT1, BIT2, BIT3};

int main(void) {
    keypadInit();
    char key1;
    char code_entered[5] = "";
    int index_code = 0;
    bool unlock = false;

    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    P1DIR |= BIT0;  // P1.0 as output, used for heartbeat LED
    P1OUT &= ~BIT0;  // Clear P1.0

    P6DIR |= BIT6;  // Green LED feedback
    P6OUT &= ~BIT6;

    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO

    TB0CTL |= TBCLR;  // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;  // Use ACLK
    TB0CTL |= MC__UP;  // Up counting mode
    TB0CCR0 = 32768;  // Compare value

    TB0CCTL0 &= ~CCIFG;  // Clear CCR0 flag
    TB0CCTL0 |= CCIE;  // Enable flag
    __enable_interrupt();


    while (1) {  // Loop forever
        while(scanPad() != '1');
        while(scanPad() != '7');
        while(scanPad() != '3');
        while(scanPad() != '8');
       P6OUT ^= BIT6;
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