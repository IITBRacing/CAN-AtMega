/*
 * Sensor_CAN_Ex.c
 *
 * Created: 10/21/2013 1:19:58 PM
 *  Author: Digi-Key Design Support
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "LED.h"
#include "Timer_1.h"
#include "can_lib.h"

#define MY_ID_TAG 0x81 // 0x80 for 1st Sensor Node
                       // 0x81 for 2nd Sensor Node

#define DATA_BUFFER_SIZE 8 // 8 bytes max

static void sys_init(void);
static void io_init(void);

volatile uint8_t CTC_flag;

uint8_t response_data[DATA_BUFFER_SIZE];

int main(void)
{		
	// Initialize I/O, Timer, and CAN peripheral
	sys_init();
	
	// Enable global interrupts for Timer execution
	sei();
	
	// Flash LEDs to indicate program startup
	LED_Reg_Write(0xAA);
	delay_ms(50);
	LED_Reg_Write(0x00);

	st_cmd_t reply_message; // response message object
        DDRD = 32;           // Configure PORTD5 as output
        PORTD=0;
	
    while(1)
    {
		// Simulate collecting local sensor data: put test bytes in response buffer
		response_data[0]  = 23;
		if(MY_ID_TAG == 0x80) { response_data[1] = 0x3C; }
		if(MY_ID_TAG == 0x81) { response_data[1] = 0x0A; }

                  response_data[2]=0x45;
                  response_data[3]=0x23;
                  response_data[4]=0x00;
                  



			
		reply_message.pt_data = &response_data[0]; // point message object to first element of data buffer
		reply_message.ctrl.ide = 0; // standard CAN frame type (2.0A)

          ///////////////New line added in code //////////////
		reply_message.ctrl.rtr = 0; // this message object is not requesting a remote node to transmit data back
                
                
                reply_message.dlc = DATA_BUFFER_SIZE; // Number of bytes being sent (8 max)
		reply_message.id.std = MY_ID_TAG; // populate ID field with ID Tag
		reply_message.cmd =  CMD_TX_DATA; // assign this as a CAN transmit object try with CMD_TX as well

                //changed from the assignment below to the one above
                //reply_message.cmd = CMD_REPLY_MASKED; // assign this as a "Standard (2.0A) Reply" message object
		
		
		while(can_cmd(&reply_message) != CAN_CMD_ACCEPTED); // wait for MOb to configure
		
		while(can_get_status(&reply_message) != CAN_STATUS_COMPLETED); // wait for a transmit request to come in, and send a response
		
		// Flash LED0 to indicate a transmit request has been received from Hub Node
		//LED_Reg_Write(0x01);

                PORTD=PORTD^32;
		delay_ms(25);
		LED_Reg_Write(0x00);
    }
}

void sys_init(void) {
	// Make sure sys clock is at least 8MHz
	CLKPR = 0x80;  
	CLKPR = 0x00;
	
	io_init();	
	timer_init();
	can_init(0);
}

void io_init(void) {
	
	// Init PORTB[7:0] // LED port
	DDRB = 0x00;
	LED_Reg_Write(0x00); // clear all LEDs
	
	// Init PORTC[7:0] // PORTC[3:2] => RXCAN:TXCAN
	DDRC = 0x00;
	PORTC = 0x00;
	
	// Init PORTD[7:0]
	DDRD = 0x00;
	PORTD = 0x00;
	
	// Init PORTE[2:0]
	DDRE = 0x00;
	PORTD = 0x00;
}
