#ifndef ROBOT_H
#define ROBOT_H

typedef struct robotStateBITS {
    unsigned char taskEnCours;
    float vitesseExtremeGaucheConsigne;
    float vitesseExtremeGaucheCommandeCourante;
    float vitesseGaucheConsigne;
    float vitesseGaucheCommandeCourante;
    float vitesseDroiteConsigne;
    float vitesseDroiteCommandeCourante;
    float vitesseExtremeDroiteConsigne;
    float vitesseExtremeDroiteCommandeCourante;
    float distanceTelemetreExtremeGauche;
    float distanceTelemetreGauche;
    float distanceTelemetreCentre;
    float distanceTelemetreDroit;
    float distanceTelemetreExtremeDroite;
} ROBOT_STATE_BITS;

extern volatile ROBOT_STATE_BITS robotState;
void PWMUpdateSpeed();
#endif /* ROBOT_H */
