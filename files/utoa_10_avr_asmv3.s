/********************************
Description: Atmega specific code for utoa function with hardcoded 10 as the radix
			 This is version 3
			 This function is based off code found from the fast itoa function at community atmel website
			 http://community.atmel.com/projects/fast-itoa-v10
			 This function is slightly faster and smaller due to avoiding conversion to BCD and swapping nibbles


function:
extern void utoa10_asm(unsigned int number, char *array);

inputs:
number: self explainatory
array: expects char array that is atleast size 6 (array[6])

output:
returns nothing

detailed:
uses neat tricks to reduce ints by powers of 10 and
avoiding having to do comparisons by alterting between 
subtracting positive numbers and negative numbers
 

Default Code size:


Default Code Execution:
~120-140 cycles

*********************************/
	.file "utoa_10_avr_asmv3.s"

	.text

	.global _utoa10_asm                    

//-----------------------------------

_utoa10_asm:
	/*
	r25:24   - number to breakdown
	r23:22   - array pointer, gets moved to X, 
			 - R23 is used during function as a counter	
	*/       

		movw R26,R22   ;move array pointer to X
		ldi	R23,0xff   

digit0:	
		
		inc	    R23		
		subi	R24,lo8(10000)    ;low(10000)  0x10
		sbci	R25,hi8(10000)    ;high(10000) 0x27
		brcc	digit0	
		
		subi	r23,-0x30
		st		x+,r23

		ldi	R23,10

digit1:	

		dec     R23	
		subi	R24,lo8(-1000)    ;low(-1000)  0x18
		sbci	R25,hi8(-1000)    ;high(-1000) 0xfc
		brcs	digit1	

		subi	r23,-0x30
		st		x+,r23
		
		ldi	R23,0xff

digit2:	

		inc	    R23	
		subi	R24,0x64    ;low(100)  0x64
		sbci	R25,0x00    ;high(100) 0x00 
		brcc	digit2   	;

		subi	r23,-0x30
		st		x+,r23

		ldi	R23,10

digit3:	

		dec     R23	
		subi	R24,-10		
		brcs	digit3	

		subi	r23,-0x30
		st		x+,r23

digit4:

		subi	r24,-0x30
		st		x+,r24

digitnull:

		st      x+,r1

endfunc:

		ret

