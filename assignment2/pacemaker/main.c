/*
 * COMPSYS303 Assignment 2 main source file.
 * Authors: Conor Hayes and Dallas Watene
 *
 */

#include <stdio.h>
#include "pacemaker.h"

int main()
{
	reset();
	while (1) {
		tick();
	}
}
