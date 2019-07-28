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
    //Setup Timer  :CTC mode ;1ms cycle.ATtiny13A
#define OCRX ((F_CPU-512000)/512000)*2
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS02);
    OCR0A = OCRX;
    TIMSK0 |= 1 << OCIE0A;
    TIFR0 |= 1 << OCF0A;
    //

    sei();
    while (1) {
        //        if (READp(PINB, 3) == HIGH) {
        //            SETp(PORTB, 0);
        //            _delay_ms(500);
        //            CLEARp(PORTB, 0);
        //            _delay_ms(500);
        //        }



    }
}

ISR(TIM0_COMPA_vect) {

    static uint16_t i;
    if (i++ > 30) {
        TOGGLEp(PORTB, 0);

        i = 0;
    }



}