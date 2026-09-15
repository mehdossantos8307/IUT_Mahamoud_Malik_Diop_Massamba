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
#include "timer.h"
#include "IO.h"
#include "PWM.h"
#include "robot.h" 
#include "ADC.h"

int main(void) {
    // static int i=1;
    //Initialisation oscillateur
    InitOscillator();
    //Configuration des input et output (IO)
    InitIO();
    // Initialisation timers
    InitTimer23();
    InitTimer1();
    // Initialisation des PWM     ?
    InitPWM();
    InitADC1();
    
    PWM_EN = 1;
    PWMUpdateSpeed();
   
    LED_ORANGE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;
    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;;
   // PWMSetSpeed(MOTEUR_DROIT, -5 );    //LED_BLANCHE_1 = !LED_BLANCHE_1;
    //PWMSetSpeed(MOTEUR_GAUCHE, -5); 
    //Boucle Principale
    while (1) {
        
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

