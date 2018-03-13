#define F_CPU 16000000UL

//INCLUDES
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <util/atomic.h>

#include "i2c_inline.h"
#include "ina219.h"
#include "oled_i2c_inline.h"
#include "atmega328p-common.h"


//PROGMEM SRINGS
const char voltage[] PROGMEM = "VOLT:";
const char shunt[] PROGMEM   = "SHNT:";
const char amps[] PROGMEM    = "AMPS:";
const char watts[] PROGMEM   = "WATS:";

extern const char font[] PROGMEM;

//STRUCTS
typedef struct
{
	
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	
} NEOPIXEL;

//FUNCTIONS

void transmit_ws_blank(unsigned char size, volatile unsigned char *port, unsigned char pin);
void transmit_ws_strip(unsigned char r, unsigned char g, unsigned char b, volatile unsigned char *port, unsigned char pin, unsigned int led_bytes);
void update_led(int raw, NEOPIXEL *neo_ptr);
void T1_delay(unsigned int time);

extern void _itoa10_asm(int number, char *array);

//DEFINES
#define TRIMPOT_CHANNEL 0
#define NEOPIXEL_ADC_RESOLUTION 83
#define STRIPSIZE 12 

#define NEOPORT PORTB
#define NEOPIN  2

//ISR
volatile unsigned int countdown;

ISR (TIMER1_OVF_vect)
{
	if(countdown>0)
	countdown--;
}

//--------------------------------------------------------
int main(void)
{
//PERIPHERAL INIT

	DDRB =PINS(0,7); //set all pins to outputs
	DDRC =PINS(1,5); //PC0 is ADC channel
	DDRD =PINS(0,5); 
	
	
	ADC_INIT_REFERENCE(ADC_REF_AREF);
	ADC_INIT_CONFIG(ADC_AUTOTRIGGER_DISABLE,ADC_INT_DISABLE,ADC_PRESCALER128);
	
	TIMER1_INIT_CONFIG(T_COM_DISCONNECT,T_COM_DISCONNECT,T1_MODE_FAST_PWM_ICR1);
	TIMER1_INTERRUPT_ENABLE(DISABLE_INT_COMB,DISABLE_INT_COMA,ENABLE_INT_OVF);
	ICR1=250;	
	
	I2C_INIT();
	
//STRUCT INIT 

	INA219 ina0={0};
	INA219_STRINGS ina0_buffer;
	OLED   oled0;	
	NEOPIXEL neopixel;
	
//VARIABLE INIT

	
	ina219_resetBuffer(&ina0_buffer);
	ina0.address = INA219_ADD0;
	oled0.address = OLED_ADD0;		
	
	unsigned int  input;

	neopixel.green = 255;
	neopixel.red   = 0;
	neopixel.blue  = 255;
	
//IC INIT

	ina219_initDefault(ina0.address);		
	oled_initDefault32(oled0.address);
	
//OLED INIT

	oled_pageAddressScheme(oled0.address);
	oled_selectPageAndColumn(oled0.address,PAGE0,0);
	oled_clearDisplay(oled0.address);	
	
//OLED TEXT INIT

	oled_selectPageAndColumn(oled0.address,PAGE0,0);
	oled_writeFlashToBuffer(voltage,&oled0);
	oled_writeBufferToPage(&oled0);

	oled_selectPageAndColumn(oled0.address,PAGE1,0);
	oled_writeFlashToBuffer(shunt,&oled0);
	oled_writeBufferToPage(&oled0);
	
	oled_selectPageAndColumn(oled0.address,PAGE2,0);	
	oled_writeFlashToBuffer(amps,&oled0);
	oled_writeBufferToPage(&oled0);

	oled_selectPageAndColumn(oled0.address,PAGE3,0);
	oled_writeFlashToBuffer(watts,&oled0);
	oled_writeBufferToPage(&oled0);
	
//MAIN PROGMEM		
	
	while(1)
	{
		input=adc_read(TRIMPOT_CHANNEL);
		update_led(input,&neopixel);	
		
		ina219_readAndConvertAll(&ina0);	
		ina219_writeToStrings(&ina0_buffer,&ina0);
	
		oled_selectPageAndColumn(oled0.address,PAGE0,7*FONT5);	
		oled_writeNumStringToBuffer(ina0_buffer.bus_volt,&oled0);
		oled_writeIntAsFloat(&oled0,2);
		
		oled_selectPageAndColumn(oled0.address,PAGE1,7*FONT5);	
		oled_writeNumStringToBuffer(ina0_buffer.shunt_volt,&oled0);
		oled_writeIntAsFloat(&oled0,3);

		oled_selectPageAndColumn(oled0.address,PAGE2,7*FONT5);	
		oled_writeNumStringToBuffer(ina0_buffer.current,&oled0);
		oled_writeIntAsFloat(&oled0,1);

		oled_selectPageAndColumn(oled0.address,PAGE3,7*FONT5);	
		oled_writeNumStringToBuffer(ina0_buffer.power,&oled0);
		oled_writeIntAsFloat(&oled0,2);	
	
		T1_delay(500); // in ms
	}

}

void T1_delay(unsigned int time)
{	
	countdown=time;
	
	TCNT1=0;
	TIMER1_PRESCALER(T_PRESCALER64);
	
	unsigned int cntdwn_cmp; //countdown compare
		
	do{
			
		ATOMIC_BLOCK(ATOMIC_FORCEON)
		{
			cntdwn_cmp=countdown; //prevent compare mismatch
		}

	}while(cntdwn_cmp!=0);

	TIMER1_DISABLE_PRESCALER();
	TCNT1=0;
}

void update_led(int raw, NEOPIXEL *neo_ptr)
{
	unsigned char led = 0;
	
	while(raw>=NEOPIXEL_ADC_RESOLUTION)
	{
		raw-=NEOPIXEL_ADC_RESOLUTION;
		led++;		
	}	
		
	if(led>0)
	{
		transmit_ws_strip(neo_ptr->red,neo_ptr->green,neo_ptr->blue,&NEOPORT,NEOPIN,led);
		transmit_ws_blank(STRIPSIZE-led,&NEOPORT,NEOPIN);	
	}

	else
	transmit_ws_blank(STRIPSIZE,&NEOPORT,NEOPIN);
	
}	
