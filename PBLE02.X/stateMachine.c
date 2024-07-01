#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"
#include "serial.h"
#include "adc.h"

#define RELOAD_TIME 700

int flag, level, send, timer;

static char * serial_out[NUM_IDIOMAS] = {"ACIONADO EM ", "ACTIVATED AT ", "ACTIVE A ", "ACTIVADO A "};

void smInit(void) {
    setState(STATE_HOUR);
    flag = 0;
    send = 0;
    timer = 0;
}

void smLoop(void) {
    unsigned char evento;
    
    updateLevel();
    level = getLevel();

    //máquina de estados
    evento = eventRead();

    switch (getState()) {
        case STATE_ALARM_UPPER:
            //execução de atividade
            if (evento == EV_RIGHT) {
                setAlarmUpperLevel(getAlarmUpperLevel() + 1);
            }
            if (evento == EV_LEFT) {
                setAlarmUpperLevel(getAlarmUpperLevel() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARM_LOWER);
            }
            break;
        case STATE_ALARM_LOWER:
            //execução de atividade
            if (evento == EV_RIGHT) {
                setAlarmLowerLevel(getAlarmLowerLevel() + 1);
            }
            if (evento == EV_LEFT) {
                setAlarmLowerLevel(getAlarmLowerLevel() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_HOUR);
            }
            break;
        case STATE_HOUR:

            //execução de atividade
            if (evento == EV_RIGHT) {
                setHOUR(getHOUR() + 1);
            }
            if (evento == EV_LEFT) {
                setHOUR(getHOUR() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_MIN);
            }
            break;
            
        case STATE_MIN:

            //execução de atividade
            if (evento == EV_RIGHT) {
                setMIN(getMIN() + 1);
            }
            if (evento == EV_LEFT) {
                setMIN(getMIN() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_SEC);
            }
            break;
            
        case STATE_SEC:

            //execução de atividade
            if (evento == EV_RIGHT) {
                setSEC(getSEC() + 1);
            }
            if (evento == EV_LEFT) {
                setSEC(getSEC() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_IDIOMA);
            }
            break;

        case STATE_IDIOMA:

            //execução de atividade
            if (evento == EV_RIGHT) {
                setLanguage(getLanguage() + 1);
            }
            if (evento == EV_LEFT) {
                setLanguage(getLanguage() - 1);
            }

            //gestão da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARM_UPPER);
            }
            break;

        case STATE_OVER_LIMIT:
            if ((evento != EV_NOEVENT) && (flag > 0)) {
                setState(STATE_ALARM_UPPER);
                flag = 0;
                send = 0;
                timer = RELOAD_TIME;
            } else if ((evento != EV_NOEVENT) && (flag < 0)) {
                setState(STATE_ALARM_LOWER);
                flag = 0;
                send = 0;
                timer = RELOAD_TIME;
            }
            
            updateLevel();
            if (flag > 0 && getLevel() < getAlarmUpperLevel())
            {
                setState(STATE_ALARM_UPPER);
                timer = 0;
            }
            if (flag < 0 && getLevel() > getAlarmLowerLevel())
            {
                setState(STATE_ALARM_LOWER);
                timer = 0;
            }
    }
    outputPrint(getState(), getLanguage());
    

    if ((level <= getAlarmLowerLevel()) && (timer == 0)) {
        setState(STATE_OVER_LIMIT);
        flag = -1;
        timer = RELOAD_TIME;
        if (!send) {
            serialSendString(serial_out[getLanguage()]);
            serialSendInt(getHOUR());
            serialSend(':');
            serialSendInt(getMIN());
            serialSend(':');
            serialSendInt(getSEC());
            send = 1;
        }
    } else if ((level >= getAlarmUpperLevel()) && (timer == 0)) {
        setState(STATE_OVER_LIMIT);
        flag = 1;
        timer = RELOAD_TIME;
        if (!send) {
            serialSendString(serial_out[getLanguage()]);
            serialSendInt(getHOUR());
            serialSend(':');
            serialSendInt(getMIN());
            serialSend(':');
            serialSendInt(getSEC());
            send = 1;
        }
    }
    if (timer > 0) {
        timer--;
    } else {
        send = 0;
    }
}
