#include "i2c.h"

void i2c_init(void)
{
    //set SCL to 400kHz / 12 @16mhz
	//set SCL to 400kHz / 72 @16mhz
    TWSR = 0x00;
	//TWBR = 72;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1<<TWEN);
}

void i2c_start(void)
{
    TWCR = 0;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}
//send stop signal
void i2c_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2c_write(unsigned char u8data)
{
    TWDR = u8data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

unsigned char i2c_read_ack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}
//read byte with NACK
unsigned char i2c_read_nack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

unsigned char i2c_getstatus(void)
{
    uint8_t status;
    //mask status
    status = TWSR & 0xF8;
    return status;
}

//
/*
uint8_t EEWriteByte(uint16_t u16addr, uint8_t u8data)
{
    TWIStart();
    if (TWIGetStatus() != 0x08)
        return ERROR;
    //select devise and send A2 A1 A0 address bits
    TWIWrite((EEDEVADR)|(uint8_t)((u16addr & 0x0700)>>7));
    if (TWIGetStatus() != 0x18)
        return ERROR;  
    //send the rest of address
    TWIWrite((uint8_t)(u16addr));
    if (TWIGetStatus() != 0x28)
        return ERROR;
    //write byte to eeprom
    TWIWrite(u8data);
    if (TWIGetStatus() != 0x28)
        return ERROR;
    TWIStop();
    return SUCCESS;
}

//

uint8_t EEReadByte(uint16_t u16addr, uint8_t *u8data)
{
    //uint8_t databyte;
    TWIStart();
    if (TWIGetStatus() != 0x08)
        return ERROR;
    //select devise and send A2 A1 A0 address bits
    TWIWrite((EEDEVADR)|((uint8_t)((u16addr & 0x0700)>>7)));
    if (TWIGetStatus() != 0x18)
        return ERROR;
    //send the rest of address
    TWIWrite((uint8_t)(u16addr));
    if (TWIGetStatus() != 0x28)
        return ERROR;
    //send start
    TWIStart();
    if (TWIGetStatus() != 0x10)
        return ERROR;
    //select devise and send read bit
    TWIWrite((EEDEVADR)|((uint8_t)((u16addr & 0x0700)>>7))|1);
    if (TWIGetStatus() != 0x40)
        return ERROR;
    *u8data = TWIReadNACK();
    if (TWIGetStatus() != 0x58)
        return ERROR;
    TWIStop();
    return SUCCESS;
}
*/

