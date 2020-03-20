
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer_1.h"

ISR(TIMER0_COMPA_vect) {
	CTC_flag = 1;
}

// This function initializes a 16-bit timer used for delays.
void timer_init(void) {
	
	TIMSK0 = 0x00; //Disable timer interrupts
	TCCR0A = 0x02; //Timer not connected to any pins but waveform generator is in mode 2 CTC mode as timer 0 is being used
	TCCR0B = 0x02; // Timer_Rate = System_CLK/8 = 1MHz
	// 1 tick = 1 us (assume system clock = 8MHz)
}

// This is a blocking function that sets the timer value
// and waits until the value is reached. Waits for interrupt
// to execute.  Parameter "us" is truly 1 micro-second only
// if timer rate is set to 1MHz frequency. For example, this 
// project uses a system clock of 8MHz. Timer1 rate is set to
// System Clock divided by 8 which is 1MHz (in timer_init). 
// Therefore the "us" parameter truly is 1us.
void delay_us(uint8_t us) { //can go only upto 255 
	CTC_flag = 0; //Clear CTC Interrupt flag
	TCNT0 = 0x0000; //Clear timer
	OCR0A = us; //Load compare value with desired delay in us
	TIMSK0 = 0x02; //Enable OCIE0A Interrupt
	while(!CTC_flag); //wait for the designated number of us
}

void delay_ms(uint16_t ms) {
	for(uint16_t i=0; i<ms; i++) {
		delay_us(255);
                delay_us(255);
                delay_us(255);
                delay_us(235);
	}
}
