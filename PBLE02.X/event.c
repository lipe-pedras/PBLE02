#include "keypad.h"
#include "event.h"
#include "var.h"
#include "bits.h"
#include "serial.h"
#include "output.h"
#include <pic18f4550.h>

int pow10(int expoent) {
    int result = 1;
    for (int i = 0; i < expoent; i++) {
        result *= 10;
    }
    return result;
}

static unsigned int key_ant;
static char reading_protocol = 0;

void eventInit(void) {
    kpInit();
    key_ant = 0;
}

unsigned int eventRead(void) {
    int key;
    int ev = EV_NOEVENT;
    key = kpRead();
    if (key != key_ant) {
        if (bitTst(key, 0)) {
            ev = EV_RIGHT;
        }

        if (bitTst(key, 1)) {
            ev = EV_LEFT;
        }

        if (bitTst(key, 2)) {
            ev = EV_ENTER;
        }
    }
    key_ant = key;


    static unsigned char msg[6];
    unsigned char static data;
    data = serialRead();
    if (data != 0) {
        if (reading_protocol) {
            msg[reading_protocol - 1] = data;
            reading_protocol++;
        } else if (data == 'w') ev = EV_ENTER;
        else if (data == 'a') ev = EV_LEFT;
        else if (data == 'd') ev = EV_RIGHT;

        if (data == 'p') {
            if (reading_protocol == 0) {
                reading_protocol = 1;
                for (char i = 0; i < 6; i++) {
                    msg[i] = '0';
                }
            } else {
                unsigned int value = 0;
                for (char i = reading_protocol - 3; i > 0; i--) {                    
                    value += (msg[i] - '0') * pow10(reading_protocol - 3 - i);
                }                

                if (msg[0] == 'H') {
                    setHOUR(value);
                }
                
                if (msg[0] == 'M') {
                    setMIN(value);
                }
                
                if (msg[0] == 'S') {
                    setSEC(value);
                }

                if (msg[0] == 'L') {
                    setLanguage(value % NUM_IDIOMAS);
                }

                if (msg[0] == 'A') {
                    setAlarmUpperLevel(value);
                }

                if (msg[0] == 'a') {
                    setAlarmLowerLevel(value);
                }
                static char envio[7];
                for (char i = 0; i < 6; i++) {
                    envio[i] = msg[i];
                }
                reading_protocol = 0;
            }
        }
    }
    return ev;
}
