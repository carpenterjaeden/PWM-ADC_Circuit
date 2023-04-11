#include "sevensegment.h"
#include <avr/io.h>
#include <util/delay.h>

void initSevenSegment(){
    //Set data directions for ports C0-C6
DDRC |= (1<< PORTC0) | (1<<PORTC1) | (1<<PORTC2) | 
        (1<<PORTC3) | (1<<PORTC4) | (1<<PORTC5) | 
        (1<<PORTC6);

}

void displayNum(unsigned int num){
    switch (num) {

        case 0:
            PORTC |= (1<< PORTC0) | (1<<PORTC1) | (1<<PORTC2) | 
            (1<<PORTC3) | (1<<PORTC4) | (1<<PORTC5); 
            PORTC &=  ~(1<<PORTC6);
        break;
        case 1:
            PORTC |= (1<<PORTC1) | (1<<PORTC2); 
         
            PORTC &=  ~(1<< PORTC0) & 
            ~(1<<PORTC3) & ~(1<<PORTC4) & ~(1<<PORTC5) & ~(1<<PORTC6);
        break;
         case 2:
            PORTC |= (1 << PORTC0) | (1 << PORTC1) | 
                     (1 << PORTC4) | (1 << PORTC6) | 
                     (1 << PORTC3);
            PORTC &= ~(1 << PORTC2) & ~(1 << PORTC5);
        break;
        case 3:
            PORTC |= (1 << PORTC0) | (1 << PORTC1) | 
                     (1 << PORTC2) | (1 << PORTC3) | 
                     (1 << PORTC6);
            PORTC &= ~(1 << PORTC4) & ~(1 << PORTC5);
        break;
        case 4:
            PORTC |= (1 << PORTC1) | (1 << PORTC2) |
                     (1 << PORTC5) | (1 << PORTC6);
            PORTC &= ~(1 << PORTC0) & ~(1 << PORTC3) & ~(1 << PORTC4);
        break;
        case 5:
            PORTC |= (1 << PORTC0) | (1 << PORTC2) |
                     (1 << PORTC3) | (1 << PORTC5) |
                     (1 << PORTC6);
            PORTC &= ~(1 << PORTC1) & ~(1 << PORTC4);
        break;
        case 6:
            PORTC &= ~(1 << PORTC1);
            PORTC |= (1 << PORTC0) | (1 << PORTC2) | (1 << PORTC3);
            PORTC |= (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6);
        break;
        case 7:
            PORTC |= (1<< PORTC0) | (1<<PORTC1) | (1<<PORTC2);
         
            PORTC &=  ~(1<<PORTC3) & ~(1<<PORTC4) & ~(1<<PORTC5) & ~(1<<PORTC6);
        break;
        case 8:
            PORTC |= (1<< PORTC0) | (1<<PORTC1) | (1<<PORTC2) | 
            (1<<PORTC3) | (1<<PORTC4) | (1<<PORTC5) | (1<<PORTC6);
        break;
        case 9:
            PORTC |= (1<< PORTC0) | (1<<PORTC1) | (1<<PORTC2) | 
            (1<<PORTC3) | (1<<PORTC5) | (1<<PORTC6);
         
            PORTC &=  ~(1<<PORTC4);
        break;
        default:
        PORTC &=  ~(1<< PORTC0) & ~(1<< PORTC1) & ~(1<< PORTC2) &
            ~(1<<PORTC3) & ~(1<<PORTC4) & ~(1<<PORTC5) & ~(1<<PORTC6);
        break;
    }
}