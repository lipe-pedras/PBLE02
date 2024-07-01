/* 
 * File:   stateMachine.h
 * Author: Avell
 *
 * Created on 18 de Junho de 2017, 22:17
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H


//estados da maquina de Estados

enum {
    STATE_ALARM_UPPER,
    STATE_ALARM_LOWER,
    STATE_HOUR,
    STATE_MIN,
    STATE_SEC,
    STATE_IDIOMA,
    STATE_OVER_LIMIT,
    STATE_FIM
};


void smInit(void);
void smLoop(void);


#endif	/* STATEMACHINE_H */

