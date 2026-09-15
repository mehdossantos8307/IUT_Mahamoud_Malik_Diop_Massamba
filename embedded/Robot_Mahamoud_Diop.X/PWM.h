/* 
 * File:   PWM.h
 * Author: E306_PC1
 *
 * Created on 15 septembre 2026, 10:59
 */

#ifndef PWM_H
#define	PWM_H
#define MOTEUR_DROITE 0
#define MOTEUR_GAUCHE 1

void InitPWM(void);
void PWMUpdateSpeed();
void PWMSetSpeedConsigne(unsigned char moteur, float vitesseEnPourcents);
#endif	/* PWM_H */

