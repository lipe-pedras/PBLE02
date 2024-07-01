/* 
 * File:   adc.h
 * Author: lfljp
 *
 * Created on July 1, 2024, 12:13 AM
 */

#ifndef ADC_H
#define ADC_H

#include <pic18f4550.h>
#include "bits.h"

void adcInit(void);
int adcRead(void);

#endif // ADC_H


