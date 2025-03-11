/*
 * ADC.h
 *
 * Created: 21/02/2025 07:01:02 p. m.
 *  Author: carlos yuen
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "General_Definitions.h"
#include "General_Includes.h"
#include "Interrupts.h"

#define AC0				0
#define AC1				1
#define AC2				2
#define AC3				3
#define AC4				4
#define AC5				5
#define AC6				6
#define AC7				7
#define D0_0_10X		8
#define D1_0_10X		9
#define D0_0_200X		10
#define D1_0_200X		11
#define D2_2_10X		12
#define D3_2_10X		13
#define D2_2_200X		14
#define D3_2_200X		15
#define D0_1			16
#define D1_1			17
#define D2_1			18
#define D3_1			19
#define D4_1			20
#define D5_1			21
#define D6_1			22
#define D7_1			23
#define D0_2			24
#define D1_2			25
#define D2_2			26
#define D3_2			27
#define D4_2			28
#define D5_2			29
#define V1_1			30
#define V0				31
#define AC8				32
#define AC9				33
#define AC10			34
#define AC11			35
#define AC12			36
#define AC13			37
#define AC14			38
#define AC15			39
#define D8_8_10X		40
#define D9_8_10X		41
#define D8_8_200X		42
#define D9_8_200X		43
#define D10_10_10X		44
#define D11_10_10X		45
#define D10_10_200X		46
#define D11_10_200X		47
#define D8_9			48
#define D9_9			49
#define D10_9			50
#define D11_9			51
#define D12_9			52
#define D13_9			53
#define D14_9			54
#define D15_9			55
#define D8_10			56
#define D9_10			57
#define D10_10			58
#define D11_10			59
#define D12_10			60
#define D13_10			61

#define AREF			0
#define AVCC			1
#define INTERNAL_1V1	2
#define INTERNAL_2V56	3

#define ADCLEFT			0
#define ADCRIGHT		1

#define SCALEX2			1
#define SCALEX4			2
#define SCALEX8			3
#define SCALEX16		4
#define SCALEX32		5
#define SCALEX64		6
#define SCALEX128		7

#define FREE_RUN				0
#define ANALOG_COMPARATOR		1
#define EXTERNAL_INT0			2
#define TMR0_COMPARE_A			3
#define TMR0_OVERFLOW			4
#define TMR1_COMPARE_B			5
#define TMR1_OVERFLOW			6
#define TMR1_CAPTURE			7
#define NO_AUTOTRIGGER			8
/*
enum{
	AC0, AC1, AC2, AC3, AC4, AC5, AC6, AC7,
	V1_1 = 0b011110,
	V0, AC8, AC9, AC10, AC11, AC12, AC13, AC14, AC15
};
*/

void ADCInit(uint32_t cpuFreq);
uint16_t analogRead(uint8_t channel);

void ADC_SetAref(uint8_t ref);
void ADC_SetJustify(uint8_t adjust);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_Convert(void);
void ADC_SetAutotrigger(uint8_t state);
void ADC_EnableInterrupt(FuncVect userFunc);
void ADC_DisableInterrupt(void);
void ADC_AutoSetPrescaler(uint32_t cpuFreq);
void ADC_SetPrescaler(uint8_t prescaler);
uint16_t ADC_GetValue(void);
void ADC_SetAnalogPin(uint8_t pin);
void ADC_SetDigitalPin(uint8_t pin);
void ADC_SetChannel(uint8_t channel);

#endif /* ADC_H_ */