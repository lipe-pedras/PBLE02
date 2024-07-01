// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: serial.c
//            Biblioteca da porta serial (USART) do PIC18F4520
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "serial.h"
#include <pic18f4520.h>

#define BitSet(arg,bit) ((arg) |= (1<<bit))
#define BitClr(arg,bit) ((arg) &= ~(1<<bit)) 
#define BitFlp(arg,bit) ((arg) ^= (1<<bit)) 
#define BitTst(arg,bit) ((arg) & (1<<bit)) 

void serialSend(unsigned char c) {
    while (!BitTst(PIR1, 4)); //aguarda o registro ficar disponível
    TXREG = c; //coloca o valor para ser enviado
}

void serialSendString(const char *str) {
    while (*str) {
        serialSend(*str++);
    }
}

void intToStr(int value, char *buffer) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed for 0
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    // Process individual digits
    while (value != 0) {
        int digit = value % 10;
        buffer[i++] = digit + '0';
        value = value / 10;
    }

    // If the number was negative, add the negative sign
    if (isNegative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // Null-terminate the string

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

void serialSendInt(int value) {
    char buffer[12]; // Buffer to hold the string representation of the integer
    intToStr(value, buffer); // Convert the integer to a string
    serialSendString(buffer); // Send the string
}

unsigned char serialRead(void) {
    char resp = 0;

    if (BitTst(RCSTA, 1)) //Verifica se há erro de overrun e reseta a serial
    {
        BitClr(RCSTA, 4);
        BitSet(RCSTA, 4);
    }

    if (BitTst(PIR1, 5)) //Verifica se existe algum valor disponivel
    {
        resp = RCREG; //retorna o valor
    }
    return resp; //retorna zero


}

void serialInit(void) {
    TXSTA = 0b00101100; //configura a transmissão de dados da serial
    RCSTA = 0b10010000; //configura a recepção de dados da serial
    BAUDCON = 0b00001000; //configura sistema de velocidade da serial
    SPBRGH = 0b00000000; //configura para 56k
    SPBRG = 0b00100010; //configura para 56k
    BitSet(TRISC, 6); //pino de recepção de dados
    BitSet(TRISC, 7); //pino de envio de dados
}