/********************************
Description: Atmega specific code for itoa function with hardcoded 10 as the radix

function:
extern global void itoa10_asm(unsigned int number, char *array);

number: self explainatory
array: expects char array that is atleast size 6 (array[6])

detailed: standard itoa takes an excessive amount of time and is pretty big
this function reduces execution time by ~72% (59999 as test)
and code size is reduced by ~80%

Default Code size: 152 Bytes
can reduced by getting of LOOP_INT/CHAR
at end of file that are used for unrolling loops
*********************************/
	.file "itoa_10_avr_asm.s"

	.text

	.global itoa10_asm                       

//-----------------------------------

/*

*/

.MACRO LOOP_INT
	cp  R24,R20
	cpc R25,R21
	brlo endcheck
	
	inc R23
	sub R24,R20
	sbc R25,R21

.ENDM

.MACRO LOOP_CHAR
	cp R24,R20
	brlo endcheck

	inc R23
	sub R24,R20
.ENDM

itoa10_asm:

	//r25:24   - number to breakdown
	//r23:22   - array pointer, gets moved to X, and is used function
	
	movw R26,R22
	clr R23

main:

Bin2BCD16:	

		ldi	R23,0xff	;initialize digit 4

binbcd_4:	
		
		inc	    R23		
		subi	R24,0x10    ;low(10000)
		sbci	R25,0x27    ;high(10000)
		brcc	binbcd_4	
		
		subi	r23,-0x30
		st		x+,r23

		ldi	R23,10

binbcd_3:	

		dec   R23	
		subi	R24,0x18    ;low(-1000)
		sbci	R25,0xfc    ;high(-1000)
		brcs	binbcd_3	

		subi	r23,-0x30
		st		x+,r23
		
		ldi	R23,0xff

binbcd_2:	

		inc	    R23	
		subi	R24,0x64    ;low(100)	
		sbci	R25,0x00    ;high(100) 
		brcc	binbcd_2	;

		subi	r23,-0x30
		st		x+,r23

		ldi	R23,10

binbcd_1:	

		dec R23	
		subi	R24,-10		
		brcs	binbcd_1	

		subi	r23,-0x30
		st		x+,r23
		st		x+,r24
		st      x+,r1
save:
	ret

/*
	rcall load_tenk
	rcall load_onek
	clr R21
	rcall load_hund
	rcall load_ten

endfunc:
	subi R24,0xD0 ; add '0', in two's complement
	st x+,R24
	st x+,R1
	ret	

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

	LOOP_INT //r25,r24,r21,r20,r23
	LOOP_INT //R25,R24,R21,R20,R23
	LOOP_INT //R25,R24,R21,R20,R23
	LOOP_INT //R25,R24,R21,R20,R23
	LOOP_INT //R25,R24,R21,R20,R23
	rjmp compareint

endcheck:

	subi R23,0xD0 ; add '0', in two's complement
	st x+,R23
	clr R23
	ret	

comparechar:
	
	LOOP_CHAR
	LOOP_CHAR
	LOOP_CHAR
	LOOP_CHAR
	LOOP_CHAR
	rjmp comparechar 
	*/



