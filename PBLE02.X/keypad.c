
#include <pic18f4550.h>
#include "bits.h"

static unsigned char tecla = 0x00;

void kpInit(void) {
    /*
     *Portas dos botoes:
     * PORTB, bit 2;
     * PORTB, bit 3;
     * PORTB, bit 4;
     * PORTE, bit 1;
     * PORTB, bit 5; 
     */
    TRISB = 0xff;
    ADCON1 = 0b00001110;
    bitSet(TRISE, 1);
}

unsigned char kpRead(void) {
    return tecla;
}

void kpDebounce(void) {
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned char teclaNew = 0x0000;
    static unsigned char teclaOld = 0x0001;

    if (!bitTst(PORTB, 2)) bitSet(teclaNew, 0);
    else bitClr(teclaNew, 0);

    if (!bitTst(PORTB, 3)) bitSet(teclaNew, 1);
    else bitClr(teclaNew, 1);

    if (!bitTst(PORTB, 5)) bitSet(teclaNew, 2);
    else bitClr(teclaNew, 2);

    if (!bitTst(PORTB, 4)) bitSet(teclaNew, 3);
    else bitClr(teclaNew, 3);
    
    if (!bitTst(PORTE, 1)) bitSet(teclaNew, 4);
    else bitClr(teclaNew, 4);

    if (teclaOld == teclaNew) tempo--;
    else {
        tempo = 10;
        teclaOld = teclaNew;
    }

    if (tempo == 0) tecla = teclaOld;
}
