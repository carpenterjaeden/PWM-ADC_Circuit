// Author: Jaeden Carpenter, Sam Kerns, Malcolm Hayes
// Net ID: carpenterjaeden, s4k3, malcolmhayes
// Date: 3/20/23
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PD0 and sets it into input mode
 */
void initSwitchPD0(){
  //data direction
DDRD &= ~(1 << PD0);
//port
PORTD |= (1 << PD0);

//Set the external interrupt control register A to 11 for INT0
EICRA |= (1<<ISC00) | (1<<ISC01);
//turn on INT0 in the external interrupt mask register to enable it
EIMSK |= (1<<INT0);




}
