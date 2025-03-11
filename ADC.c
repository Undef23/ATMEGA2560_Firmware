/*
 * ADC.c
 *
 * Created: 21/02/2025 07:05:26 p. m.
 *  Author: carlos yuen
 */ 

#include "ADC.h"

/*
************************************************************
-------------------Basic ADC commands-----------------------
************************************************************
*/

/*
	Name:	ADCInit
	Parameters:
		cpuFreq:	Receives the frequency of the CPU
	Description:
		initializes the ADC converter with basic functionality
		that means no interrupts and no auto trigger
*/
void ADCInit(uint32_t cpuFreq){
	
	//Set the reference to VCC
	ADC_SetAref(AVCC);
	
	//Set to right adjust
	ADC_SetJustify(ADCLEFT);
	
	//Set the pre-scaler
	ADC_AutoSetPrescaler(cpuFreq);
	
	//Enable the ADC
	ADC_Enable();
	
	//Do a dummy conversion to initialize the ADC hardware
	analogRead(V1_1);
	
}

/*
	Name:	analogRead
	Parameters :
		channel:	Receives the analog channel to read
	Description:
		starts the ADC convention on the channel given by "channel" and returns
		his value
*/
uint16_t analogRead(uint8_t channel){
	
	//Set the channel as an analog input
	ADC_SetAnalogPin(channel);
	
	//Select the ADC channel
	ADC_SetChannel(channel);
	
	//Start the conversion
	ADC_Convert();
	
	//Wait for the ADC to finish
	while((ADCSRA >> ADSC) & 0x01);
	
	//Read and return the conversion
	return ADC_GetValue();
	
}

/*
************************************************************
-----------------Advanced ADC commands----------------------
************************************************************
*/

/*
	Name:	ADC_SetAref
	Parameters:
		ref:	receives the reference for the ADC
	Description:
		Sets the ADC reference voltage to:
			AREF			:	Externally connected to AREF pin
			AVCC			:	VCC supply voltage
			INTERNAL_1V1	:	Internal 1.1 Volts reference
			INTERNAL_2V56	:	Internal 2.56 Volts reference
*/
void ADC_SetAref(uint8_t ref){
	ADMUX &= ~(0b11 << REFS0);
	ADMUX |= (ref & 0x03) << REFS0;
}

/*
	Name:	ADC_SetJustiffy
	Parameters:
		adjust:		Receives the justify of the ADC register
	Description:
		Sets the justify to:
			ADCLEFT		:	Left justified
			ADCRIGHT	:	Right Justified
*/
void ADC_SetJustify(uint8_t adjust){
	ADMUX &= ~(0b1 << ADLAR);
	ADMUX |= (adjust & 0x01) << ADLAR;
}


/*
	Name:	ADC_Enable
	Description:
		Enables the ADC
*/
void ADC_Enable(void){
	ADCSRA |= 1 << ADEN;
}

/*
	Name:	ADC_Disable
	Description:
		Disable the ADC
*/
void ADC_Disable(void){
	ADCSRA &= ~(1 << ADEN);
}

/*
	Name:	ADC_Convert
	Description:
		Starts the ADC convention but it doesn't give the value
*/
void ADC_Convert(void){
	ADCSRA |= 1 << ADSC;
}

/*
	Name:	ADC_SetAutotrigger
	Parameters:
		source:	Receives the source of the auto trigger
	Description:
		Sets the auto trigger function of the ADC to:
			FREE_RUN			:	Starts the conversion as soon as the previous one is completed
			ANALOG_COMPARATOR	:	Starts the conversion with an analog comparator event
			EXTERNAL_INT0		:	Starts the conversion with an external interrupt 0 event
			TMR0_COMPARE_A		:	Starts the conversion with a timer 0 compare A event
			TMR0_OVERFLOW		:	Starts the conversion with a timer 0 overflow event
			TMR1_COMPARE_B		:	Starts the conversion with a timer 1 compare B event
			TMR1_OVERFLOW		:	Starts the conversion with a timer 1 overflow event
			TMR1_CAPTURE		:	Starts the conversion with a timer 1 capture event
			NO_AUTOTRIGGER		:	Disables the auto trigger
*/
void ADC_SetAutotrigger(uint8_t source){
	if(source == NO_AUTOTRIGGER){
		//disable the auto trigger
		ADCSRA &= ~(1 << ADATE);
	} else{
		//Enables and sets the auto trigger source
		ADCSRA |= 1 << ADATE;
		ADCSRB &= ~(0b111);
		ADCSRB |= (source & 0b111);
	}
}

