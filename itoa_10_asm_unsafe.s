/********************************
Description: Atmega specific code for itoa function with hardcoded 10 as the radix

function:
extern void itoa10_asm_unsafe(unsigned int number, char *array);

number: self explainatory
array: expects char array that is atleast size 6 (array[6])

detailed: standard itoa takes an excessive amount of time and is pretty big
this function reduces execution time by ~72% (59999 as test)
and code size is reduced by ~80%




*********************************/
	.file "itoa_10_asm_unsafe.s"

	.text

	.global itoa10_asm_unsafe                      

//-----------------------------------
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

itoa10_asm_unsafe:

	//r25:24   - number to breakdown
	//r23:22   - array pointer, gets moved to X, and is used function
	
	movw R26,R22

	clr R23	

	ldi R30,pm_lo8(compareint)
	ldi R31,pm_hi8(compareint)

	ldi R21,0x27
	ldi R20,0x10
	rjmp compareint 

endfunc:
	subi R24,0xD0 ; add '0', in two's complement
	st x+,R24
	st x+,R1
	ret	

load_ten:

	ldi R20,10
	rjmp comparechar
	nop			    ; do not delete 
	nop
load_hund:

	ldi R20,100
	clr R21
	rjmp compareint  ; do not delete 
	nop
load_onek:
	ldi R21,0x03
	ldi R20,0xE8 
	rjmp compareint   ; do not delete 
	nop
	//rjmp compareint

compareint:

	LOOP_INT
	LOOP_INT
	LOOP_INT
	LOOP_INT
	LOOP_INT

	rjmp compareint

endcheck:

	subi R23,0xD0 ; add '0', in two's complement
	st x+,R23
	clr R23

	sbiw R30,4
	ijmp

comparechar:
	
	LOOP_CHAR
	LOOP_CHAR
	LOOP_CHAR
	LOOP_CHAR
	LOOP_CHAR
	rjmp comparechar 


