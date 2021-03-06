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
#include "ADC_conv.h"


#define MY_ID_TAG 0x81 // 0x80 for 1st Sensor Node
                       // 0x81 for 2nd Sensor Node

#define DATA_BUFFER_SIZE 8 // 8 bytes max

static void sys_init(void);
static void io_init(void);
static void can_send_interrupt(uint16_t);



volatile uint8_t CTC_flag;

uint8_t response_data[DATA_BUFFER_SIZE];

st_cmd_t reply_message; // response message object

uint8_t max_attempts=20;//This is the max no of times it will try to check status of the CAN bus before it breaks the loop

int main(void)
{	

        //uint16_t ADC_data=0;
        uint16_t L1C = 0;	// L1C : LOAD CELL 1
        uint16_t L2C = 0;	// L1C : LOAD CELL 2
        uint16_t SR = 0;	// SR : RIGHT SUSPENSION SENSOR
        uint16_t SL = 0;	// SL : LEFT SUSPENSION SENSOR
        uint16_t B2D = 0;	// B2D : 2nd BREAK PRESSURE SENSOR
        // uint16_t A6D = 0;	// A6D : Data in 6th analog connector on midcan

	// Initialize I/O, Timer, and CAN peripheral
	sys_init();
	
	// Enable global interrupts for Timer execution
	sei();
	
	// Flash LEDs to indicate program startup
	LED_Reg_Write(0xAA);
	delay_ms(50);
	LED_Reg_Write(0x00);

	
        DDRD = 32;           // Configure PORTD5 as output
        PORTD=0;
	
   
		// Simulate collecting local sensor data: put test bytes in response buffer
		
                response_data[1]=0x45;
                  response_data[2]=0x23;
                  

			
		reply_message.pt_data = &response_data[0]; // point message object to first element of data buffer
		reply_message.ctrl.ide = 0; // standard CAN frame type (2.0A)

          ///////////////New line added in code //////////////
		reply_message.ctrl.rtr = 0; // this message object is not requesting a remote node to transmit data back
                
                
                reply_message.dlc = DATA_BUFFER_SIZE; // Number of bytes being sent (8 max)
		reply_message.id.std = MY_ID_TAG; // populate ID field with ID Tag
		reply_message.cmd =  CMD_TX_DATA; // assign this as a CAN transmit object try with CMD_TX as well

                //changed from the assignment below to the one above
                //reply_message.cmd = CMD_REPLY_MASKED; // assign this as a "Standard (2.0A) Reply" message object
		
		
		
		// Flash LED0 to indicate a transmit request has been received from Hub Node
		//LED_Reg_Write(0x01);

            can_send_interrupt(4000);

            while (1){

                 L1C = ADC_convert(10); 
                 L2C = ADC_convert(5); 
                 SR = ADC_convert(4);	
                 SL = ADC_convert(6);	
                 B2D = ADC_convert(7);	
               //  A6D = ADC_convert(8);

		    
                  response_data[0]  = L1C/4;
		  response_data[1]  = L2C/4;
                  response_data[2]  = SR/4;
                  response_data[3]  = SL/4;
                  response_data[4]  = (L1C%4)*64+(L2C%4)*16+(SR%4)*4+(SL%4);
                  response_data[5]  = B2D/4;
                  response_data[6]  = B2D%4;
                  response_data[7]  = 0;
                     
                  /*ADC_data = ADC_convert(4);

                     PORTD=32;

                  response_data[0]  = ADC_data%256;
		  response_data[1]= ADC_data/256;
                  response_data[2]=0x20;
                  response_data[3]=0x00;
                  response_data[4]=20;
                  response_data[5]=ADC_data/256;
                  response_data[6]=11;
                  response_data[7]=178;  */

                 //PORTD=PORTD^32; ///If this line is not used the old data initialised before while loop is being sent Hence add some delay or something like that. 

                 
                  delay_us(100);


                }
           

                 

                
    
}


void can_send_interrupt(uint16_t time_overflow) {  //enables timer to overflow after time_overflow us


  TCCR1B |=1<<CS11|1<<WGM12; ///sets prescaler of 8.
  //TCCR1B &=0x11111001;//makes bit CS11 and CS12 zero as they are zero at reset

  TIMSK1 |= 1<<OCIE1A; //Timer1 Output Compare A Match interrupt enabled
  OCR1A = time_overflow; //Value at which CTC as clock runs at 8MHz and prescaler of 8 is used.
  

}

ISR(TIMER1_COMPA_vect){ //Checks argument
      
   ////Message is sent on CAN bus each time timer interrupt occurs.

   

  uint8_t count_attempts=0;
    
    while(can_cmd(&reply_message) != CAN_CMD_ACCEPTED){

          }; // wait for MOb to configure

    
		
    while(can_get_status(&reply_message) != CAN_STATUS_COMPLETED){

      count_attempts+=1;

      if (count_attempts==max_attempts) break;

         }; // wait for a transmit request to come in, and send a response
	
   //count=(count+1)%15;
	
 //if (count==0)
    
   


     
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
	DDRB = 0x00; //This is because ADC 4 is being as an input 
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
