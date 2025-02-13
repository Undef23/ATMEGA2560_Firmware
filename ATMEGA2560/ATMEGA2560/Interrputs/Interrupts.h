
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../GeneralIncludes.h"
#include "../GeneralDeclarations.h"

//Define a pointer to function type
typedef (*FuncVect)(void);

//General use functions to allow o deny interrupts
void allowInterrupts(void);
void denyInterrupts(void);

#endif /* INTERRUPTS_H_ */