// Author: Jaeden Carpenter, Sam Kerns, Malcolm Hayes
// Net ID: carpenterjaeden, s4k3, malcolmhayes
// Date: 3/20/23
// Assignment: Lab 4
//----------------------------------------------------------------------//




#include <Arduino.h>
#include <avr/io.h>
#include "switch.h"
#include "timer.h"
#include "pwm.h"
#include "sevensegment.h"
#include "adc.h"

// defines


/*
 * Define a set of states that can be used in the state machine using an enum.
 */
typedef enum {counting, motor} states;
//global variable for motor states
volatile states interrupt = motor;

typedef enum {wait_press, debounce_press, wait_release, debounce_release} debounce;
//define global variable for debounce states
volatile debounce dbState = wait_press;


int main(){

  Serial.begin(9600);
  initTimer0();

  //Timer 1 used for counting, timer 3 used for PWM, Switch used for state change, seven segment translates numbers to the display
  initTimer1();
  initPWMTimer3();
  initSwitchPD0();
  initSevenSegment();
  initADC();



  
  sei(); // Enable global interrupts.
  
  unsigned int result = 0;
  float voltage = 0;
	while (1) {

      result = ADCL;
      result += ((unsigned int) ADCH) << 8;
      voltage = result * (4.586/1024.0);
      Serial.println(voltage,2);
      Serial.flush();
    

//switch case to determine delay based on the state we are in (motor or counting)
    switch (interrupt){
      case motor:
        PORTB |= (1<<PB5);
        changeDutyCycle(ADCL + ((unsigned int)ADCH << 8));
      break;
      case counting:
      PORTB &= ~(1 << PB5);
      //set duty cycle at the 0
        changeDutyCycle(512);
        for (unsigned int i = 9; i >= 0; i--){
          PORTB |= (1 << PB5);
          displayNum(i);
          delayMs0(1000);
        }
        
        interrupt = motor;
      break;
      default:
      interrupt = motor;
      break;
    }

  //Switch case for debounce states
  switch(dbState){
  //do nothing while waiting
    case wait_press:
    break;

  //debounce press adds delay and goes to wait_release
    case debounce_press:
    delayMs0(1);
    dbState = wait_release;
    break;

  //Do nothing while waiting
    case wait_release:
    break;
  //After release, delay and then go back to waiting for press
    case debounce_release:
    delayMs0(1);
    dbState = wait_press;
    interrupt = counting;
    break;

  }

	}
  return 0;
}


//Pin change interrupt: INT0 uses PORTD0
ISR(INT0_vect){

//if INT0 is triggered for press
if (dbState == wait_press){
  dbState = debounce_press;
}
//if INT0 is triggered for release
else if (dbState == wait_release){
  //change motor state to counting
  dbState = debounce_release;
}



}