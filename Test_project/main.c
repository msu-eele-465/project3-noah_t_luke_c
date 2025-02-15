#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>
#include <string.h>

#define unlock_code "1738"
const char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
const char rowPins[4] = {BIT0, BIT1, BIT2, BIT3};
const char colPins[4] = {BIT0, BIT1, BIT2, BIT3};

    P1DIR |= BIT0;                                      // P1.0 as output
    P1OUT &= ~BIT0;                                     // Clear P1.0

    P6DIR |= BIT
    
    PM5CTL0 &= ~LOCKLPM5;                               // GPIO on            

    WDTCTL = WDTPW | WDTHOLD;                           // Stop watchdog timer

    P1DIR |= BIT0;                                      // P1.0 as output, used for heartbeat LED
    P1OUT &= ~BIT0;                                     // Clear P1.0

    P6DIR |= BIT6;                                      // Green LED feedback
    P6OUT &= ~BIT6;

    // Column pins are 6.0 - 6.3, right 4 pins on Keypad, descending left to right
    P6DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);              // Clear column pins
    P6DIR |= (BIT0 + BIT1 + BIT2 + BIT3);               // Set column pins as outputs
    P6OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);              // Set column pins low

    // Row pins are 5.0 - 5.3, left 4 pins, descending left to right
    P5DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);              // Set row pins as inputs
    P5REN |= (BIT0 + BIT1 + BIT2 + BIT3);               // Enable pull-up/down resistors
    P5OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);              // Set pull-down for resistors

    PM5CTL0 &= ~LOCKLPM5;                               // Enable GPIO

    TB0CTL |= TBCLR;                                    // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;                             // Use ACLK
    TB0CTL |= MC__UP;                                   // Up counting mode
    TB0CCR0 = 32768;                                    // Compare value

    TB0CCTL0 &= ~CCIFG;                                 // Clear CCR0 flag
    TB0CCTL0 |= CCIE;                                   // Enable flag
    __enable_interrupt();

    while (1) {                                         // Loop forever
        char key = scanPad();
        
    }

    return 0;
}

//-----------------------------------------------Scan Keypad------------------------------------------------------------------------

char scanPad() {
    int row, col;  // Loop variables

    for (col = 0; col < 4; col++) {
        P6OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);          // Clear all column pins
        P6OUT |= colPins[col];                          // Set the current column pin high

        for (row = 0; row < 4; row++) {
            if ((P5IN & rowPins[row]) != 0) {           // Check if the row pin is high
                P6OUT ^= BIT6;                          // Toggle LED for feedback
                while ((P5IN & rowPins[row]) != 0);     // Wait for key release
                __delay_cycles(50000);                  // Debounce delay
                return keys[row][col];                  // Return the pressed key
            }
        }
    }

    return 0;                                           // Return 0 if no key is pressed
}

//------------------------------------------------------------------------------
//           Interrupt Service Routines
//------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void) {
    P1OUT ^= BIT0;  // Toggle LED
    TB0CCTL0 &= ~CCIFG;  // Clear the interrupt flag
}