#Readme for COMPSYS303 Assignment 1
###Authors: Conor Hayes and Dallas Watene (Group 34)

All top-level source code for this project is contained in the 'tlc.c' file.
It provides functionality for the four specified traffic-light controller
modes, implemented using the NIOS HAL libraries for the NIOS II processor.

####TLC I/O
###Buttons:
Key0: NS pedestrian walk request
Key1: EW pedestrian walk request
Key2: Car enter/exit intersection button.

###LED's:
Green LED0: NS-green
Green LED1: NS-yellow
Green LED2: NS-red
Green LED3: EW-green
Green LED4: EW-yellow
Green LED5: EW-red
Green LED6: NS pedestrian crossing 
Green LED7: EW pedestrian crossing

###Switches:
Switch0: Mode[0]
Switch1: Mode[1]. Mode is a two-bit value determined by Switch0 and
Switch1--i.e., To enter mode 1, Mode = 00; mode 2 = 01; mode 3 = 10; mode 4 =
11.
Switch2: Configure timeouts. Switch ON to enter timeout configuration mode
at the next red-red state. 
