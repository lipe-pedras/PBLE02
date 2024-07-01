# 1 "output.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "output.c" 2
# 1 "./output.h" 1
# 11 "./output.h"
void outputInit(void);
void outputPrint(int numTela, int idioma);
# 1 "output.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
void lcdData(unsigned char valor);
void lcdInit(void);
void lcd_write_string(const char *str);
void lcdString(char msg[]);
void lcdInt(int val);
# 2 "output.c" 2

# 1 "./stateMachine.h" 1
# 14 "./stateMachine.h"
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
# 3 "output.c" 2

# 1 "./var.h" 1
# 11 "./var.h"
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
# 4 "output.c" 2





static char * msgs[STATE_FIM][2] = {
    {"Alarme Superior ", "Upper Alarm     "},
    {"Alarme Inferior ", "Lower Alarm     "},
    {"Alterar HORAS   ", "Change HOUR     "},
    {"Alterar MIN     ", "Change MIN      "},
    {"Alterar SEC     ", "Change SEC      "},
    {"Alterar idioma  ", "Change language "},
    {"ALARME ACIONADO!", "ALARM ACTIVATED!"}
};

void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {

    if (numTela == STATE_HOUR) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        char hour, min, sec;
        hour = getHOUR();
        min = getMIN();
        sec = getSEC();
        lcdData((hour / 10) % 10 + 48);
        lcdData(hour % 10 + 48);
        lcdData(':');
        lcdData((min / 10) % 10 + 48);
        lcdData(min % 10 + 48);
        lcdData(':');
        lcdData((sec / 10) % 10 + 48);
        lcdData(sec % 10 + 48);
    }

    if (numTela == STATE_MIN) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        char hour, min, sec;
        hour = getHOUR();
        min = getMIN();
        sec = getSEC();
        lcdData((hour / 10) % 10 + 48);
        lcdData(hour % 10 + 48);
        lcdData(':');
        lcdData((min / 10) % 10 + 48);
        lcdData(min % 10 + 48);
        lcdData(':');
        lcdData((sec / 10) % 10 + 48);
        lcdData(sec % 10 + 48);
    }

    if (numTela == STATE_SEC) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        char hour, min, sec;
        hour = getHOUR();
        min = getMIN();
        sec = getSEC();
        lcdData((hour / 10) % 10 + 48);
        lcdData(hour % 10 + 48);
        lcdData(':');
        lcdData((min / 10) % 10 + 48);
        lcdData(min % 10 + 48);
        lcdData(':');
        lcdData((sec / 10) % 10 + 48);
        lcdData(sec % 10 + 48);
    }

    if (numTela == STATE_ALARM_UPPER) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdInt(getAlarmUpperLevel());
        lcdString("     ");
        lcdInt(getLevel());
    }
    if (numTela == STATE_ALARM_LOWER) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdInt(getAlarmLowerLevel());
        lcdString("     ");
        lcdInt(getLevel());
    }
    if (numTela == STATE_IDIOMA) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        if (getLanguage() == 0) {
            lcdString("Portugues       ");
        }
        if (getLanguage() == 1) {
            lcdString("English         ");
        }

    }
    if (numTela == STATE_OVER_LIMIT) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString("               ");
    }

}
