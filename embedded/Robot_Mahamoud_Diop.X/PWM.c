#include <xc.h>
#include "IO.h"
#include "PWM.h"
#include "robot.h"
#include "ToolBox.h"
#define PWMPER 24.0

void InitPWM(void) {
    PTCON2bits.PCLKDIV = 0b000; //Divide by 1
    PTPER = 100 * PWMPER; 
    IOCON1bits.PMOD = 0b11; 
    IOCON1bits.PENL = 1;
    IOCON1bits.PENH = 1;
    FCLCON1 = 0x0003; 
    
    IOCON2bits.PMOD = 0b11; 
    IOCON2bits.PENL = 1;
    IOCON2bits.PENH = 1;
    FCLCON2 = 0x0003; 
   
    PTCONbits.PTEN = 1;
}
double talon = 10;
float acceleration = 5;

void PWMUpdateSpeed() {
    // Cette fonction est appelee sur timer et permet de suivre des rampes d acceleration
    if (robotState.vitesseExtremeGaucheCommandeCourante < robotState.vitesseExtremeGaucheConsigne)
    robotState.vitesseExtremeGaucheCommandeCourante = Min(
        robotState.vitesseExtremeGaucheCommandeCourante + acceleration,
        robotState.vitesseExtremeGaucheConsigne);
    if (robotState.vitesseExtremeGaucheCommandeCourante > robotState.vitesseExtremeGaucheConsigne)
    robotState.vitesseExtremeGaucheCommandeCourante = Max(
        robotState.vitesseExtremeGaucheCommandeCourante - acceleration,
        robotState.vitesseExtremeGaucheConsigne);
    if (robotState.vitesseExtremeGaucheCommandeCourante > 0)
    {
    PDC1 = robotState.vitesseExtremeGaucheCommandeCourante * PWMPER + talon;
    SDC1 = talon;
    }
    else
    {
    PDC1 = talon;
    SDC1 = -robotState.vitesseExtremeGaucheCommandeCourante * PWMPER + talon;
    }

    if (robotState.vitesseGaucheCommandeCourante < robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Min(
            robotState.vitesseGaucheCommandeCourante + acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Max(
            robotState.vitesseGaucheCommandeCourante - acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > 0) {
        PDC1 = robotState.vitesseGaucheCommandeCourante * PWMPER + talon;
        SDC1 = talon;
    } else {
        PDC1 = talon;
        SDC1 = -robotState.vitesseGaucheCommandeCourante * PWMPER + talon;
    }
    if (robotState.vitesseDroiteCommandeCourante < robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Min(
            robotState.vitesseDroiteCommandeCourante + acceleration,
            robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante > robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Max(
            robotState.vitesseDroiteCommandeCourante - acceleration,
            robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante >= 0) {
        PDC2 = robotState.vitesseDroiteCommandeCourante * PWMPER + talon;
        SDC2 = talon;
    } else {
        PDC2 = talon;
        SDC2 = -robotState.vitesseDroiteCommandeCourante * PWMPER + talon;
    }
    if (robotState.vitesseExtremeDroiteCommandeCourante < robotState.vitesseExtremeDroiteConsigne)
    robotState.vitesseExtremeDroiteCommandeCourante = Min(
        robotState.vitesseExtremeDroiteCommandeCourante + acceleration,
        robotState.vitesseExtremeDroiteConsigne);
    if (robotState.vitesseExtremeDroiteCommandeCourante > robotState.vitesseExtremeDroiteConsigne)
    robotState.vitesseExtremeDroiteCommandeCourante = Max(
        robotState.vitesseExtremeDroiteCommandeCourante - acceleration,
        robotState.vitesseExtremeDroiteConsigne);
    if (robotState.vitesseExtremeDroiteCommandeCourante >= 0)
    {
    PDC2 = robotState.vitesseExtremeDroiteCommandeCourante * PWMPER + talon;
    SDC2 = talon;
    }
    else
    {
    PDC2 = talon;
    SDC2 = -robotState.vitesseExtremeDroiteCommandeCourante * PWMPER + talon;
    }
}

void PWMSetSpeedConsigne(unsigned char moteur, float vitesseEnPourcents)
{
    if (moteur == MOTEUR_GAUCHE) {
        robotState.vitesseGaucheConsigne = vitesseEnPourcents;
    } else if (moteur == MOTEUR_DROITE) {
        robotState.vitesseDroiteConsigne = - vitesseEnPourcents;

    }
}
