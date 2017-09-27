/*
 * COMPSYS303 Assignment 2 main source file.
 * Authors: Conor Hayes and Dallas Watene
 *
 */

#include <stdio.h>
#include "pacemaker_fsm.h"
#include <sys/alt_alarm.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>
#include <alt_types.h>
#include <system.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>

//Macro for making FSM variables less of a mouthful
//(sometimes SCCHARTS generates them with odd names)
#define FSMVAR(NAME) NAME

/******************************DEBUGGING MACROS*******************************/
#define PRINT_IF_SET(VAR) if (VAR##_t) printf("%8s", #VAR); else printf("%8s", "-");
#define DISPLAY_TIMER_VARS \
	PRINT_IF_SET(PVARP); \
	PRINT_IF_SET(VRP); \
	PRINT_IF_SET(AVI); \
	PRINT_IF_SET(AEI); \
	PRINT_IF_SET(LRI); \
	PRINT_IF_SET(URI); \
	printf("\n")

/****************************GENERAL TIMER MACROS AND DECLARATIONS***********************************/
//Declare an isr for timer with name NAME
#define DECLARE_TIMER_ISR(NAME) alt_u32 NAME##_timer_isr(void* context) \
{ 	volatile int* trigger = (volatile int*)context; \
	*trigger = 1; \
	NAME##_t = 1; \
	/*DISPLAY_TIMER_VARS;*/ \
	return 0; }
#define TIMER_ISR(NAME) NAME##_timer_isr
//Restart the given associated with variable NAME
#define RESTART_TIMER(NAME) \
		NAME##_t = 0; \
		alt_alarm_stop(& NAME##_timer); \
		alt_alarm_start(& NAME##_timer, NAME##_VALUE, TIMER_ISR(NAME), \
		& FSMVAR(NAME##_t))

//timers for various FSM-required values
static alt_alarm LRI_timer,
	PVARP_timer,
	VRP_timer,
	AEI_timer,
	AVI_timer,
	URI_timer,
	led0_timer,
	led1_timer;

/***********************************LED TIMER MACROS AND DECLARATIONS***********************************/
int led_reg = 0x0;					//current output vals for the LED's
#define LED_PULSE_LEN 50			//Length of the LED's on cycle upon receiving AP or VP, in ms
#define LED_TIMER(NUM) led##NUM##_timer	//standard name for an LED timer with LED bit 'NUM'
/*
 * Declare a timer ISR which turns off a green LED
 * argument: The bit of the LED in the LEDS_GREEN_BASE register.
 */
#define DECLARE_LED_TIMER_ISR(NUM) alt_u32 led##NUM##_timer_isr(void *context) { \
			led_reg &= ~(1 << NUM); \
			return 0; \
		}
#define LED_TIMER_ISR(NUM) led##NUM##_timer_isr
//pulses the LED using the isr and timer, for LED_PULSE_LEN ms.
#define PULSE_LED(NUM) \
	led_reg |= (1 << NUM); \
	alt_alarm_start( & LED_TIMER(NUM), LED_PULSE_LEN, LED_TIMER_ISR(NUM), &led_reg )

/************************************************BUTTONS*************************************/
int buttons;	//stores the most recent value of the buttons register

/************************************************UART*********************************/
FILE* uart_fp;
int uart_rx_count = 0;
char uart_rx_buffer[255];
int fdterm;

/************************************************FUNCTION DECLARATIONS*****************************/

//timer ISR declarations
DECLARE_TIMER_ISR (URI)
DECLARE_TIMER_ISR (AVI)
DECLARE_TIMER_ISR (LRI)
DECLARE_TIMER_ISR (PVARP)
DECLARE_TIMER_ISR (VRP)
DECLARE_TIMER_ISR (AEI)

DECLARE_LED_TIMER_ISR(0)
DECLARE_LED_TIMER_ISR(1)

//Populate AS and VS with input from the buttons
void process_button_input() {
	//Button handling. An atrial sense is mapped to KEY0 and a ventricular sense is mapped
	//to KEY1
	int newbuttons = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
	if (newbuttons != buttons) {
		buttons = newbuttons;

		AS = (~buttons & (1 << 0)) >> 0;
		VS = (~buttons & (1 << 1)) >> 1;
	}
}

//Populate AS and VS with input from the UART
void process_uart_input() {
	char c= fgetc(uart_fp);
	if (c == 'A') {
		AS = 1;
	} else if (c == 'V') {
		VS = 1;
	}
	else {
		VS = 0;
		AS = 0;
	}
}

//Output AP and VP to the UART terminal
void process_uart_output() {
	if (AP) {
		fputc('A', uart_fp);
	}
	if (VP) {
		fputc('V', uart_fp);
	}
}

//Output AP and VP to the LED's
void process_led_output() {
	if (AP) {
		PULSE_LED(0);
	}
	if (VP) {
		PULSE_LED(1);
	}
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,led_reg);
}

int main()
{
	reset();

	printf("Initializing pacemaker...\n");
	//get the initial mode from the switches
	int mode = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & 0x3;

	//initialise the button registers
	IOWR_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE, 0);
	buttons = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);

	//Set up NON_BLOCKING UART
	fdterm = open(UART_NAME, O_RDWR | O_NONBLOCK, "rw+");
	uart_fp = fdopen(fdterm, "rw+");

	while (1) {
		// if Mode switches change:
		if (mode != (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & 0x3)) {
			printf("Switching mode...\n");
			mode = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & 0x3;
		}

		//Reset and start URI and LRI timers if necessary
		//Also restart PVARP, VRP, and AEI
		if (FSMVAR(StartRI)) {
			RESTART_TIMER(URI);
			RESTART_TIMER(LRI);
			RESTART_TIMER(PVARP);
			RESTART_TIMER(VRP);
			RESTART_TIMER(AEI);
		}

		//Restart AVI timer.
		if (FSMVAR(StartAVI)) {
			RESTART_TIMER(AVI);
		}

		switch(mode) {
		case 0:		//Mode 0
			process_button_input();
			tick();
			process_led_output();
			break;
		case 1:		//Mode 1
			process_uart_input();
			tick();
			process_led_output();
			process_uart_output();
			break;
		}
	}
}
