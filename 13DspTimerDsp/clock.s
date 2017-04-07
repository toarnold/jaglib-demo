	.include	"jaguar.inc"

		.text
		.phrase
_dsp_code_start::
		.dsp

TEMP1		.equr r0
TEMP2		.equr r1
ISR_TEMP1	.equr r29
ISR_TEMP2	.equr r3
ISR_RET_ADR	.equr r30
CANCEL		.equr r13
COUNTER		.equr r14
SP			.equr r31
DSPFLAGS	.equr r28

		.org			D_RAM

		.macro ISR_NOT_SET
			.rept 8
			nop
			.endr
		.endm

		; CPU Interrupt
		movei	#.dsp_main,ISR_TEMP1	;point to start
		jump	(ISR_TEMP1)				;go start
		.rept 4
		nop
		.endr

		; I2S Interrupt
		ISR_NOT_SET

		; Timer 1 Interrupt
		movei	#.timer1,ISR_TEMP1		;point to start
		jump	(ISR_TEMP1)				;go start
		.rept 4
		nop
		.endr

		; Timer 2 Interrupt
		ISR_NOT_SET

		; External 1 Interrupt
		ISR_NOT_SET

		; External 2 Interrupt
		ISR_NOT_SET

.timer1:		
		load	(DSPFLAGS),ISR_TEMP1	;get dsp flags
		bclr	#3,ISR_TEMP1			;interrupt serviced
		load	(SP),ISR_RET_ADR		;get return from stack
		bset	#11,ISR_TEMP1			;clear int source flag
		addq	#4,SP					;update stack
		addq	#2,ISR_RET_ADR			;update return address

		; custom Code start
		load	(COUNTER),ISR_TEMP2
		addq	#1,ISR_TEMP2			; Increment counter
		store	ISR_TEMP2,(COUNTER)
		; custom Code end

		store	ISR_TEMP1,(DSPFLAGS)	;set dsp flags
		jump	(ISR_RET_ADR)			;return from int
		nop

.dsp_main:
		movei	#D_ENDRAM,SP			;point to stack
		moveta	SP,SP					;in both reg sets
		movei	#D_FLAGS,DSPFLAGS		;point to DSP flags
		movei	#_counter,COUNTER
		movei   #_stopJerry,CANCEL
		load	(DSPFLAGS),TEMP1		;get dsp flags
		bset	#6,TEMP1				; bit 6 enable timer 1 interrupt
		store	TEMP1,(DSPFLAGS)		;do it

.jwaitloop:
		load	(CANCEL),TEMP1
		cmpq	#0,TEMP1				; Test cancellation Token
		jr		eq,.jwaitloop
		nop

		; Stop DSP
		moveq   #0,TEMP1
		movei	#D_CTRL,TEMP2
		store	TEMP1,(DSPFLAGS)
		store	TEMP1,(TEMP2)
		nop
		nop

		.phrase
_counter::
		dc.l 0
_stopJerry::
		dc.l 0

_dsp_code_end::
