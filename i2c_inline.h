#include <avr/io.h>
#include <util/twi.h>

#ifndef I2C_INLINE_H
#define I2C_INLINE_H

inline void I2C_INIT(void)
{
    //set SCL to 400kHz / 12 @16mhz
	//set SCL to 400kHz / 72 @16mhz
    TWSR = 0x00;
	//TWBR = 72;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1<<TWEN);
}

inline void i2c_start(void)
{
    TWCR = 0;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}
//send stop signal
inline void i2c_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

inline void i2c_write(unsigned char u8data)
{
    TWDR = u8data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

inline unsigned char i2c_read_ack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while( !(TWCR & (1<<TWINT)) );
    return TWDR;
}
//read byte with NACK
inline unsigned char i2c_read_nack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while( !(TWCR & (1<<TWINT)) );
    return TWDR;
}

unsigned char i2c_getstatus(void);
/*
{
    uint8_t status;
    //mask status
    status = TWSR & 0xF8;
    return status;
}
*/
#endif 
