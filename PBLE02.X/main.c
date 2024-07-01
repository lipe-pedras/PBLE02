#include "config.h"
#include "pic18f4520.h"
#include "lcd.h"
#include "keypad.h"
#include "event.h"
#include "var.h"
#include "stateMachine.h"
#include "output.h"
#include "serial.h"

void main(void) {
    
    //init das bibliotecas
    serialInit();
    kpInit();
    lcdInit();
    varInit();
    eventInit();
    outputInit();
            
    
                
    for (;;) {      
        //infraestrutura da placa

        kpDebounce();
        
        //m?quina de estados
        smLoop();
    }

           
}