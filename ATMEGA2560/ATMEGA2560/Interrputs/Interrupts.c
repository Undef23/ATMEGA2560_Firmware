
#include "Interrupts.h"


/*
	NAME: allowInterrupts
	DESCRIPTION:
		Activates the allow interruptions bit in the CPU status
		register, allowing the CPU to take interrupt requests
*/
void allowInterrupts(void){
	sei();
}


/*
	NAME: denyInterrupts
	DESCRIPTION:
		Deactivates the allow interruptions bit in the CPU status
		register, Denying the CPU to take interrupt requests
*/
void denyInterrupts(void){
	cli();
}
