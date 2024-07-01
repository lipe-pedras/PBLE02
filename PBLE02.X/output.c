#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"


//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[STATE_FIM][NUM_IDIOMAS] = {
    {"Alarme Superior ", "Upper Alarm     ", "Alarme superieur", "Alarma superior "},
    {"Alarme Inferior ", "Lower Alarm     ", "Alarme inferieur", "Alarma inferior "},
    {"Alterar HORAS   ", "Change HOUR     ", "Changer HEURE   ", "Cambiar HORA    "},
    {"Alterar MIN     ", "Change MIN      ", "Changer MINUTE  ", "Cambiar MIN     "},
    {"Alterar SEG     ", "Change SEC      ", "Changer SECONDE ", "Cambiar SEG     "},
    {"Alterar idioma  ", "Change language ", "Changer langue  ", "Cambiar idioma  "},
    {"ALARME ACIONADO!", "ALARM ACTIVATED!", "ALARME ACTIVE ! ", "ALARMA ACTIVADA!"}
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
        lcdString("        ");
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
        lcdString("        ");
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
        lcdString("        ");
    }
    
    if (numTela == STATE_ALARM_UPPER) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdInt(getAlarmUpperLevel());
        lcdString("      ");
        lcdInt(getLevel());
    }
    if (numTela == STATE_ALARM_LOWER) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdInt(getAlarmLowerLevel());
        lcdString("      ");
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
        if (getLanguage() == 2) {
            lcdString("Francaise       ");
        }
        if (getLanguage() == 3) {
            lcdString("Espanol         ");
        }

    }
    if (numTela == STATE_OVER_LIMIT) {
        lcdCommand(0x80);
        lcdString(msgs[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString("                ");
    }

}

