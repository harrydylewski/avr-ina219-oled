#include <avr/io.h>
//#include "i2c.h"
#include "i2c_inline.h"
#include <stdlib.h>

#ifndef INA219_H
#define INA219_H

//STRUCT------------------------------------------
typedef struct
{
	unsigned int shunt;
	unsigned int current;
	unsigned int bus;
	unsigned int power;
	unsigned int address;
	
} INA219;

typedef struct 
{
	char bus_volt[6];
	char shunt_volt[6];
	char current[6];
	char power[6];

} INA219_STRINGS;
//------------------------------------------------

#define INA219_BAD_READ 0x8000

#define RESET 0x8000

#define CALI_DEFAULT 0x1000 //4096

#define CONFIG_32V 0x2000 //default
#define CONFIG_16V 0x0000

#define CONFIG_40PG  0x0000
#define CONFIG_80PG  0x0800
#define CONFIG_160PG 0x1000
#define CONFIG_320PG 0x1800 //default

#define BADC_SHIFT 7
#define SADC_SHIFT 3

#define INA219_ADD0 0x80 //A1:0 gnd
#define INA219_ADD1 0x82 //A1:GND A0 VS
#define INA219_ADD2 0x84
#define INA219_ADD3 0x86 //
#define INA219_ADD4 0x88 // A1: VS A0: GND
#define INA219_ADD5 0x8A // A1:0 GND
#define INA219_ADD6 0x8C
#define INA219_ADD7 0x8E
#define INA219_ADD8 0x90
#define INA219_ADD9 0x92
#define INA219_ADDA 0x94
#define INA219_ADDB 0x96
#define INA219_ADDC 0x98
#define INA219_ADDD 0x9A
#define INA219_ADDE 0x9C
#define INA219_ADDF 0x9E

//define CONFIG_DEFAULT 0x3E67
#define CONFIG_DEFAULT  (CONFIG_32V | CONFIG_320PG | (CONFIG_12BIT_8SAMP<<BADC_SHIFT) | (CONFIG_12BIT_8SAMP<<SADC_SHIFT) | CONFIG_SBVC )
//ENUM------------------------------------------------------
enum INA219_ADC_MODES
{
CONFIG_9BIT_1SAMP,    
CONFIG_10BIT_1SAMP,   
CONFIG_11BIT_1SAMP,  
CONFIG_12BIT_1SAMP,   //default

CONFIG_12BIT2_1SAMP,  
CONFIG_12BIT_2SAMP,   
CONFIG_12BIT_4SAMP,  
CONFIG_12BIT_8SAMP,   

CONFIG_12BIT_16SAMP, 
CONFIG_12BIT_32SAMP,  
CONFIG_12BIT_64SAMP, 
CONFIG_12BIT_128SAMP 
};

enum INA219_CONFIG_MODES
{
CONFIG_PWRDOWN, 
CONFIG_SVT,     
CONFIG_BST,     
CONFIG_BSVT,    
CONFIG_ADCOFF,  
CONFIG_SVC,     
CONFIG_BVC,     
CONFIG_SBVC     //default
}; 

enum INA219_REGISTERS
{
CONFIG_ADD,
SHUNT_ADD,
VOLT_ADD, 
POWER_ADD,  
CURRENT_ADD,  
CALIBRATION_ADD
};
//--------------------------------------------------------

extern void _utoa10_asm(unsigned int number, char *array);

//BASIC FUNCTIONS
unsigned char ina219_initDefault(unsigned char address); //returns 0 if successfully, 1 if not 
unsigned char ina219_write(unsigned char i2c_address, unsigned char reg_address, unsigned int value); //returns 0 if successfully, 1 if not 
unsigned int  ina219_read(unsigned char i2c_address, unsigned char reg_address); //returns -1 if successfully, 1 if not 
unsigned int  ina219_readContinuous(unsigned char i2c_address, unsigned char reg_address);
//

//
void ina219_resetBuffer(INA219_STRINGS *ptr);

void ina219_readAndConvertAll(INA219 *ptr);
void ina219_writeToStrings(INA219_STRINGS *string_ptr,INA219 *val_ptr);

//

#endif
