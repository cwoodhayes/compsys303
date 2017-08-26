/* Traffic Light Controller
 *
 * --- Code is best viewed with the tab size of 4. ---
 */

#include <system.h>
#include <sys/alt_alarm.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>
#include <alt_types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// A template for COMPSYS 303 Assignment 1
//
// NOTE: You do not need to use this! Feel free
// to write your own code from scratch if you
// want, this is purely an example

// FUNCTION PROTOTYPES
// Timer ISRs
alt_u32 tlc_timer_isr(void* context);
alt_u32 camera_timer_isr(void* context);

//  Misc
// Others maybe added eg LEDs / UART
void lcd_set_mode(unsigned int mode);

// TLC state machine functions
void init_tlc(void);
void simple_tlc(int* state);
void pedestrian_tlc(int* state);
void configurable_tlc(int* state);
int config_tlc(int *tl_state);
void camera_tlc(int* state);

// Button Inputs / Interrupts
void buttons_driver(int* button);
void handle_mode_switch(unsigned int* modeid);
void handle_vehicle_button(void);
void init_buttons_pio(void);
void NSEW_ped_isr(void* context, alt_u32 id);

// Red light Camera
void clear_vehicle_detected(void);
void vehicle_checked(void);
int is_vehicle_detected(void);
int is_vehicle_left(void);

// Configuration Functions
int update_timeout(void);
void config_isr(void* context, alt_u32 id);
void buffer_timeout(unsigned int value);
void timeout_data_handler(void);


// CONSTANTS
#define OPERATION_MODES 0x03	// number of operation modes (00 - 03 = 4 modes)
#define CAMERA_TIMEOUT	2000	// timeout period of red light camera (in ms)
#define TIMEOUT_NUM 6			// number of timeouts
#define TIME_LEN 8				// buffer length for time digits


// USER DATA TYPES
// Timeout buffer structure
typedef struct  {
	int index;
	unsigned int timeout[TIMEOUT_NUM];
} TimeBuf;


// GLOBAL VARIABLES
static alt_alarm tlc_timer;		// alarm used for traffic light timing
static alt_alarm camera_timer;	// alarm used for camera timing

// NOTE:
// set contexts for ISRs to be volatile to avoid unwanted Compiler optimisation
static volatile int tlc_timer_event = 0;
static volatile int camera_timer_event = 0;
static volatile int pedestrianNS = 0;
static volatile int pedestrianEW = 0;

// 4 States of 'Detection':
// Car Absent
// Car Enters
// Car is Detected running a Red
// Car Leaves
static int vehicle_detected = 0;

// Traffic light timeouts
static unsigned int timeout[TIMEOUT_NUM] = {500, 6000, 2000, 500, 6000, 2000};
static TimeBuf timeout_buf = { -1, {500, 6000, 2000, 500, 6000, 2000} };

// UART
FILE* uart_fp;

// LCD screen
FILE* lcd_fp;

// Traffic light LED values
//static unsigned char traffic_lights[TIMEOUT_NUM] = {0x90, 0x50, 0x30, 0x90, 0x88, 0x84};
// NS RGY | EW RGY
// NR,NG | NY,ER,EG,EY
static unsigned char traffic_lights[TIMEOUT_NUM] = {0x24, 0x14, 0x0C, 0x24, 0x22, 0x21};

// first letter is for the EW light. Second letter is for NS light.
enum traffic_states {RR0, GR, YR, RR1, RG, RY};

static unsigned int mode = 0;
// Process states: use -1 as initialization state
static int proc_state[OPERATION_MODES + 1] = {-1, -1, -1, -1};

// Initialize the traffic light controller
// for any / all modes
void init_tlc(void)
{
	printf("Initializing TLC...");
	//start the TLC timer
	alt_alarm_start(&tlc_timer, timeout[proc_state[mode]], tlc_timer_isr, &tlc_timer_event);
	//get the initial mode from the switcehes
	mode = 0;
	lcd_set_mode(mode);
}


/* DESCRIPTION: Writes the mode to the LCD screen
 * PARAMETER:   mode - the current mode
 * RETURNS:     none
 */
void lcd_set_mode(unsigned int mode)
{

	lcd_fp = fopen(LCD_NAME, "w");
	fprintf(lcd_fp, "\x1B[2JTLC Mode: %d", mode+1);
	fclose(lcd_fp);
}

/* DESCRIPTION: Performs button-press detection and debouncing
 * PARAMETER:   button - referenced argument to indicate the state of the button
 * RETURNS:     none
 */
void buttons_driver(int* button)
{
	// Persistant state of 'buttons_driver'
	static int state = 0;

	*button = 0;	// no assumption is made on intial value of *button
	// Debounce state machine
		// call handle_mode_button()
}


/* DESCRIPTION: Updates the ID of the mode to be executed and the 7-segment display
 * PARAMETER:   modeid - current mode ID
 * RETURNS:     none
 */
//void handle_mode_switch(unsigned int* modeid)
//{
//
//}


/* DESCRIPTION: Simple traffic light controller
 * PARAMETER:   state - state of the controller
 * RETURNS:     none
 */
void simple_tlc(int* state)
{
	if (*state == -1) {
		// Process initialization state
		init_tlc();
		(*state)++;
		return;
	}

	// If the timeout has occured
	if (tlc_timer_event) {
		alt_alarm_stop(&tlc_timer);
		tlc_timer_event = 0;
		*state = (*state+1)%6;
		alt_alarm_start(&tlc_timer, timeout[*state], tlc_timer_isr, &tlc_timer_event);
	}
	/*
		// Increase state number (within bounds)
		// Restart timer with new timeout value
	*/
}


