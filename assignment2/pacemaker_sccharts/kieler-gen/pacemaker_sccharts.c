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
char AS;
char AP;
char LRI_t;
char StartAVI;
char VS;
char VP;
char PVARP_t;
char VRP_t;
char AEI_t;
char AVI_t;
char URI_t;
char StartRI;
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
char g11;
char PRE_g11;
char g12;
char g13;
char g14;
char g15;
char g16;
char g16b;
char g17;
char g18;
char g19;
char g20;
char g21;
char g22;
char PRE_g22;
char g23;
char g24;
char g25;
char g26;
char g27;
char PRE_g27;
char g28;
char g29;
char g30;
char _GO;
char _cg12;
char _cg24;
char _cg21;
char _cg5;
char _cg19;
char _cg7;
char _cg17;
char _cg23;
char _cg9;
char _cg13;
char _cg15;
char g25_e1;
char g29_e2;
int _PRE_GO;
void reset(){
   _GO = 1;
   _PRE_GO = 0;
   PRE_g2 = 0;
   PRE_g4 = 0;
   PRE_g6 = 0;
   PRE_g8 = 0;
   PRE_g11 = 0;
   PRE_g22 = 0;
   PRE_g27 = 0;
   return;
}
void tick(){
   if(_PRE_GO == 1){
      _GO = 0;
   }
   {
      g0 = _GO;
      g1 = g0;
      g26 = g0;
      g28 =(PRE_g27);
      g27 =(g26||g28);
      if(g27){
         VP = 0;
         AP = 0;
         StartRI = 0;
         StartAVI = 0;
      }
      g9 =(PRE_g8);
      _cg9 = AS;
      g15 =(g9&&(!(_cg9)));
      _cg15 = AEI_t;
      g17 =(g15&&(!(_cg15)));
      _cg17 = LRI_t;
      g18 =(g17&&_cg17);
      if(g18){
         VP =(VP||1);
      }
      g12 =(PRE_g11);
      _cg12 = VS;
      g13 =(g12&&(!(_cg12)));
      _cg13 =((AVI_t&&URI_t)||LRI_t);
      g14 =(g13&&_cg13);
      if(g14){
         VP =(VP||1);
      }
      g23 =(PRE_g22);
      _cg23 = PVARP_t;
      g24 =(g23&&(!(_cg23)));
      _cg24 = VS;
      g2 =(g18||(g12&&_cg12)||g14||(g24&&_cg24)||g1);
      g3 =(PRE_g2);
      g3b = g3;
      if(g3b){
         StartRI =(StartRI||1);
      }
      g5 =(PRE_g4);
      _cg5 = PVARP_t;
      g21 =(g5&&(!(_cg5)));
      _cg21 = VRP_t;
      g4 =(g3b||(g21&&(!(_cg21))));
      g7 =(PRE_g6);
      _cg7 = VRP_t;
      g19 =(g7&&(!(_cg7)));
      _cg19 = AS;
      g6 =((g19&&(!(_cg19)))||(g5&&_cg5));
      g8 =((g7&&_cg7)||(g17&&(!(_cg17)))||(g23&&_cg23));
      g10 =(g9&&_cg9);
      if(g10){
         StartAVI =(StartAVI||1);
      }
      g16 =(g15&&_cg15);
      if(g16){
         AP =(AP||1);
      }
      g16b = g16;
      if(g16b){
         StartAVI =(StartAVI||1);
      }
      g20 =(g19&&_cg19);
      if(g20){
         StartAVI =(StartAVI||1);
      }
      g11 =((g13&&(!(_cg13)))||g10||g16b||g20);
      g22 =((g21&&_cg21)||(g24&&(!(_cg24))));
      g25_e1 =(!((g3||g5||g7||g23||g9||g12)));
      g29_e2 =(!(g28));
   }
   PRE_g2 = g2;
   PRE_g4 = g4;
   PRE_g6 = g6;
   PRE_g8 = g8;
   PRE_g11 = g11;
   PRE_g22 = g22;
   PRE_g27 = g27;
   _PRE_GO = _GO;
   return;
}
