/* 
 * File:   main.c
 * Author: E306_PC1
 *
 * Created on 7 septembre 2026, 13:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
int main (void){
  // static int i=1;
//Initialisation oscillateur
InitOscillator();
//Configuration des input et output (IO)
InitIO();
LED_BLANCHE_1 = 1;
LED_BLEUE_1 = 1;
LED_ORANGE_1 = 1;
LED_ROUGE_1 = 1;
LED_VERTE_1 = 1;
LED_BLANCHE_2 = 1;
LED_BLEUE_2 = 1;
LED_ORANGE_2 = 1;
LED_ROUGE_2 = 1;
LED_VERTE_2 = 1;
//Boucle Principale
    while(1){
   LED_BLANCHE_1 = !LED_BLANCHE_1;
      }
 // fin main
/*for(;;){
    if (LED_BLANCHE_1=0){
      LED_BLANCHE_1=1; }
  else{
      LED_BLANCHE_1=0;
  } 
}*/
//
}

