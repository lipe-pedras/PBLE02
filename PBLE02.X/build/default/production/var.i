# 1 "var.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "var.c" 2
# 1 "./var.h" 1
# 11 "./var.h"
void varInit(void);

char getState(void);
void setState(char newState);
int getTime(void);
void setTime(int newTime);
int getAlarmLevel(void);
void setAlarmLevel(int newAlarmLevel);
char getLanguage(void);
void setLanguage(char newLanguage);
# 1 "var.c" 2

# 1 "./ds1307.h" 1
# 14 "./ds1307.h"
 void dsInit(void);
 void dsStartClock(void);
 void dsStopClock(void);
 int dec2bcd(int value);
 int bcd2dec(int value);
 void dsWriteData(unsigned char value, int address);
 int dsReadData(int address);
# 2 "var.c" 2


# 1 "./lcd.h" 1
# 23 "./lcd.h"
void lcdCommand(unsigned char cmd);

void lcdCommand4bits(unsigned char cmd, unsigned char data);
void lcdData(unsigned char valor);
void lcdInit(void);
void lcd_write_string(const char *str);
void lcdString(char msg[]);
void lcdInt(int val);
# 4 "var.c" 2
# 13 "var.c"
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
    a = dsReadData(0x00);
    b = dsReadData(0x01);
    return (a<<8) | b;
}

void setTime(int newTime) {
    static unsigned char a, b;
    a = (dec2bcd(newTime)>>8) & 0xFF;
    b = dec2bcd(newTime) & 0xFF;
    dsWriteData(a, 0x00);
    dsWriteData(b, 0x01);
}


int getAlarmLevel(void) {
    unsigned static char a, b;
    a = dsReadData(0x04);
    b = dsReadData(0x05);
    lcdCommand(0xC0);
    lcdInt(a);
    lcdInt(b);
    return (a<<8) | b;
}
void setAlarmLevel(int newAlarmLevel) {
    static unsigned char a, b;
    a = (newAlarmLevel>>8);
    b = newAlarmLevel;
    dsWriteData(a, 0x04);
    dsWriteData(b, 0x05);
}



char getLanguage(void){
    return dsReadData(0x06);
}
void setLanguage(char newLanguage){


    language = newLanguage%2;
    dsWriteData(language, 0x06);
}
