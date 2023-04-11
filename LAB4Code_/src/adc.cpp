#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

void initADC(){

    //set input channel ADC0, sets mode to single ended input with MUX[5:0] = 0b000000
    ADMUX &= ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
    ADMUX &= ~((1 << MUX4) & ~(1 << MUX3));
    ADCSRB &= ~(1 << MUX5);


    //sets vref to AVCC with external capacitr at AREF pin
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1<< REFS0);


    //sets ADCH and ADCL to right adjusted
    ADMUX &= ~(1 << ADLAR);

    //set auto trigger to disable
    ADMUX &= ~(1 << ADATE);

    //set interrupt to disable
    ADMUX &= ~(1 << ADIE);

    //enables the ADC
    ADCSRA |= (1 << ADEN) | (1 << ADATE);

    // Sampling rate is 1/ ((1/125K Hz )*(13 clock cycles)) = 9615 KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    //disable ADC0 pin digital input - pin A0 on board
    DIDR0 |= (1 << ADC7D);

    //start a conversion
    ADCSRA |= (1<<ADSC);
}