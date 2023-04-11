// Author: Jaeden Carpenter
// Net ID: carpenterjaeden
// Date: 3/20/23
// Assignment: Lab 3
//----------------------------------------------------------------------//

// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//




#include <Arduino.h>
#include <avr/io.h>
#include "switch.h"
#include "timer.h"
#include "pwm.h"
#include "sevensegment.h"

// defines


/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum {counting, motor} states;
states interrupt = motor;

  unsigned int portdhistory = 0;
int main(){

  Serial.begin(9600);
  initTimer0();
  initTimer1();
  initPWMTimer3();
  initSwitchPD0();
  initSevenSegment();



  
  sei(); // Enable global interrupts.
  
	while (1) {

      unsigned int result = ADCL;
      result += ((unsigned int) ADCH) << 8;
      unsigned int voltage = result * (4.586/1024.0);
      Serial.println(voltage,2);
      Serial.flush();
    

//switch case to determine delay based on the state we are in (motor or longDelat)
    switch (interrupt){
      case motor:
      
        changeDutyCycle(ADCL + ((unsigned int)ADCH << 8));
      break;
      case counting:
        
        for (unsigned int i = 9; i >= 0; i--){
          displayNum(i);
          delayMs1(1000);
        }
        interrupt = motor;
      break;
      default:
      interrupt = motor;
      break;
    }

   

	}
  return 0;
}


//Pin change interrupt: INT0 uses PORTD0
ISR(INT0_vect){
unsigned int changedbits;
changedbits = PIND ^ portdhistory;
portdhistory = PIND;
if(changedbits & (1 << PD0))
{ interrupt = counting; }

}