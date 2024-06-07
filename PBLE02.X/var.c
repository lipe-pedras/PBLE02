#include "var.h"
#include "ds1307.h"

#include "lcd.h"

#define TIME 0x00
#define TIME_1 0x01
#define ALARM 0x04
#define ALARM_1 0x05
#define LANG 0x06

//variáveis a serem armazenadas
static char state;
static char language;
static int time;
static int alarmLevel;

void varInit(void) {
    dsInit();
    state = 0;
    setTime(0);
    setAlarmLevel(0);
}


char getState(void) {
    return state;
}
void setState(char newState) {
    state = newState;
}

int getTime(void) {
    unsigned static char a, b;
    a = dsReadData(TIME);
    b = dsReadData(TIME_1);
    return (a<<8) | b;
}

void setTime(int newTime) {
    static unsigned char a, b;
    a = (dec2bcd(newTime)>>8) & 0xFF;
    b = dec2bcd(newTime) & 0xFF;
    dsWriteData(a, TIME);
    dsWriteData(b, TIME_1);
}


int getAlarmLevel(void) {
    unsigned static char a, b;
    a = dsReadData(ALARM);
    b = dsReadData(ALARM_1);
    lcdCommand(0xC0);
    lcdInt(a);
    lcdInt(b);
    return (a<<8) | b;
}
void setAlarmLevel(int newAlarmLevel) {
    static unsigned char a, b;
    a = (newAlarmLevel>>8);
    b = newAlarmLevel;
    dsWriteData(a, ALARM);
    dsWriteData(b, ALARM_1);
}



char getLanguage(void){
    return dsReadData(LANG);
}
void setLanguage(char newLanguage){
    //só tem 2 linguas
    //usando resto pra evitar colocar valor errado
    language = newLanguage%2;
    dsWriteData(language, LANG);
}