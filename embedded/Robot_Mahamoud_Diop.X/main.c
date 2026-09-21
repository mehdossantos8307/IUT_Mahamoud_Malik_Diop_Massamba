#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "timer.h"
#include "IO.h"
#include "PWM.h"
#include "robot.h" 
#include "ADC.h"
#include "main.h"

float distance0 = 0;
float distance1 = 0;
float distance2 = 0;
float distance3 = 0;
float distance4 = 0;

unsigned int ADCValue0 = 0;
unsigned int ADCValue1 = 0;
unsigned int ADCValue2 = 0;
unsigned int ADCValue4 = 0;
unsigned int ADCValue3 = 0;
// euh ?
unsigned char stateRobot;
unsigned char nextStateRobot = 0;

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(MOTEUR_DROITE, 0);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, 0);
            stateRobot = STATE_ATTENTE_EN_COURS;
            break;

        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;

        case STATE_AVANCE:
            PWMSetSpeedConsigne(MOTEUR_DROITE, 25);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, 25);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;

        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(MOTEUR_DROITE, 15);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, 0);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;

        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(MOTEUR_DROITE, 0);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, 15);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;

        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(MOTEUR_DROITE, 15);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, -15);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

            ///
        case STATE_FROLEMENT_GAUCHE:
            PWMSetSpeedConsigne(MOTEUR_DROITE, 10);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, 30);
            stateRobot = STATE_FROLEMENT_GAUCHE_EN_COURS;
            break;
        case STATE_FROLEMENT_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_FROLEMENT_DROITE:
            PWMSetSpeedConsigne(MOTEUR_DROITE, 30);
            PWMSetSpeedConsigne(MOTEUR_GAUCHE, 10);
            stateRobot = STATE_FROLEMENT_DROITE_EN_COURS;
            break;
        case STATE_FROLEMENT_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}

void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;

    if (robotState.distanceTelemetreExtremeGauche < 15)
        positionObstacle = FROLEMENT_A_GAUCHE;
    else if (robotState.distanceTelemetreExtremeDroite < 15)
        positionObstacle = FROLEMENT_A_DROITE;

    else if (robotState.distanceTelemetreDroit < 40 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 40)
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 40 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche < 40)
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (robotState.distanceTelemetreCentre < 40)
        positionObstacle = OBSTACLE_EN_FACE;
    else
        positionObstacle = PAS_D_OBSTACLE;

    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
    else if (positionObstacle == FROLEMENT_A_GAUCHE)
        nextStateRobot = STATE_FROLEMENT_GAUCHE;
    else if (positionObstacle == FROLEMENT_A_DROITE)
        nextStateRobot = STATE_FROLEMENT_DROITE;

    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
\
}

int main(void) {
    InitOscillator();
    InitIO();
    InitPWM();
    InitADC1();
    InitTimer23();
    InitTimer1();
    InitTimer4();

    PWM_EN = 1;
    PWMUpdateSpeed();\

    LED_ORANGE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;
    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;

    stateRobot = STATE_ATTENTE;

    while (1) {
        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();

            unsigned int * result = ADCGetResult();
            float volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreExtremeGauche = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [3])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [4])* 3.3 / 4096;
            robotState.distanceTelemetreExtremeDroite = 34 / volts - 5;

            if (robotState.distanceTelemetreDroit > 30) {
                LED_ROUGE_1 = 0;
            } else {
                LED_ROUGE_1 = 1;
            }
            if (robotState.distanceTelemetreCentre > 30) {
                LED_ORANGE_1 = 0;
            } else {
                LED_ORANGE_1 = 1;
            }
            if (robotState.distanceTelemetreGauche > 30) {
                LED_BLEUE_1 = 0;
            } else {
                LED_BLEUE_1 = 1;
            }
            if (robotState.distanceTelemetreExtremeGauche > 30) {
                LED_BLANCHE_1 = 0;
            } else {
                LED_BLANCHE_1 = 1;
            }
            if (robotState.distanceTelemetreExtremeDroite > 30) {
                LED_VERTE_1 = 0;
            } else {
                LED_VERTE_1 = 1;
            }
        }
    }
}