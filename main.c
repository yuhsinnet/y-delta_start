/*
 * File:   main.c
 * Author: SG
 *
 * Created on 2019?7?28?, ?? 8:20
 */

#define F_CPU 1200000UL
#include <avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "ioconfig.h"

int main(void) {
    /* Replace with your application code */

    OUTPUTp(DDRB, 0);

    while (1) {
        if (READp(PINB, 3) == HIGH) {
            SETp(PORTB, 0);
            _delay_ms(500);
            CLEARp(PORTB, 0);
            _delay_ms(500);
        }



    }
}
