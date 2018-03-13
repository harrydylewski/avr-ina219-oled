#include "ATMEGA328p-UART-LIBRARY.H"

char uart_rx(void)
{
	while(!( UCSR0A&(1<<RXC0) ) )
	;
	return UDR0;
}

void uart_tx(char data)
{
	while(!( UCSR0A&(1<<UDRE0) ) )
	;
	
	UDR0=data;	
}

