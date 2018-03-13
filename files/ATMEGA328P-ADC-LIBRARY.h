#include <avr/io.h>
#include "avr-macros.h"

#ifndef AVRADC_H
#define AVRADC_H

/*

Analog Comparator:

ADCSRB - enables Analog comparator/selects autotrigger source
ACSR   - disable analog compare, other analog comparator features
DIDR0 - disable digital buffers

ADMUX - chooses adc reference, chooses ADC channel for conversion, chooses ADC endianness
ADCSRA - enable ADC, enable ADC int, enable adc autotrigger, chooses adc prescaler


*/
	
enum ADC_REFERENCE
{
	ADC_REF_AREF,
	ADC_REF_AVCC,
	ADC_REF_RESERVED,
	ADC_REF_INTERNAL11V	
};

enum ADC_CHANNELS
{
	ADC_CHANNEL0,
	ADC_CHANNEL1,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7,
	ADC_CHANNEL_TEMPERATURE,
	ADC_CHANNEL_RESERVED0,
	ADC_CHANNEL_RESERVED1,
	ADC_CHANNEL_RESERVED2,
	ADC_CHANNEL_RESERVED3,
	ADC_CHANNEL_RESERVED4,
	ADC_CHANNEL_11V,
	ADC_CHANNEL_GND
};

enum ADC_PRESCALER
{
	ADC_PRESCALER0,
	ADC_PRESCALER2,
	ADC_PRESCALER4,
	ADC_PRESCALER8,
	ADC_PRESCALER16,
	ADC_PRESCALER32,
	ADC_PRESCALER64,
	ADC_PRESCALER128
};

enum ADC_INTERRUPT
{
	ADC_INT_DISABLE,
	ADC_INT_ENABLE
};

enum ADC_AUTOTRIGGER_STATUS
{
	ADC_AUTOTRIGGER_DISABLE,
	ADC_AUTOTRIGGER_ENABLE
};

enum ADC_AUTOTRIGGER
{
	ADC_FREERUN,
	ADC_ANALOG_COMP,
	ADC_EXT_INT0,
	ADC_T0_COMA,
	ADC_T0_OVF,
	ADC_T1_COMB,
	ADC_T1_OVF,
	ADC_T1_CAPTURE
};


#define ADC_AC_MASK 0x40

#define ADC_START_CONVERSION() ADCSRA |= (1<<ADSC)
#define ADC_WAIT_CONVERSION() while(!(ADCSRA&(1<<ADIF)))

#define ADC_RIGHTADJUST()         ADMUX &=~ (0<<ADLAR)
#define ADC_LEFTADJUST()          ADMUX &=~ (1<<ADLAR)
#define ADC_STOP_CONVERSION()     ADCSRA &=~ (1<<ADEN) 
#define ADC_DISABLE()             ADCSRA = 0 
#define ANALOG_COMPARATOR_DISABLE() ACSR = (1<<ACD)


unsigned int adc_read(unsigned char channel);

inline void ADC_INIT_REFERENCE(enum ADC_REFERENCE reference)
{
     ADMUX = reference<<6;
}

inline void ADC_INIT_CONFIG(bool ADC_TRIGGER_SOURCE, bool ADC_INTERRUPT_STATUS, enum ADC_PRESCALER prescaler) 
{
	ADCSRA = (1<<ADEN) | (ADC_TRIGGER_SOURCE<<ADATE) | (ADC_INTERRUPT_STATUS<<ADIE) | prescaler;
}

inline void ADC_AUTOTRIGGER_SOURCE(enum ADC_AUTOTRIGGER source) 
{
	ADCSRB = (ADCSRB&ADC_AC_MASK) | source;
}


/*
ADC_INIT_REFERENCE(ADC_REF_AREF);
ADC_INIT_CONFIG(ADC_AUTOTRIGGER_DISABLE,ADC_INT_DISABLE,ADC_PRESCALER128); 
*/


#endif