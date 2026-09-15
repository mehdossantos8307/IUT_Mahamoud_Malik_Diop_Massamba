/* 
 * File:   ADC.h
 * Author: E306_PC1
 *
 * Created on 15 septembre 2026, 16:26
 */

#ifndef ADC_H
#define	ADC_H

void InitADC1(void);
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void);
void ADC1StartConversionSequence();
unsigned char ADCIsConversionFinished(void);
void ADCClearConversionFinishedFlag(void);


#endif	/* ADC_H */

