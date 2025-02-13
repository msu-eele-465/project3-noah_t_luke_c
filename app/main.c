#include <msp430.h>
#include <stdbool.h>

int main(void)
{
 
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    P1DIR |= BIT0;                          // P1.0 as output
    P1OUT &= ~BIT0;                         // Clear P1.0

    P6DIR |= BIT
    
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


//------------------------------------------------------------------------------
//           Interrupt Service Routines
//------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT ^= BIT0;                          // Toggle led
    TB0CCTL0 &= ~CCIFG;                     // Clear flag

}