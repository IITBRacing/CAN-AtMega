

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LED.h"
#include <stdbool.h>

volatile uint16_t output_ans;

volatile bool conv_complete;//changed initialisation added volatile to both

uint16_t ADC_convert(uint8_t pin) { //In which pin conversion is to be done


uint16_t calc_value=0;

    conv_complete=0;
    ADCSRA |= 1<<ADPS2; //ADC Prescaler = 16

    ADMUX |= (1<<REFS0) | (1<<REFS1); // Reference Voltage = 2.56V 

    ADMUX &= 0b11110000 ; //making all last 4 bits of ADMUX zero

    ADMUX|= pin; //selecting correct pin 

    ADCSRA |= 1<<ADIE; // Enable ADC Interrupt

    ADCSRA |= 1<<ADEN; //Enable ADC

    sei();
    ADCSRA |= 1<<ADSC; //Start Conversion

   

    while (!conv_complete);
     
    

    calc_value=output_ans;

    return calc_value;



}


ISR(ADC_vect)
{
    uint8_t low_1 = ADCL; //a datatype of 8 bits, unsigned

    output_ans = ADCH<<8 | low_1; //similar, but 16 bits, concatenated with upper two bits in ADLAR

    conv_complete=1;

    

}
