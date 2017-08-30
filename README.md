# Readme for COMPSYS303 Assignment 1

All top-level source code for this project is contained in the 'tlc.c' file.
It provides functionality for the four specified traffic-light controller
modes, implemented using the NIOS HAL libraries for the NIOS II processor.

## TLC I/O
### Buttons:
Key0: NS pedestrian walk request
Key1: EW pedestrian walk request
Key2: Car enter/exit intersection button.

### LED's:
Green LED0: NS-green
Green LED1: NS-yellow
Green LED2: NS-red
Green LED3: EW-green
Green LED4: EW-yellow
Green LED5: EW-red
Green LED6: NS pedestrian crossing 
Green LED7: EW pedestrian crossing

### Switches:
Switch0: Mode[0]
Switch1: Mode[1]. Mode[1:0] is a two-bit value representing the mode of the TLC. The TLC's mode = Mode[1:0]+1. (for example, Mode=00 corresponds to mode 1; Mode=01 is mode 2, etc).
Switch2: Configure timeouts. Switch ON to enter timeout configuration mode
at the next red-red state. Make sure to switch off at some point after entering configuration mode before the subsequent red-red state, otherwise the state will be re-entered and you'll have to input config values again.

##### Authors: Conor Hayes and Dallas Watene (Group 34)
