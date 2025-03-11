/*
 * ATMEGA2560_firmware.c
 *
 * Created: 10/03/2025 01:11:38 a. m.
 * Author : carlos yuen
 */ 

#include "GPIO_PORTS.h"

/*
	Name : pinMode
	Parameters :
		PortReg_t *pPort	: Receives the address of the port
		uint8_t pin			: Receives the pin number
		uint8_t mode		: Receives the mode in witch the pin will operate
	Description	:
		Configures the pin given by "pPort" and "pin" in the given "mode", macros have been
		provided to each parameter.
		Use IOx where "x" is the port letter in capital letters.
			Example "pinMode(IOA, 3, INPUT)" Sets pin 3 of port "A" as an input
		Use IOxy where "x" is the port letter in capital letters and "y" the pin number
			Example "pinMode(IOA3, INPUT)" Sets pin "3" of port "A" as an input
		For mode you can use:
			"INPUT"			:	Sets the pin as an input
			"INPUT_PULL_UP"	:	Sets the pin as an input and activates the pull up resistor
			"OUTPUT"		:	Sets the pin as an output
*/

void pinMode(PortReg_t *pPort, uint8_t pin, uint8_t mode){
	//Determine the mode
	switch(mode){
		//if its not on the list, do nothing
		default: return;
		case INPUT:
			//Set the pin as an input
			pPort->DDR &= ~(1 << pin);
			break;
		case OUTPUT:
			//Set the pin as an output
			pPort->DDR |= 1 << pin;
			break;
		case INPUT_PULL_UP:
			//Set the pin as an input
			pPort->DDR &= ~(1 << pin);
			//Activate the pull up resistor
			pPort->PORT |= 1 << pin;
		break;
	}
}

/*
	Name : portMode
	Parameters :
		PortReg_t *pPort	: Receives the address of the port
		uint8_t value		: Receives the mode for each pin of the port
	Description	:
		Configures the port given by "pPort" and sets the pins as inputs or outputs
		according to "value" where "0" is an input and "1" is an output
		Use IOx macro for "pPort" where "x" is the port letter in capital letters.
			Example "pinMode(IOA, 0xFF)" Sets all the pins in port "A" to outputs
*/
void portMode(PortReg_t *pPort, uint8_t value){
	//Sets the pin directions
	pPort->DDR = value;
}

/*
	Name : digitalRead
	Parameters :
		PortReg_t *pPort	: Receives the address of the port to read
		uint8_t pin			: Receives the pin to read
	Returns:
		"HIGH"	: if the pin state is logical high ("1")
		"LOW"	: if the pin state is logical low ("0")
	Description	:
		Reads a pin state specified by "pin" in the port specified by "pPort".
		Use IOx macro for "pPort" where "x" is the port letter in capital letters.
			Example "digitalRead(IOA, 6)" Reads the state of pin 6 in port "A"
		Use IOxy where "x" is the port letter in capital letters and "y" the pin number
			Example "digitalRead(IOA6)" Reads the state of pin "6" in port "A"
*/
uint8_t digitalRead(PortReg_t *pPort, uint8_t pin){
	//Read the pin state
	uint8_t value = (pPort->PIN >> pin) & 0x01;
	//returns its value
	return value;
}

/*
	Name : portRead
	Parameters :
		PortReg_t *pPort	: Receives the address of the port to read
	Returns:
		The state of the pins of the port
	Description	:
		Reads all the pins in the port given by "pPort".
		Use IOx macro for "pPort" where "x" is the port letter in capital letters.
			Example "portRead(IOA)" Reads the port "A" and returns its value
*/
uint8_t portRead(PortReg_t *pPort){
	return pPort->PIN;
}

/*
	Name : digitalWrite
	Parameters :
		PortReg_t *pPort	: Receives the address of the port
		uint8_t pin			: Receives the pin number
		uint8_t value		: Receives the value to set the pin
	Description	:
		Sets the state of a pin given by "pin" in the port given by "pPort" to a desired state
		given by "value".
		Use IOx macro for "pPort" where "x" is the port letter in capital letters.
			Example "digitalWrite(IOA, 2, HIGH)" Sets the pin 2 in port "A" to high (logical 1)
		Use IOxy where "x" is the port letter in capital letters and "y" the pin number
		Example "digitalWrite(IOA2, LOW)" Sets the pin "2" in port "A" to low (logical 0)
		Use "HIGH" to set the pin to logical 1 or use "LOW" to set the pin to logical 0
*/
void digitalWrite(PortReg_t *pPort, uint8_t pin, uint8_t value){
	//Set the pin to 1 
	if(value == HIGH){
		pPort->PORT |= 1 << pin;
	}
	//Set the pin to 0
	else if(value == LOW){
		pPort->PORT &= ~(1 << pin);
	}
}

/*
	Name : portWrite
	Parameters :
		PortReg_t *pPort	: Receives the address of the port
		uint8_t value		: Receives the value to set the pin
	Description	:
		Sets the state of all the pins in the port given by "pPort" to a desired state
		given by "value".
		Use IOx macro for "pPort" where "x" is the port letter in capital letters.
			Example "digitalWrite(IOA, 0x0F)" Sets the pins 0,1,2 and 3 of port "A" to logical 1
*/
void portWrite(PortReg_t *pPort, uint8_t value){
	pPort->PORT = value;
}

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
void attachPCInterrupt(uint8_t INTNum, uint8_t pins, FuncVect UserVect){
	
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