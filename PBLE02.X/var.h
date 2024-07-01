/* 
 * File:   alarme.h
 * Author: Avell
 *
 * Created on 14 de Junho de 2017, 16:10
 */

#ifndef VAR_H
#define	VAR_H

void varInit(void);

int getLevel(void);
void updateLevel(void);
char getState(void);
void setState(char newState);
char getSEC();
void setSEC(char value);
char getMIN();
void setMIN(char value);
char getHOUR();
void setHOUR(char value);
int getAlarmLowerLevel(void);
void setAlarmLowerLevel(int newAlarmLevel);
int getAlarmUpperLevel(void);
void setAlarmUpperLevel(int newAlarmLevel);
char getLanguage(void);
void setLanguage(char newLanguage);
#endif	/* VAR_H */
