#include "ATMEGA328P-SPI-LIBRARY.h"

void spi_tx(unsigned char data)
{

	SPDR = data;

	while(!(SPSR & (1<<SPIF)))
 	;
 
}

unsigned char spi_rx(unsigned char data)
{

	SPDR = data;

	while(!(SPSR & (1<<SPIF)))
 	;

	return(SPDR);

}




