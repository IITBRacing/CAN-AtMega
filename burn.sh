#!/bin/bash
PROJECT=can_test_code
HEX=$PROJECT.hex
OBJDIR=build
 
 avrdude -p atmega16 -F -c usbasp -P usb -U flash:w:$HEX
 
