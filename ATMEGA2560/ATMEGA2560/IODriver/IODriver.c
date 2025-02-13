
#include "IODriver.h"

/* 
	Name: pinMode
	Parameters:
		char port	 : Receive the port letter
		uint8_t pin  : Receive the pin number
		uint8_t mode : Receives the mode in witch the pin will operate
	Description:	 : Configures a pin as:
						INPUT:			Digital input
						OUTPUT:			Digital Output
						INPUT_PULL_UP:	Digital input whit pull up resistor
*/
void pinMode(char port, uint8_t pin, uint8_t mode){
	
	//Stores the memory address of the port
	volatile uint8_t* ddr;

	//Loads the port address
	switch(port){
		default: return;
		case 'A': ddr = &DDRA; break;
		case 'B': ddr = &DDRB; break;
		case 'C': ddr = &DDRC; break;
		case 'D': ddr = &DDRD; break;
		case 'E': ddr = &DDRE; break;
		case 'F': ddr = &DDRF; break;
		case 'G': ddr = &DDRG; break;
		case 'H': ddr = &DDRH; break;
		case 'J': ddr = &DDRJ; break;
		case 'K': ddr = &DDRK; break;
		case 'L': ddr = &DDRL; break;
	}
	
	//Verify if the pin exists
	if(port == 'G'){
		if(pin > 5) return;
	}
	if(pin > 8) return;

	//set the pin in the desired mode
	if (mode == OUTPUT){
		*ddr |= (1 << pin);
	} else if (mode == INPUT){
		*ddr &= ~(1 << pin);
	} else if(mode == INPUT_PULL_UP){
		*ddr &= ~(1 << pin);
		digitalWrite(port, pin, HIGH);
	} else return;
	
	return;
}

/* 
	Name: portMode
	Parameters:
		char port	 : Receive the port letter
		uint8_t mode : Receives the mode in witch the pin will operate
	Description:	 : Configures an entire port to a value specified by the user
*/
void portMode(char port, uint8_t mode){

	//Loads the mode to the port address
	switch(port){
		default: return;
		case 'A': DDRA = mode; break;
		case 'B': DDRB = mode; break;
		case 'C': DDRC = mode; break;
		case 'D': DDRD = mode; break;
		case 'E': DDRE = mode; break;
		case 'F': DDRF = mode; break;
		case 'G': DDRG = mode; break;
		case 'H': DDRH = mode; break;
		case 'J': DDRJ = mode; break;
		case 'K': DDRK = mode; break;
		case 'L': DDRL = mode; break;
	}
	
	return;
}

/* 
	Name: digitalWrite
	Parameters:
		char port	 : Receive the port letter
		uint8_t pin  : Receive the pin number
		uint8_t value: Receives the value in witch the pin will be set
	Description:	 : Configures a pin as LOW or HIGH
*/
void digitalWrite(char port, uint8_t pin, uint8_t value){
	
	//Stores the memory address of the port
	volatile uint8_t* portReg;
	
	//Loads the port address
	switch(port){
		default: return;
		case 'A': portReg = &PORTA; break;
		case 'B': portReg = &PORTB; break;
		case 'C': portReg = &PORTC; break;
		case 'D': portReg = &PORTD; break;
		case 'E': portReg = &PORTE; break;
		case 'F': portReg = &PORTF; break;
		case 'G': portReg = &PORTG; break;
		case 'H': portReg = &PORTH; break;
		case 'J': portReg = &PORTJ; break;
		case 'K': portReg = &PORTK; break;
		case 'L': portReg = &PORTL; break;
	}
	
	//Verify if the pin exists
	if(port == 'G'){
		if(pin > 5) return;
	}
	if(pin > 8) return;
	
	//set the pin in the desired mode
	if(value == HIGH) *portReg |= (1 << pin);
	else if(value == LOW) *portReg &= ~(1 << pin);
	else return;
	
	return;
}

/* 
	Name: portWrite
	Parameters:
		char port	 : Receive the port letter
		uint8_t value: Receives the value in witch the port will be set
	Description:	 : Configures an entire port to a value specified by the user
*/
void portWrite(char port, uint8_t value){
	
	//Loads the value to the port address
	switch(port){
		default: return;
		case 'A': PORTA = value; break;
		case 'B': PORTB = value; break;
		case 'C': PORTC = value; break;
		case 'D': PORTD = value; break;
		case 'E': PORTE = value; break;
		case 'F': PORTF = value; break;
		case 'G': PORTG = value; break;
		case 'H': PORTH = value; break;
		case 'J': PORTJ = value; break;
		case 'K': PORTK = value; break;
		case 'L': PORTL = value; break;
	}
	
	return;
}

/* 
	Name: digitalRead
	Parameters:
		char port	 : Receive the port letter
		uint8_t pin  : Receive the pin number
	Description:	 : Reads the value of the pin and returns if the pin is HIGH or LOW
*/
uint8_t digitalRead(char port, uint8_t pin){
	
	//Stores the memory address of the port
	volatile uint8_t* pinReg;
	
	//Loads the port address
	switch(port){
		default: return LOW;
		case 'A': pinReg = &PINA; break;
		case 'B': pinReg = &PINB; break;
		case 'C': pinReg = &PINC; break;
		case 'D': pinReg = &PIND; break;
		case 'E': pinReg = &PINE; break;
		case 'F': pinReg = &PINF; break;
		case 'G': pinReg = &PING; break;
		case 'H': pinReg = &PINH; break;
		case 'J': pinReg = &PINJ; break;
		case 'K': pinReg = &PINK; break;
		case 'L': pinReg = &PINL; break;
	}
	
	//Verify if the pin exists
	if(port == 'G'){
		if(pin > 5) return LOW;
	}
	if(pin > 8) return LOW;
	
	//Return the value of the pin
	return (*pinReg & (1 << pin)) ? HIGH : LOW;
}

/* 
	Name: portRead
	Parameters:
		char port	 : Receive the port letter
	Description:	 : Returns the value of the entire port
*/
uint8_t portRead(char port){
	 
	 //Reads and returns the value of the port
	switch(port){
		default: return 0;
		case 'A': return PINA;
		case 'B': return PINB;
		case 'C': return PINC;
		case 'D': return PIND;
		case 'E': return PINE;
		case 'F': return PINF;
		case 'G': return PING;
		case 'H': return PINH;
		case 'J': return PINJ;
		case 'K': return PINK;
		case 'L': return PINL;
	}
	
}