	.include    "jaguar.inc"

	.extern _sine_tab

	; No ORG is needed cause the loop
	; uses a relative jump.
	; 'cause the jr the code must
	; be executed in DSP RAM

	.text
	.dsp
	;.phrase					; make phrase align, so the blitter can move this block
_create_sine_table_start::
	movei	#_sine_tab,r16	; C sine table
	movei	#ROM_SINE,r17	; ROM sine table
	movei	#128,r18		; repeat times
.loop:
	load	(r17),r0		; load sine value
	addqt	#4,r17			; next adress
	sharq	#10,r0			; treat as multiple of 32
	subq	#1,r18			; decrease counter
	store	r0,(r16)		; store in sine table
	jr		ne,.loop		; repeat counter 0?
	addqt	#4,r16			; next adress

	moveq   #0,r0         	; Stop GPU
	movei   #D_CTRL,r1
	store   r0,(r1)
	nop
	nop
_create_sine_table_end::
