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

void i2c_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void i2c_write(unsigned char data)
{
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

unsigned char i2c_read_ack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

unsigned char i2c_read_nack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

unsigned char i2c_getstatus(void)
{
    unsigned char status = TWSR & 0xF8;
    return status;
}