/*
	Name:	ADC_EnableInterrupt
	Parameters:
		userFunc:	Receives the function to be executed when the interrupt occurs
	Description:
		Allows the ADC to cause an interrupt when the conversion is done and
		executes the function given by "userfunc"
*/
static FuncVect adcFuncVect;
void ADC_EnableInterrupt(FuncVect userFunc){
	ADCSRA |= 1 << ADIE;
	adcFuncVect = userFunc;
}
ISR(ADC_vect){
	if(adcFuncVect != NULL){
		adcFuncVect();
	}
}

/*
	Name:	ADC_DisableInterrupt
	Description:
		Denies the ADC interrupt requests
*/
void ADC_DisableInterrupt(void){
	ADCSRA &= ~(1 << ADIE);
	adcFuncVect = NULL;
}

/*
	Name:	ADC_AutoSetPrescaler
	Parameters:
		cpuFreq:	receives the frequency of the CPU
	Description:
		Automatically set the prescaler to an acceptable operating
		frequency
*/
void ADC_AutoSetPrescaler(uint32_t cpuFreq){
	//Holder for the prescaler values
	uint8_t values[8] = {2, 2, 4, 8, 16, 32, 64, 128};
	uint8_t i = 0;
	//Find the pre-scaler for a frequency between 50 kHz and 200 kHz
	while(((cpuFreq / values[i]) < 50000) || ((cpuFreq / values[i]) > 200000)) i++;
	//Load the value
	ADCSRA &= ~(0b111);
	ADCSRA |= (i & 0b111);
}

/*
	Name:	ADC_SetPrescaler
	Parameters:
		prescaler:	receives the desired prescaler value
	Description:
		Sets the ADC prescaler to:
			SCALEX2		:	Division factor of 2
			SCALEX4		:	Division factor of 4
			SCALEX8		:	Division factor of 8
			SCALEX16	:	Division factor of 16
			SCALEX32	:	Division factor of 32
			SCALEX64	:	Division factor of 64
			SCALEX128	:	Division factor of 128
*/
void ADC_SetPrescaler(uint8_t prescaler){
	ADCSRA &= ~(0b111);
	ADCSRA |= (prescaler & 0b111);
}

/*
	Name:	ADC_GetValue
	Description:
		Gives the value of the previous conversion
*/
uint16_t ADC_GetValue(void){
	uint16_t value = ADCL;
	value |= ADCH << 8;
	return value;
}

/*
	Name:	ADC_SetAnalogPin
	Parameters:
		pin:	receives the analog channel to set as analog input
	Description:
		Sets the desired analog channel to be analog
*/
void ADC_SetAnalogPin(uint8_t pin){
	//Set the pin as an analog input
	if((pin != V1_1) || (pin != V0)){
		if(pin <= AC7){
			DIDR0 |= 1 << pin;
			} else if((pin >= AC8) && (pin <= AC15)){
			DIDR2 |= 1 << (pin - 0x20);
		}
	}
}

/*
	Name:	ADC_SetDigitalPin
	Parameters:
		pin:	receives the analog channel to set as digital pin
	Description:
		Sets the desired analog channel to be digital
*/
void ADC_SetDigitalPin(uint8_t pin){
	//Set the pin as an analog input
	if((pin != V1_1) || (pin != V0)){
		if(pin <= AC7){
			DIDR0 &= ~(1 << pin);
			} else if((pin >= AC8) && (pin <= AC15)){
			DIDR2 &= ~(1 << (pin - 0x20));
		}
	}
}

/*
	Name:	ADC_SetChannel
	Parameters:
		channel:	receives the ADC channel to make the conversion
	Description:
		Sets the ADC channel to make the conversion
*/
void ADC_SetChannel(uint8_t channel){
	//Select the ADC channel
	ADMUX &= ~(0x1F);
	ADCSRB &= ~(1 << MUX5);
	ADMUX |= (channel & 0x1F);
	ADCSRB |= (channel & 0x20) >> 2;
}