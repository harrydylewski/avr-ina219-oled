/********************************
Description: Atmega specific code for utoa function with hardcoded 10 as the radix

function:
extern void _itoa16_ASM(unsigned int number, char *array);

number: self explainatory
array: expects char array that is atleast size 6 (array[6])

detailed: 

Default Code size: 

*********************************/
	.file "itoa10_asmv2.s"

	.text

	.global _itoa16_ASM                   

//-----------------------------------

_itoa16_ASM:
		movw R26,R22
	
Bin2BCD16:	

		ldi	R23,0xff	;initialize digit 4
		ldi	R22,0x9f	;initialize digits 3 and 2
		ldi	R21,0xa0	;initialize digits 1 and 0

binbcd_4:	

		inc	    R23		
		subi	R24,0x10    ;low(10000)
		sbci	R25,0x27    ;high(10000)
		brcc	binbcd_4			

binbcd_3:	

		subi	R22,0x10	
		subi	R24,0x18    ;low(-1000)
		sbci	R25,0xfc    ;high(-1000)
		brcs	binbcd_3	

binbcd_2:	

		inc	    R22		
		subi	R24,0x64    ;low(100)	
		sbci	R25,0x00    ;high(100) 
		brcc	binbcd_2	;

binbcd_1:	

		subi	R21,0x10	
		subi	R24,-10		
		brcs	binbcd_1
		add		R21,R24		
save:

		subi	r23,-0x30
		st		x+,r23
				
		mov     R20,R22

		swap	R22
		andi	R22,0x0F
		subi	r22,-0x30
		st		x+,r22

		andi	R20,0x0F
		subi	r20,-0x30
		st		x+,r20

		mov R20,R21

		swap	R21
		andi	R21,0x0F
		subi	r21,-0x30
		st		x+,r21
		andi	r20,0x0F
		subi	r20,-0x30
		st		x+,r20

		st      x,r1

		ret