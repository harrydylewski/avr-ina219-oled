.file "WS2813-blank.s"

	.text
	.global transmit_ws_blank

//FINAL------------------------------------------
transmit_ws_blank:
	
	cli
	cp R24,R1
	cpc R25,R1
	breq end

	movw R30,R22
	ld R21,Z
	or R20,R21

start:

	ldi R22,24
	rjmp maincode

maincode:

	st Z,R20
    rjmp delay0

delay0:

	rjmp delay1

delay1:

	st Z,R21

	dec R22
	brne maincode
	
	sbiw R24,1
	brne start

end:
	sei
	ret

	
