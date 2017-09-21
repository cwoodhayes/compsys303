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

//Macros for declaring and using timer ISR's, since they always do the same thing here
#define DECLARE_TIMER_ISR(NAME) int/*alt_u32*/ NAME##_timer_isr(void* context) \
{ 	volatile int* trigger = (volatile int*)context; \
	*trigger = 1; \
	return 0; }
#define TIMER_ISR(NAME) NAME##_timer_isr

//Macro for restarting a timer
#define RESTART_TIMER(NAME) \
		alt_alarm_stop(& NAME##_timer); \
		alt_alarm_start(& NAME##_timer, NAME##_VALUE, NAME##_timer_isr, \
		FSMVAR(NAME##_t) )

static int/*alt_alarm*/ LRI_timer,
	PVARP_timer,
	VRP_timer,
	AEI_timer,
	AVI_timer,
	URI_timer;

//timer ISR declarations
DECLARE_TIMER_ISR (LRI)
DECLARE_TIMER_ISR (URI)
DECLARE_TIMER_ISR (PVARP)
DECLARE_TIMER_ISR (VRP)
DECLARE_TIMER_ISR (AEI)
DECLARE_TIMER_ISR (URI)



int main()
{
	reset();
	while (1) {
		//reset and start URI and LRI timers if necessary
		//also start pvarp, vrp, and aei, although they should have stopped long before
		if (FSMVAR(StartRI) ) {
			RESTART_TIMER(URI);
			RESTART_TIMER(LRI);
			RESTART_TIMER(PVARP);
			RESTART_TIMER(VRP);
			RESTART_TIMER(AEI);
		}
		if (FSMVAR(StartAVI) ) {
			RESTART_TIMER(AVI);
		}
		tick();
	}
}