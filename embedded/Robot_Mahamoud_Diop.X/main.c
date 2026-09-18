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
float distance0 = 0;
float distance1 = 0;
float distance2 = 0;

// Déclaration des variables pour stocker les résultats des 3 capteurs
unsigned int ADCValue0 = 0;
unsigned int ADCValue1 = 0;
unsigned int ADCValue2 = 0;

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
    LED_VERTE_2 = 1;
    ;
    // PWMSetSpeed(MOTEUR_DROIT, -5 );    //LED_BLANCHE_1 = !LED_BLANCHE_1;
    //PWMSetSpeed(MOTEUR_GAUCHE, -5); 
    //Boucle Principale
    while (1) {
        // 1. On teste si la conversion de l'ADC est terminée
        if (ADCIsConversionFinished() == 1) {
            // 2. On nettoie le flag de fin de conversion
            ADCClearConversionFinishedFlag();

            // 3. On récupère l'adresse du tableau des résultats
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;

            // 4. On récupère les résultats dans les variables demandées
           
            // led
            if (robotState.distanceTelemetreDroit > 30) {
                LED_ORANGE_1 = 0;
            } else {
                LED_ORANGE_1 = 1;
            }
            if (robotState.distanceTelemetreCentre > 30) {
                LED_BLEUE_1 = 0;
            } else {
                LED_BLEUE_1 = 1;
            }
            if (robotState.distanceTelemetreGauche > 30) {
                LED_BLANCHE_1 = 0;
            } else {
                LED_BLANCHE_1 = 1;
            }
            
            SetFreqTimer1(3.0) ;
            // (Optionnel) Relancer une nouvelle séquence de conversion si ton code ne le fait pas ailleurs
            // ADC1StartConversionSequence();
        }


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

