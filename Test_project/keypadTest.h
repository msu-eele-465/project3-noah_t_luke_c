#include <msp430.h>
#include <stdbool.h>
#include <LEDbar.h>

#define unlock_code "1738"
const char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
const char rowPins[4] = {BIT1, BIT2, BIT3, BIT4};
const char colPins[4] = {BIT0, BIT1, BIT2, BIT3};

void keypadInit(void){

    // Status LED setup
    P3DIR |= BIT6;  // P1.5 as output
    P3OUT &= ~BIT6;  // Clear P1.5
    P1DIR |= BIT6;  // P1.6 as output
    P1OUT &= ~BIT6;  // Clear P1.6
    P1DIR |= BIT7;  // P1.7 as output
    P1OUT &= ~BIT7;  // Clear P1.7

    // Column pins are 6.0 - 6.3, right 4 pins on Keypad, descending left to right
    // Pin 5.0 is column 0 (connected to the middle of the keypad) (column 0 is the furthest left column)
    // Pin 5.3 is column 3 (connected to the right of the keypad) (column 3 is the furthest right column)
    P6DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Clear column pins
    P6DIR |= (BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins as outputs
    P6OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins high

    // Row pins are 1.1 - 1.4, left 4 pins, descending left to right
    // Pin 1.1 is row 0 (connected to the middle of the keypad) (row 0 is the top column)
    // Pin 1.4 is row 3 (connected to the left of the keypad) (row 3 is the bottom column)
    P1DIR &= ~(BIT1 + BIT2 + BIT4 + BIT4);  // Set row pins as inputs
    P1REN |= (BIT1 + BIT2 + BIT3 + BIT4);  // Enable pull-up/down resistors
    P1OUT &= ~(BIT1 + BIT2 + BIT3 + BIT4);  // Set pull-down for resistors

    // Interrupt Setup for port 1
    // Pins 1.1 1.2 1.3 1.4
    P1IES &= ~(BIT1 + BIT2 + BIT3 + BIT4); // Set IRQ sensitivity to L-to-H
    P1IFG &= ~(BIT1 + BIT2 + BIT3 + BIT4); // Clear IFG
    P1IE |= (BIT1 + BIT2 + BIT3 + BIT4);   // Enable IRQs
}


void lockKeypad(char str[]){ // Reset system until correct password is typed in
        P1IE &= ~(BIT1 + BIT2 + BIT3 + BIT4);   // Disenable IRQs
        clear();
        P3OUT &= ~BIT6;
        P1OUT |= BIT7;
        while(scanPad() != str[0]);    // Wait for a 1
        P1OUT |= BIT6;
        while(scanPad() != str[1]);    // Wait for a 7
        while(scanPad() != str[2]);    // Wait for a 3
        while(scanPad() != str[3]);    // Wait for an 8
        P1OUT &= ~BIT6;
        P1OUT &= ~BIT7;
        P3OUT |= BIT6;
        P1IE |= (BIT1 + BIT2 + BIT3 + BIT4);   // Enable IRQs
}


void testInput(){ // Test the keypad after system unlocks
    char input = scanPad();
        switch(input){
            case 'D':   clear();
                        lockKeypad(unlock_code);
                        break;
            case '1':   clear;
                        pattern1();
                        break;
            case '2':   clear();
                        pattern0();
                        break;
                        
        }
}
   

char scanPad() { // Scan the keypad
    int row, col;  // Loop variables
    P6OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Clear column pins

    for (col = 0; col < 4; col++) {
        P6OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // Clear all column pins
        P6OUT |= colPins[col];  // Set the current column pin high

        for (row = 0; row < 4; row++) {
            if ((P1IN & rowPins[row]) != 0) {  // Check if the row pin is high
                while ((P1IN & rowPins[row]) != 0);  // Wait for key release
                __delay_cycles(50000);  // Debounce delay
                P6OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins high
                return keys[col][row];  // Return the pressed key
            }
        }
    }
    P6OUT |= (BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins high
    return 0;  // Return 0 if no key is pressed
}



