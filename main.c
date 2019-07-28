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
#include <stdbool.h>
#include <avr/wdt.h>


bool timer01_start;
bool timer01_up;

int main(void) {
    /* Replace with your application code */

    OUTPUTp(DDRB, 0);
    OUTPUTp(DDRB, 1);
    OUTPUTp(DDRB, 2);


    //Setup Timer  :CTC mode ;1ms cycle.ATtiny13A
#define OCRX ((F_CPU-((2*8)*1000))/((2*8)*1000))*2
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS01);
    OCR0A = OCRX;
    TIMSK0 |= 1 << OCIE0A;
    TIFR0 |= 1 << OCF0A;
    //

    sei();


    wdt_enable(WDTO_1S);
    while (1) {
        if (READp(PINB, 3) == HIGH) {
            _delay_ms(100);

            if (READp(PINB, 3) == HIGH) {
                timer01_start = true;

                if (timer01_up == true) {
                    CLEARp(PORTB, 2);
                    SETp(PORTB, 1);
                } else {
                    SETp(PORTB, 2);
                }
            }



        } else {
            timer01_start = false;
            CLEARp(PORTB, 2);
            CLEARp(PORTB, 1);
        }


    }
}

ISR(TIM0_COMPA_vect) {

    static uint8_t i;
    if (i++ > 100) {

        wdt_reset();
        TOGGLEp(PORTB, 0);
        i = 0;
    }

#define timer01_PV 15 *1000

    static uint16_t timer01_CV;
    if (timer01_start == true) {
        if (timer01_CV++ > timer01_PV) {
            timer01_up = true;
            timer01_CV = 0;
        }
    } else {

        timer01_CV = 0;
        timer01_up = false;

    }

}