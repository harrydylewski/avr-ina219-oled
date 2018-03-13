#include <avr/io.h>
#include <util/twi.h>


#ifndef I2C_H
#define I2C_H

void i2c_init(void);

void i2c_start(void);
void i2c_stop(void);

void i2c_write(unsigned char u8data);

unsigned char i2c_read_ack(void);
unsigned char i2c_read_nack(void);

unsigned char i2c_getstatus(void);

/*
unsigned char EEWriteByte(uint16_t u16addr, uint8_t u8data);
unsigned char EEReadByte(uint16_t u16addr, uint8_t *u8data);
*/
#endif 
