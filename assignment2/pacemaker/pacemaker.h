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
char g0;
char g1;
char g2;
char PRE_g2;
char g3;
char g3b;
char g4;
char PRE_g4;
char g5;
char g6;
char PRE_g6;
char g7;
char g8;
char PRE_g8;
char g9;
char g10;
char PRE_g10;
char g11;
char g12;
char g13;
char g14;
char g15;
char g16;
char g17;
char g18;
char g19;
char g20;
char PRE_g20;
char g21;
char g22;
char g23;
char g24;
char g25;
char PRE_g25;
char g26;
char g27;
char g28;
char _GO;
char _cg11;
char _cg22;
char _cg19;
char _cg5;
char _cg18;
char _cg7;
char _cg16;
char _cg21;
char _cg9;
char _cg12;
char _cg14;
char g23_e1;
char g27_e2;
int _PRE_GO;

void reset(){
   _GO = 1;
   _PRE_GO = 0;
   PRE_g2 = 0;
   PRE_g4 = 0;
   PRE_g6 = 0;
   PRE_g8 = 0;
   PRE_g10 = 0;
   PRE_g20 = 0;
   PRE_g25 = 0;
   return;
}

void tick(){
   if(_PRE_GO == 1){
      _GO = 0;
   }
   {
      g0 = _GO;
      g1 = g0;
      g21 =(PRE_g20);
      _cg21 = _pacemaker_local_PVARP_t;
      g22 =(g21&&(!(_cg21)));
      _cg22 = _pacemaker_local_VS;
      g11 =(PRE_g10);
      _cg11 = _pacemaker_local_VS;
      g24 = g0;
      g26 =(PRE_g25);
      g25 =(g24||g26);
      if(g25){
         _pacemaker_local_VP = 0;
         _pacemaker_local_AP = 0;
         _pacemaker_local_StartRI = 0;
      }
      g12 =(g11&&(!(_cg11)));
      _cg12 =((_pacemaker_local_AVI_t&&_pacemaker_local_URI_t)||_pacemaker_local_LRI_t);
      g13 =(g12&&_cg12);
      if(g13){
         _pacemaker_local_VP =(_pacemaker_local_VP||1);
      }
      g9 =(PRE_g8);
      _cg9 = _pacemaker_local_AS;
      g14 =(g9&&(!(_cg9)));
      _cg14 = _pacemaker_local_AEI_t;
      g16 =(g14&&(!(_cg14)));
      _cg16 = _pacemaker_local_LRI_t;
      g17 =(g16&&_cg16);
      if(g17){
         _pacemaker_local_VP =(_pacemaker_local_VP||1);
      }
      g2 =((g22&&_cg22)||(g11&&_cg11)||g1||g13||g17);
      g3 =(PRE_g2);
      g3b = g3;
      if(g3b){
         _pacemaker_local_StartRI =(_pacemaker_local_StartRI||1);
      }
      g5 =(PRE_g4);
      _cg5 = _pacemaker_local_PVARP_t;
      g19 =(g5&&(!(_cg5)));
      _cg19 = _pacemaker_local_VRP_t;
      g4 =(g3b||(g19&&(!(_cg19))));
      g7 =(PRE_g6);
      _cg7 = _pacemaker_local_VRP_t;
      g18 =(g7&&(!(_cg7)));
      _cg18 = _pacemaker_local_AS;
      g6 =((g5&&_cg5)||(g18&&(!(_cg18))));
      g8 =((g7&&_cg7)||(g16&&(!(_cg16)))||(g21&&_cg21));
      g15 =(g14&&_cg14);
      if(g15){
         _pacemaker_local_AP =(_pacemaker_local_AP||1);
      }
      g10 =(g15||(g18&&_cg18)||(g9&&_cg9)||(g12&&(!(_cg12))));
      g20 =((g19&&_cg19)||(g22&&(!(_cg22))));
      g23_e1 =(!((g3||g5||g7||g21||g9||g11)));
      g27_e2 =(!(g26));
   }
   PRE_g2 = g2;
   PRE_g4 = g4;
   PRE_g6 = g6;
   PRE_g8 = g8;
   PRE_g10 = g10;
   PRE_g20 = g20;
   PRE_g25 = g25;
   _PRE_GO = _GO;
   return;
}


#endif /* PACEMAKER_H_ */
