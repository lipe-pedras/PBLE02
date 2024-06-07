#include "keypad.h"
#include "event.h"
#include "var.h"
#include "bits.h"
#include "serial.h"
#include <pic18f4550.h>


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


    static unsigned char msg[5];
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
            } else {
                reading_protocol = 0;
                if (msg[0] == 'T') {
                    setTime((msg[1] - 48)*10 * 10 * 10 + (msg[2] - 48)*10 * 10 + (msg[3] - 48)*10 + (msg[4] - 48));
                }

                if (msg[0] == 'L') {
                    setLanguage((msg[1] - 48)*10 * 10 * 10 + (msg[2] - 48)*10 * 10 + (msg[3] - 48)*10 + (msg[4] - 48) % 2);
                }

                if (msg[0] == 'A') {
                    setAlarmLevel((msg[1] - 48)*10 * 10 * 10 + (msg[2] - 48)*10 * 10 + (msg[3] - 48)*10 + (msg[4] - 48));
                }
            }
        }
    }
    return ev;
}
