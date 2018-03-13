#include <avr/io.h>
#include "avr-macros.h"

#ifndef AVR_SPI_H
#define AVR_SPI_H


#define SPI_PRESCALER2
//choose from 2,4,8,15,32,64,128
#define SPI_MASTER

#define SCK  PB5
#define MISO PB4
#define MOSI PB3
#define SS   PB2

#define SPI_MASTER_MASK ( (1<<SCK) | (1<<MOSI) | (1<<SS) )
#define SPI_SLAVE_MASK  ( (1<<SCK) | (1<<MISO) | (1<<SS) )

#define SPI_SS_MASK ~(1<<SS)

inline void SPI_INIT(void)
{	
	#ifdef SPI_MASTER
	SPCR = (1<<SPE)|(1<<MSTR);
	
	#else
	SPCR = (1<<SPE);
	#endif

	#if defined(SPI_PRESCALER2) ||  defined(SPI_PRESCALER8) || defined(SPI_PRESCALER32) || defined(SPI_PRESCALER64)
	SPSR = 0x01; //turn on double speed bit
	#endif

	#if defined(SPI_PRESCALER8) || defined(SPI_PRESCALER16)
	SPCR |= (1<<SPR0);

	#elif  defined(SPI_PRESCALER64) ||   defined(SPI_PRESCALER32)
	SPCR |= (1<<SPR1);

	#elif  defined(SPI_PRESCALER128) ||  defined(SPI_PRESCALER64)
	SPCR |= (1<<SPR1) | (1<<SPR0);
	#endif
}

void spi_tx(unsigned char data);
unsigned char spi_rx(unsigned char data);

#endif
