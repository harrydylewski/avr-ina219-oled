/********************************
Description: Atmega specific code for itoa function with hardcoded 10 as the radix
This is version 3

function:
extern void _itoa10_asm(int number, char *array);

inputs:
number: self explainatory
array: expects char array that is atleast size 7 (array[7])

outputs:
returns nothing


*********************************/
	.file "itoa_10_avr_asmv3.s"

	.text

	.global _itoa10_asm                    

//-----------------------------------

_itoa10_asm:
	/*

	r25:24   - number to breakdown
	r23:22   - array pointer, gets moved to X, and is used during function
			   as a counter
	
	*/       

		movw R26,R22   //move array pointer to X
		ldi	R23,0xff   
		ldi R22,'-'
		
		sbrs R25,7    //if not negative, skip negative setup code
		rjmp digit0
		
		st x+,R22	  //append '-' to string		
		
		eor R25,R23	   //two's complement across 16bit	
		eor R24,R23
		adiw R24,1  

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

