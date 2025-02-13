/*
 * IODriver.h
 *
 * Created: 11/02/2025 10:40:20 p. m.
 *  Author: carlos yuen
 */ 


#ifndef IODRIVER_H_
#define IODRIVER_H_

#include "../GeneralIncludes.h"
#include "../GeneralDeclarations.h"


/*
****************************************************
-------------Functions declarations-----------------
****************************************************
*/

void pinMode(char port, uint8_t pin, uint8_t mode);
void portMode(char port, uint8_t mode);
void digitalWrite(char port, uint8_t pin, uint8_t value);
void portWrite(char port, uint8_t value);
uint8_t digitalRead(char port, uint8_t pin);
uint8_t portRead(char port);

#endif /* IODRIVER_H_ */