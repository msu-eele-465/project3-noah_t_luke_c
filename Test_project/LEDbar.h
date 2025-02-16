#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>

void LEDbarInit(void){
    // Setting GPIO pins as outputs to control the LED bar
    // LED1
    P6DIR |= BIT4;
    P6OUT &= ~ BIT4;
    // LED2
    P3DIR |= BIT7;
    P3OUT &= ~ BIT7;
    // LED3
    P2DIR |= BIT4;
    P2OUT &= ~ BIT4;
    // LED4
    P4DIR |= BIT0;
    P4OUT &= ~BIT0;
    // LED5
    P3DIR |= BIT2;
    P3OUT &= ~ BIT2;
    // LED6
    P3DIR |= BIT0;
    P3OUT &= ~ BIT0;
    // LED7
    P2DIR |= BIT5;
    P2OUT &= ~ BIT5;
    // LED8
    P4DIR |= BIT4;
    P4OUT &= ~ BIT4;
    // LED9
    P4DIR |= BIT7;
    P4OUT &= ~ BIT7;
    // LED10
    P4DIR |= BIT6;
    P4OUT &= ~ BIT6;
}

void pattern0(void){
    // Sets LED bar to a 1010101010 static pattern
    ON(1);
    OFF(2);
    ON(3);
    OFF(4);
    ON(5);
    OFF(6);
    ON(7);
    OFF(8);
    ON(9);
    OFF(10);
}

void pattern0_alt(void){
    // Sets LED bar to a 0101010101 static pattern
    OFF(1);
    ON(2);
    OFF(3);
    ON(4);
    OFF(5);
    ON(6);
    OFF(7);
    ON(8);
    OFF(9);
    ON(10);
}

void pattern1(){
        pattern0();
        __delay_cycles(500000);
        pattern0_alt();
        __delay_cycles(500000);
}

void clear(void){
    // Turns every LED off
    OFF(1);
    OFF(2);
    OFF(3);
    OFF(4);
    OFF(5);
    OFF(6);
    OFF(7);
    OFF(8);
    OFF(9);
    OFF(10);
}

void ON(int led){
    // Turns LED on the LED bar ON depending on the given int
    switch(led){
        case 1:     P6OUT |= BIT4;
                    break;
        case 2:     P3OUT |= BIT7;
                    break;
        case 3:     P2OUT |= BIT4;
                    break;
        case 4:     P4OUT |= BIT0;
                    break;
        case 5:     P3OUT |= BIT2;
                    break;
        case 6:     P3OUT |= BIT0;
                    break;
        case 7:     P2OUT |= BIT5;
                    break;
        case 8:     P4OUT |= BIT4;
                    break;
        case 9:     P4OUT |= BIT7;
                    break;
        case 10:    P4OUT |= BIT6;
                    break;
        default:    break;                                                                                                                              
    }
}

void OFF(int led){
    // Turns LED on the LED bar OFF depending on the given int
    switch(led){
        case 1:     P6OUT &= ~BIT4;
                    break;
        case 2:     P3OUT &= ~BIT7;
                    break;
        case 3:     P2OUT &= ~BIT4;
                    break;
        case 4:     P4OUT &= ~BIT0;
                    break;
        case 5:     P3OUT &= ~BIT2;
                    break;
        case 6:     P3OUT &= ~BIT0;
                    break;
        case 7:     P2OUT &= ~BIT5;
                    break;
        case 8:     P4OUT &= ~BIT4;
                    break;
        case 9:     P4OUT &= ~BIT7;
                    break;
        case 10:    P4OUT &= ~BIT6;
                    break;
        default:    break;                                                                                                                              
    }
}

