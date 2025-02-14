#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>

int main(void)
{ 
    #define unlock_code "1738"
    char code_entered[5] = "";
    int index_code = 0;
    bool unlock = false;

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
    P1DIR |= BIT0;                          // P1.0 as output, used for heartbeat led
    P1OUT &= ~BIT0;                         // Clear P1.0

    // Column pins are 6.0 - 6.3, right 4 pins on Keypad, decending left to right
    P6DIR |= BIT0 | BIT1 | BIT2 | BIT3;     // Set col pins as outputs
    P6REN |= BIT0 | BIT1 | BIT2 | BIT3;     // Pull up/down resistors
    P6OUT |= BIT0 | BIT1 | BIT2 | BIT3;     // Pull-up for resistors

    // Row pins are 5.0 - 5.3, left 4 pins, decending left to right
    P5DIR &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // Set row pins as inputs
    P5REN |= BIT0 | BIT1 | BIT2 | BIT3;     // Pull up/down resistors
    P5OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // Pull-down for resistors

    PM5CTL0 &= ~LOCKLPM5;                   // GPIO on            

    TB0CTL |= TBCLR;                        // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;                 // Use ACLK                   
    TB0CTL |= MC__UP;                       // Up counting mode
    TB0CCR0 = 32768;                        // Compare value

    TB0CCTL0 &= ~CCIFG;                     // Clear CCR0 flag
    TB0CCTL0 |= CCIE;                       // Enable flag
    __enable_interrupt(); 

    while(1){}                              // Loop forever

    return 0;
}

int scanPad(){
    char keys[4][4] = {{'1','2','3','A'},
                       {'4','5','6','B'},
                       {'7','8','9','C'},
                       {'*','0','#','D'}};
    
    int row, col = 0;                       // Loop variables
    P6OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // Clear all column pins

    for(col = 0; col < 4; col++){
        P6OUT |= (1 << col);                // Set single column high
        __delay_cycles(100);                // Delay let signal stop oscillating
        
        for (row = 0; row < 4; row++){
            if (P5IN & (1 << row) != 0){    // Check if row high, if high key pressed
                return keys[row][col];      // If pressed return the key
            }       
        }
        P6OUT &= ~(1 << col);               // Set the column back low
    }

    return 0;

}

//------------------------------------------------------------------------------
//           Interrupt Service Routines
//------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT ^= BIT0;                          // Toggle led
    TB0CCTL0 &= ~CCIFG;                     // Clear flag

}