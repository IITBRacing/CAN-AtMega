# CAN-AtMega

### For test node
In timer.c , the timer has been changed from 1 to timer 0 as timer 1 is being used to send message on CAN bus periodically Same change is refllected on timer.h as well.

Orig_code.c First initial CAN code which sends data on bus at the end of while loop.
CAN_send_interrupt.c This sends CAN message after every fixed interval on the bus.
CAN_send_reset.c This is the code written to resolve the mbed reset issue as written in documentation.

main_code_ADC.c This is the final code using ADC to rad the analog voltage from pot.

ADC.c- This contains the function to return the 10 bit data from the read potentiometer value.

ADC.h Corresponding header
> Test node is tested and is working


### For MID-CAN node

The code used for Testing AtMega 16M1 is taken and we made changes in final_code_adc.c 

the only change made was, while mapping the sensor data to buffer bites of CAN message, 

we made changes according our convetional encoding method.

Board is compatible with 6 Analog pins but as 8 bits can maximum take 5 sensors data we ommited 6th buffer sensors data in CAN message  

> This code isn't tested yet

