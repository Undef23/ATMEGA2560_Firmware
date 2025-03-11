
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "General_Includes.h"
#include "General_Definitions.h"

//Define a pointer to function type
typedef void (*FuncVect)(void);

//General use functions to allow o deny interrupts
void allowInterrupts(void);
void denyInterrupts(void);

#endif /* INTERRUPTS_H_ */