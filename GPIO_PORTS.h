/*
 * GPIO_PORTS.h
 *
 * Created: 10/03/2025 01:13:32 a. m.
 *  Author: carlos yuen
 */ 

#include "General_Includes.h"
#include "General_Definitions.h"
#include "Interrupts.h"

#ifndef GPIO_PORTS_H_
#define GPIO_PORTS_H_

typedef struct{
	volatile uint8_t PIN;
	volatile uint8_t DDR;
	volatile uint8_t PORT;
}PortReg_t;

#define IOA		((PortReg_t *) 0x20)
#define IOB		((PortReg_t *) 0x23)
#define IOC		((PortReg_t *) 0x26)
#define IOD		((PortReg_t *) 0x29)
#define IOE		((PortReg_t *) 0x2C)
#define IOF		((PortReg_t *) 0x2F)
#define IOG		((PortReg_t *) 0x32)
#define IOH		((PortReg_t *) 0x100)
#define IOJ		((PortReg_t *) 0x103)
#define IOK		((PortReg_t *) 0x106)
#define IOL		((PortReg_t *) 0x109)

#define IOA0	IOA,0
#define IOA1	IOA,1
#define IOA2	IOA,2
#define IOA3	IOA,3
#define IOA4	IOA,4
#define IOA5	IOA,5
#define IOA6	IOA,6
#define IOA7	IOA,7

#define IOB0	IOB,0
#define IOB1	IOB,1
#define IOB2	IOB,2
#define IOB3	IOB,3
#define IOB4	IOB,4
#define IOB5	IOB,5
#define IOB6	IOB,6
#define IOB7	IOB,7

#define IOC0	IOC,0
#define IOC1	IOC,1
#define IOC2	IOC,2
#define IOC3	IOC,3
#define IOC4	IOC,4
#define IOC5	IOC,5
#define IOC6	IOC,6
#define IOC7	IOC,7

#define IOD0	IOD,0
#define IOD1	IOD,1
#define IOD2	IOD,2
#define IOD3	IOD,3
#define IOD4	IOD,4
#define IOD5	IOD,5
#define IOD6	IOD,6
#define IOD7	IOD,7

#define IOE0	IOE,0
#define IOE1	IOE,1
#define IOE2	IOE,2
#define IOE3	IOE,3
#define IOE4	IOE,4
#define IOE5	IOE,5
#define IOE6	IOE,6
#define IOE7	IOE,7

#define IOF0	IOF,0
#define IOF1	IOF,1
#define IOF2	IOF,2
#define IOF3	IOF,3
#define IOF4	IOF,4
#define IOF5	IOF,5
#define IOF6	IOF,6
#define IOF7	IOF,7

#define IOG0	IOG,0
#define IOG1	IOG,1
#define IOG2	IOG,2
#define IOG3	IOG,3
#define IOG4	IOG,4
#define IOG5	IOG,5

#define IOH0	IOH,0
#define IOH1	IOH,1
#define IOH2	IOH,2
#define IOH3	IOH,3
#define IOH4	IOH,4
#define IOH5	IOH,5
#define IOH6	IOH,6
#define IOH7	IOH,7

#define IOJ0	IOJ,0
#define IOJ1	IOJ,1
#define IOJ2	IOJ,2
#define IOJ3	IOJ,3
#define IOJ4	IOJ,4
#define IOJ5	IOJ,5
#define IOJ6	IOJ,6
#define IOJ7	IOJ,7

#define IOK0	IOK,0
#define IOK1	IOK,1
#define IOK2	IOK,2
#define IOK3	IOK,3
#define IOK4	IOK,4
#define IOK5	IOK,5
#define IOK6	IOK,6
#define IOK7	IOK,7

#define IOL0	IOL,0
#define IOL1	IOL,1
#define IOL2	IOL,2
#define IOL3	IOL,3
#define IOL4	IOL,4
#define IOL5	IOL,5
#define IOL6	IOL,6
#define IOL7	IOL,7

#define INPUT			0
#define OUTPUT			1
#define INPUT_PULL_UP	2

#define CHANGE			1
#define FALLING			2
#define RISING			3

#define MAX_NUM_PC_INT	3
#define MAX_NUM_EXT_INT	8

void pinMode(PortReg_t *pPort, uint8_t pin, uint8_t mode);
void portMode(PortReg_t *pPort, uint8_t value);
uint8_t digitalRead(PortReg_t *pPort, uint8_t pin);
uint8_t portRead(PortReg_t *pPort);
void digitalWrite(PortReg_t *pPort, uint8_t pin, uint8_t value);
void portWrite(PortReg_t *pPort, uint8_t value);

void attachInterrupt(uint8_t INTNum, FuncVect UserFunc, uint8_t mode);
void detachInterrupt(uint8_t INTNum);
void attachPCInterrupt(uint8_t INTNum, uint8_t pins, FuncVect UserVect);
void detachPCInterrupt(uint8_t INTNum);

#endif /* GPIO_PORTS_H_ */