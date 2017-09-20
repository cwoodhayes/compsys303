/*
 * COMPSYS303 Assignment 2 main source file.
 * Authors: Conor Hayes and Dallas Watene
 *
 */

/*
char _pacemaker_local_AS;
char _pacemaker_local_AP;
char _pacemaker_local_LRI_t;
char _pacemaker_local_StartRI;
char _pacemaker_local_VS;
char _pacemaker_local_VP;
char _pacemaker_local_PVARP_t;
char _pacemaker_local_VRP_t;
char _pacemaker_local_AEI_t;
char _pacemaker_local_AVI_t;
char _pacemaker_local_URI_t;

#define AVI_VALUE 300
#define AEI_VALUE 800
#define PVARP_VALUE 50
#define VRP_VALUE 150
#define LRI_VALUE 950
#define URI_VALUE 900
 *
 */

#include <stdio.h>
#include "pacemaker_fsm.h"

//Macro for making FSM variables less of a mouthful
#define FSMVAR(NAME) _pacemaker_local_##NAME
//Macro for declaring timer ISR's
#define DECLARE_TIMER_ISR(NAME) alt_u32 NAME##_timer_isr(void* context)
//Macro for restarting a timer
#define RESTART_TIMER(NAME) \
		alt_alarm_stop(& NAME##_timer); \
		alt_alarm_start(& NAME##_timer, NAME##_VALUE, NAME##_timer_isr, \
		FSMVAR(NAME##_t) )

static alt_alarm LRI_timer,
	PVARP_timer,
	VRP_timer,
	AEI_timer,
	AVI_timer,
	URI_timer;

//timer ISR declarations

DECLARE_TIMER_ISR (LRI) {

}

DECLARE_TIMER_ISR (URI) {

}

int main()
{
	reset();
	while (1) {
		//reset and start URI and LRI timers if necessary
		if (FSMVAR(StartRI) ) {
			RESTART_TIMER(URI);
			RESTART_TIMER(LRI);
		}

		tick();
	}
}
