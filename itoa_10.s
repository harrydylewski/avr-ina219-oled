#include <avr/io.h>
	

	.file "itoa_10.s"

	.text

	.global itoa_10
                                    
//global extern void itoa(unsigned int number, unsigned char array);

//-----------------------------------
itoa_10:

	//r25:24   - number to breakdown
	
	movw R26,R22
	ldi R22,'0'
	
	/*
	ldi R23,5
	mov R0,R23
	*/
	clr R23

	
	/*
	ldi R30,pm_lo8(startijmp)
	ldi R31,pm_hi8(startijmp)
	
	rjmp load_tenk
	*/
loop:

	
	rcall load_tenk
	rcall load_onek
	clr R21
	rcall load_hund
	rcall load_ten

	//ldi R20,1
	//rcall comparechar

endfunc:
	add R24,R22
	st x+,R24
	st x+,R1
	ret	

/*
	dec R0
startijmp:
	breq end
	adiw R30,3
	ijmp  

load_onek:
	ldi R21,0x03
	ldi R20,0xE8
	rjmp compareint
load_hund:
	ldi R20,100
	clr R21
	rjmp compareint	
load_ten:
	ldi R20,10
	clr R21
	rjmp compareint	
load_one:
	ldi R20,1
	clr R21
	rjmp compareint	
	*/

load_ten:
	ldi R20,10
	rjmp comparechar

load_hund:
	ldi R20,100
	rjmp compareint

load_onek:
	ldi R21,0x03
	ldi R20,0xE8
	rjmp compareint
	
	
load_tenk:

	ldi R21,0x27
	ldi R20,0x10

compareint:

	cp  R24,R20
	cpc R25,R21
	brlo endcheck

	inc R23	
	sub R24,R20
	sbc R25,R21

	rjmp compareint

endcheck:
	add R23,R22
	st x+,R23
	clr R23
	ret	

comparechar:
	
	cp R24,R20
	brlo endcheck

	inc R23
	sub R24,R20
	rjmp comparechar 


