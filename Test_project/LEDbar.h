#include <msp430.h>
#include <stdbool.h>

void LEDbarInit(void){
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
    P3DIR |= BIT3;
    P3OUT &= ~ BIT3;
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

void pattern1(void){
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

void clear(void){
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
    switch(led){
        case 1:     P6OUT |= BIT4;
                    break;
        case 2:     P3OUT |= BIT7;
                    break;
        case 3:     P2OUT |= BIT4;
                    break;
        case 4:     P3OUT |= BIT3;
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
    switch(led){
        case 1:     P6OUT &= ~BIT4;
                    break;
        case 2:     P3OUT &= ~BIT7;
                    break;
        case 3:     P2OUT &= ~BIT4;
                    break;
        case 4:     P3OUT &= ~BIT3;
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