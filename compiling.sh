#!/bin/bash
PROJECT=can_test_code
FILE1=final_code_ADC
FILE2=LED
FILE3=can_drv
FILE4=can_lib
FILE5=Timer_1
FILE6=ADC_conv
OBJDIR=build
SRC1=$FILE1.c
SRC2=$FILE2.c
SRC3=$FILE3.c
SRC4=$FILE4.c
SRC5=$FILE5.c
SRC6=$FILE6.c
OBJ1=$OBJDIR/$FILE1.o
OBJ2=$OBJDIR/$FILE2.o
OBJ3=$OBJDIR/$FILE3.o
OBJ4=$OBJDIR/$FILE4.o
OBJ5=$OBJDIR/$FILE5.o
OBJ6=$OBJDIR/$FILE6.o
ELF=$OBJDIR/$PROJECT.elf
HEX=$PROJECT.hex





    mkdir -p $OBJDIR
	avr-gcc -g -mmcu=atmega16m1 -Os -std=c11 -c $SRC1 -o $OBJ1 #! We used -std=c11 so as to allow the timer code to get compiled which had initialisation of variable within for loop w
        avr-gcc -g -mmcu=atmega16m1 -Os -std=c11 -c $SRC2 -o $OBJ2
        avr-gcc -g -mmcu=atmega16m1 -Os -std=c11 -c $SRC3 -o $OBJ3
        avr-gcc -g -mmcu=atmega16m1 -Os -std=c11 -c $SRC4 -o $OBJ4
        avr-gcc -g -mmcu=atmega16m1 -Os -std=c11 -c $SRC5 -o $OBJ5
        avr-gcc -g -mmcu=atmega16m1 -Os -std=c11 -c $SRC6 -o $OBJ6
	avr-gcc -g -mmcu=atmega16m1 -Os -DF_CPU=8000000 $OBJ1 $OBJ2 $OBJ3 $OBJ4 $OBJ5 $OBJ6 -o $ELF
	avr-objcopy -j .text -j .data -O ihex $ELF $HEX

