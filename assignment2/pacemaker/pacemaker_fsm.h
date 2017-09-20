/*
 * pacemaker.h
 *
 *  Created on: 20/09/2017
 *      Author: chay774
 */

#ifndef PACEMAKER_H_
#define PACEMAKER_H_

/*****************************************************************************/
/*                 G E N E R A T E D       C    C O D E                      */
/*****************************************************************************/
/* KIELER - Kiel Integrated Environment for Layout Eclipse RichClient        */
/*                                                                           */
/* http://www.informatik.uni-kiel.de/rtsys/kieler/                           */
/* Copyright 2014 by                                                         */
/* + Kiel University                                                         */
/*   + Department of Computer Science                                        */
/*     + Real-Time and Embedded Systems Group                                */
/*                                                                           */
/* This code is provided under the terms of the Eclipse Public License (EPL).*/
/*****************************************************************************/
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

void reset();
void tick();

// Example timeout values in milliseconds
#define AVI_VALUE 300
#define AEI_VALUE 800
#define PVARP_VALUE 50
#define VRP_VALUE 150
#define LRI_VALUE 950
#define URI_VALUE 900

#endif /* PACEMAKER_H_ */
