/* 
 * File:   keypad.h
 * Author: lipedras
 *
 * Created on May 7, 2024, 4:17 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

void kpInit(void);
unsigned char kpRead(void);
void kpDebounce(void);

#endif	/* KEYPAD_H */