/* DESCRIPTION: Handles the traffic light timer interrupt
 * PARAMETER:   context - opaque reference to user data
 * RETURNS:     Number of 'ticks' until the next timer interrupt. A return value
 *              of zero stops the timer.
 */
alt_u32 tlc_timer_isr(void* context)
{
	volatile int* trigger = (volatile int*)context;
	*trigger = 1;
	return 0;
}


/* DESCRIPTION: Initialize the interrupts for all buttons
 * PARAMETER:   none
 * RETURNS:     none
 */
void init_buttons_pio(void)
{
	// Initialize NS/EW pedestrian button
	// Reset the edge capture register

}


/* DESCRIPTION: Pedestrian traffic light controller
 * PARAMETER:   state - state of the controller
 * RETURNS:     none
 */
void pedestrian_tlc(int* state)
{
	if (*state == -1) {
		// Process initialization state
		init_tlc();
		(*state)++;
		return;
	}

	// Same as simple TLC
	// with additional states / signals for Pedestrian crossings


}


/* DESCRIPTION: Handles the NSEW pedestrian button interrupt
 * PARAMETER:   context - opaque reference to user data
 *              id - hardware interrupt number for the device
 * RETURNS:     none
 */
void NSEW_ped_isr(void* context, alt_u32 id)
{
	// NOTE:
	// Cast context to volatile to avoid unwanted compiler optimization.
	// Store the value in the Button's edge capture register in *context


}


/* DESCRIPTION: Configurable traffic light controller
 * PARAMETER:   state - state of the controller
 * RETURNS:     none
 */
/*
If there is new configuration data... Load it.
Else run pedestrian_tlc();
*/
void configurable_tlc(int* state)
{
	if (*state == -1) {
		// Process initialization state
		return;
	}


}


/* DESCRIPTION: Implements the state machine of the traffic light controller in
 *              the ***configuration*** phase
 * PARAMETER:   tl_state - state of the traffic light
 * RETURNS:     Returns the state of the configuration phase
 */
/*
Puts the TLC in a 'safe' state... then begins update
*/
int config_tlc(int* tl_state)
{
	// State of configuration
	static int state = 0;

	if (*tl_state == -1) {
		// Process initialization state
		state = 0;
		return 0;
	}

	return state;
}


/* DESCRIPTION: Parses the configuration string and updates the timeouts
 * PARAMETER:   none
 * RETURNS:     none
 */
/*
 buffer_timeout() must be used 'for atomic transfer to the main timeout buffer'
*/
void timeout_data_handler(void)
{

}


/* DESCRIPTION: Stores the new timeout values in a secondary buffer for atomic
 *              transfer to the main timeout buffer at a later stage
 * PARAMETER:   value - value to store in the buffer
 * RETURNS:     none
 */
void buffer_timeout(unsigned int value)
{

}


/* DESCRIPTION: Implements the update operation of timeout values as a critical
 *              section by ensuring that timeouts are fully received before
 *              allowing the update
 * PARAMETER:   none
 * RETURNS:     1 if update is completed; 0 otherwise
 */
int update_timeout(void)
{

}

/* DESCRIPTION: Handles the red light camera timer interrupt
 * PARAMETER:   context - opaque reference to user data
 * RETURNS:     Number of 'ticks' until the next timer interrupt. A return value
 *              of zero stops the timer.
 */
alt_u32 camera_timer_isr(void* context)
{
	volatile int* trigger = (volatile int*)context;
	*trigger = 1;
	return 0;
}

/* DESCRIPTION: Camera traffic light controller
 * PARAMETER:   state - state of the controller
 * RETURNS:     none
 */
 /*
 Same functionality as configurable_tlc
 But also handles Red-light camera
 */
void camera_tlc(int* state)
{
	if (*state == -1) {
		configurable_tlc(state);
		return;
	}

}


/* DESCRIPTION: Simulates the entry and exit of vehicles at the intersection
 * PARAMETER:   none
 * RETURNS:     none
 */
void handle_vehicle_button(void)
{

}

// set vehicle_detected to 'no vehicle' state
void clear_vehicle_detected(void)
{
}
// set vehicle_detected to 'checking' state
void vehicle_checked(void)
{
}
// return true or false if a vehicle has been detected
int is_vehicle_detected(void)
{
}
// return true or false if the vehicle has left the intersection yet
int is_vehicle_left(void)
{
}

void update_traffic_lights(void) {
	switch (proc_state[mode]) {
	case RR0:
	case RR1:
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,0x24);
		break;
	case RG:
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,0x21);
		break;
	case RY:
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,0x22);
		break;
	case GR:
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,0x0C);
		break;
	case YR:
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,0x14);
		break;
	//default:
		//printf("TLC state invalid: %d  mode: %d\n", proc_state[mode], mode+1);
	}
}


int main(void)
{
	int buttons = 0;			// status of mode button

	lcd_set_mode(0);		// initialize lcd
	init_buttons_pio();			// initialize buttons
	while (1) {
		// Button detection & debouncing

		// if Mode switches change:
		if (mode != (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & 0x3)) {
			mode = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & 0x3;
			printf("mode: %08x\n", mode);
			lcd_set_mode(mode);
		}
		// if Car button pushed...
			// handle_vehicle_button

		// Execute the correct TLC
    	switch (mode) {
			case 0:
				simple_tlc(&proc_state[0]);
				break;
			case 1:
				pedestrian_tlc(&proc_state[1]);
				break;
			case 2:
				configurable_tlc(&proc_state[2]);
				break;
			case 3:
				camera_tlc(&proc_state[3]);
				break;
		}
		// Update Displays
    	// Update LED display:
    	update_traffic_lights();

	}
	return 1;
}
