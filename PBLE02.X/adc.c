#include "adc.h"
#include "bits.h"

void adcInit(void) {
    bitSet(TRISA, 5); // Condigura RA5 como 
    ADCON0 = 0b00010001; // Seleciona o canal 0 (AN0) e liga o ADC
    ADCON1 = 0b00001010; // Apenas AN0, AN3 (RA4) e AN4 (RA5) s�o anal�gicos, refer�ncia baseada na fonte
    ADCON2 = 0b10101010; // FOSC/32, Alinhamento � direita e tempo de convers�o = 12 TAD
}

int adcRead(void) {
    unsigned int ADvalor;
    ADCON0 |= 0b00000010; //inicia conversao

    while (bitTst(ADCON0, 1)); // espera terminar a convers�o;

    ADvalor = ADRESH; // le o resultado
    ADvalor <<= 8;
    ADvalor += ADRESL;
    return ADvalor;
}