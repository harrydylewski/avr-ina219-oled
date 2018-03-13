#include "ATMEGA328P-ADC-LIBRARY.h"

unsigned int adc_read(unsigned char channel)
{
		ADMUX  = (ADMUX&0xF0) | channel;
		ADC_START_CONVERSION(); 
		ADC_WAIT_CONVERSION();
		
		return ADC;		
}
