
#include "ExternalInterrupts.h"

/*
************************************************************
---------------External Interrupt Handler-------------------
************************************************************
*/

//Stores the user functions for every interrupt
static FuncVect UserINTVect[MAX_NUM_EXT_INT] = {NULL};

/*
	Name : attachInterrupt
	Parameters :
		uint8_t INTNum		: Receives the number of the interrupt
		FuncVect UserFunc	: Receives the address of the function to execute
		uint8_t mode		: Receives the mode in witch the interrupt will be activated
	Description	:
		Set up the interrupt number defined by "INTNum" in the mode set by "mode"
		When the said interrupt occurs, it will run the function defined by "UserFunc".
		Global interrupts musts be enabled with "allowInterrupts();" in order to work.
*/
void attachInterrupt(uint8_t INTNum, FuncVect UserFunc, uint8_t mode){
	
	//verifies if the interrupt number exists
	if( INTNum > MAX_NUM_EXT_INT) return;
	
	//Stores the size of the shift
	uint8_t shift = INTNum * 2;
	
	//sets the interrupt condition
	if(INTNum < 4){
		//Clear The register
		EICRA &= ~(1 << shift);
		//Loads the condition
		switch(mode){
			default: return;
			case LOW	: EICRA |= 00 << shift; break;
			case CHANGE	: EICRA |= 01 << shift; break;
			case FALLING: EICRA |= 10 << shift; break;
			case RISING	: EICRA |= 11 << shift; break;
				
		}
	} else{
		//Clear the register
		EICRB &= ~(1 << (shift - 8));
		//Loads the condition
		switch(mode){
			default: return;
			case LOW	: EICRB |= 00 << (shift - 8); break;
			case CHANGE	: EICRB |= 01 << (shift - 8); break;
			case FALLING: EICRB |= 10 << (shift - 8); break;
			case RISING	: EICRB |= 11 << (shift - 8); break;
		}
	}
	
	//Loads the function address
	UserINTVect[INTNum] = UserFunc;
	
	//Enables the interrupt
	EIMSK |= 1 << INTNum;
	
	return;
}

/*
	Name : detachInterrupt
	Parameters:
		uint8_t INTNum		: Receives the number of the interrupt
	Description	:
		Deactivates the interrupt said by "INTNum", clears the configuration bits and
		clears the function vector in said address
*/
void detachInterrupt(uint8_t INTNum){
	
	//verifies if the interrupt number exists
	if(INTNum > MAX_NUM_EXT_INT);
	
	uint8_t shift = INTNum * 2;
	
	//Clear the configuration
	if(INTNum < 4 ) EICRA &= ~(11 << shift);
	else EICRB &= ~(11 << shift);
	
	//Mask the interrupt
	EIMSK &= ~(1 << INTNum);
	
	//Erase the function vector
	UserINTVect[INTNum] = NULL;
	
	return;
}

/*
************************************************************
-----------External Interrupt Service Routine---------------
************************************************************
*/
ISR(INT0_vect){
	if(UserINTVect[0] != NULL) UserINTVect[0]();
}
ISR(INT1_vect){
	if(UserINTVect[1] != NULL) UserINTVect[1]();
}
ISR(INT2_vect){
	if(UserINTVect[2] != NULL) UserINTVect[2]();
}
ISR(INT3_vect){
	if(UserINTVect[3] != NULL) UserINTVect[3]();
}
ISR(INT4_vect){
	if(UserINTVect[4] != NULL) UserINTVect[4]();
}
ISR(INT5_vect){
	if(UserINTVect[5] != NULL) UserINTVect[5]();
}
ISR(INT6_vect){
	if(UserINTVect[6] != NULL) UserINTVect[6]();
}
ISR(INT7_vect){
	if(UserINTVect[7] != NULL) UserINTVect[7]();
}
	
/*
************************************************************
--------------Pin Change Interrupt Handler------------------
************************************************************
*/

//Stores the user functions for every pin change interrupt
static FuncVect UserPCINTFunc[MAX_NUM_PC_INT] = {NULL};

/*
	Name : atachPCInterrupt
	Parameters :
		uint8_t INTNum		: Receives the number of the interrupt
		uint8_t pins		: Receives the pins that can cause an interrupt
		FuncVect UserVect	: Receives the function that will be executed
	Description	:
		Set up the pin change interrupt number defined by "INTNum" in the pins said by pins
		(logic ones activates, logic zero deactivates) When the said interrupt occurs, it will 
		run the function defined by "UserFunc". Global interrupts musts be enabled with 
		"allowInterrupts();" in order to work.
*/
void atachPCInterrupt(uint8_t INTNum, uint8_t pins, FuncVect UserVect){
	
	//verifies if the interrupt number exists
	if(INTNum > MAX_NUM_PC_INT) return;
	
	//Activate the PCINT number
	PCICR &= ~(1 << INTNum);
	PCICR |= 1 << INTNum;
	
	//loads the function in the function vector
	UserPCINTFunc[INTNum] = UserVect;
	
	//Allows the pin to cause a PCINT
	switch(INTNum){
		default: return;
		case 0: PCMSK0 = pins;
		case 1: PCMSK1 = pins;
		case 2: PCMSK2 = pins;
	}
	
	return;
}

/*
	Name : detachPCInterrupt
	Parameters :
		uint8_t INTNum		: Receives the number of the interrupt
	Description	:
		Deactivates the interrupt said by "INTNum", clears the configuration bits and
		clears the function vector in said address
*/
void detachPCInterrupt(uint8_t INTNum){
	
	//verifies if the interrupt number exists
	if(INTNum > MAX_NUM_PC_INT) return;
	
	//Clear the configuration
	switch(INTNum){
		default: return;
		case 0: PCMSK0 = 0;
		case 1: PCMSK1 = 0;
		case 2: PCMSK2 = 0;
	}
	
	//Mask the interrupt
	PCICR &= ~(1 << INTNum);
	
	//Clears the function in the function vector
	UserPCINTFunc[INTNum] = NULL;
	
	return;
}

/*
************************************************************
----------Pin change Interrupt Service Routine--------------
************************************************************
*/
ISR(PCINT0_vect){
	if(UserPCINTFunc[0] != NULL) UserPCINTFunc[0]();
}
ISR(PCINT1_vect){
	if(UserPCINTFunc[1] != NULL) UserPCINTFunc[1]();
}
ISR(PCINT2_vect){
	if(UserPCINTFunc[2] != NULL) UserPCINTFunc[2]();
}