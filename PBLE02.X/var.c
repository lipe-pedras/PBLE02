#include "var.h"
#include "ds1307.h"
#include "output.h"
#include "adc.h"

#define TIME 0x20
#define TIME_1 0x21
#define ALARM_UPPER 0x22
#define ALARM_UPPER_1 0x23
#define ALARM_LOWER 0x24
#define ALARM_LOWER_1 0x25
#define LANG 0x26

//variáveis a serem armazenadas
static char state;
static char language;
static int time;
static int alarmLevel;
static int level;

void varInit(void) {
    dsInit();
    state = 0;
    setLanguage(getLanguage() % NUM_IDIOMAS);
}

int getLevel() {
    return level;
}

void updateLevel() {
    adcInit();
    level = adcRead();
}

char getState(void) {
    return state;
}

void setState(char newState) {
    state = newState;
}

char getSEC(void) {
    return dsReadData(SEC);
}

char getMIN(void) {
    return dsReadData(MIN);
}

char getHOUR(void) {
    return dsReadData(HOUR);
}

void setSEC(char value) {
    if (value > 59) value = 0;
    if (value < 0) value = 59;
    dsWriteData(value, SEC);
}

void setMIN(char value) {
    if (value > 59) value = 0;
    if (value < 0) value = 59;
    dsWriteData(value, MIN);
}

void setHOUR(char value) {
    if (value > 23) value = 0;
    if (value < 0) value = 23;
    dsWriteData(value, HOUR);
}

int getAlarmUpperLevel(void) {
    unsigned static char a, b;
    a = dsReadData(ALARM_UPPER);
    b = dsReadData(ALARM_UPPER_1);
    return (a << 8) | b;
}

void setAlarmUpperLevel(int newAlarmLevel) {
    static unsigned char a, b;
    a = (newAlarmLevel >> 8);
    b = newAlarmLevel;
    dsWriteData(a, ALARM_UPPER);
    dsWriteData(b, ALARM_UPPER_1);
}

int getAlarmLowerLevel(void) {
    unsigned static char a, b;
    a = dsReadData(ALARM_LOWER);
    b = dsReadData(ALARM_LOWER_1);
    return (a << 8) | b;
}

void setAlarmLowerLevel(int newAlarmLevel) {
    static unsigned char a, b;
    a = (newAlarmLevel >> 8);
    b = newAlarmLevel;
    dsWriteData(a, ALARM_LOWER);
    dsWriteData(b, ALARM_LOWER_1);
}

char getLanguage(void) {
    return dsReadData(LANG);
}

void setLanguage(char newLanguage) {
    //só tem 2 linguas
    //usando resto pra evitar colocar valor errado
    language = newLanguage % NUM_IDIOMAS;
    dsWriteData(language, LANG);
}