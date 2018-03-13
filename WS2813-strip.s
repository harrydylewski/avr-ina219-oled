
/*
 * WS2813
 *
 * Created: 14/02/2017 7:28:49 PM
 *  Author: Harry Dylewski
 */ 
  #include <avr/io.h>
	;.include "m328pdef.inc"

	.file "WS2813-strip.s"

	.text
	.global transmit_ws_strip
/*

R: R25:24 
G: R23:22
B: R21:20

PORTX: R19:18
PINX:  R17:16
# of LEDS R15:r14

*/

//FINAL------------------------------------------
transmit_ws_strip:

	cli			  //no interuots during transmission
	movw R30,R18  //move PORT pointer to Z
	
	ld  R19,Z    //replace PORTX's pointer with PORTX's value
	mov R18,R16
	or  R18,R19 // used to preserve PORT values during transmission

	movw R26,R14
	clr R25
	rjmp opt

longexit: 

	st Z,R18	
	rjmp quickexit	

opt: //optimize timing for 0 bit High time

	lsl R20			
	
maincode:

	st Z,R18 ;2
	rol R24 ;3
	rol R22 ;4
	brcs longexit ;5 false/ 6 true

quickexit:

	st Z,R19   ;2	
	adc R20,R1 ;3
	inc R25    ;4
	cpi R25,24 ;5
	brne opt   ;7 true / 6 false	

checkbyte:
	
	clr R25
	sbiw R26,1
	brne opt

endtransmit:

	sei 
	ret
