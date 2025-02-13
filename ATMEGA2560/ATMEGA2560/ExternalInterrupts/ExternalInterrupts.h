
#ifndef EXTERNALINTERRUPTS_H_
#define EXTERNALINTERRUPTS_H_

#include "../GeneralIncludes.h"
#include "../GeneralDeclarations.h"
#include "../Interrputs/Interrupts.h"

void attachInterrupt(uint8_t INTNum, FuncVect UserFunc, uint8_t mode);
void detachInterrupt(uint8_t INTNum);
void atachPCInterrupt(uint8_t INTNum, uint8_t pins, FuncVect UserVect);
void detachPCInterrupt(uint8_t INTNum);

#endif /* EXTERNALINTERRUPTS_H_ */