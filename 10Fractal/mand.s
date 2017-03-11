		.include    "jaguar.inc"

BMP_WIDTH	.equ 320
BMP_HEIGHT  .equ 200
MAXITERATE	.equ 64
NORM_BITS	.equ 13
NORM_FACT 	.equ (1<<NORM_BITS)
			.globl _jag_vidmem
		.phrase
_mandcalc::
		.gpu
TEMP1		.equr r0
TEMP2		.equr r1
REAL0		.equr r2
REALMIN		.equr r3
DELTAREAL 	.equr r4
IMAG0		.equr r5
DELTAIMAG	.equr r6
REALQ		.equr r7
IMAGQ		.equr r8
REAL		.equr r9
IMAG		.equr r10
NORM_LIMIT	.equr r11
MAX_ITERATIONS .equr r12
IMAGE		.equr r16
XINDEX		.equr r17
YINDEX		.equr r18
ITERATIONS	.equr r19
XMAX		.equr r20
YMAX		.equr r21

	.macro LoadValue val, reg
        movei	#\val,TEMP1
        load	(TEMP1),\reg
	.endm

		.org G_RAM
		LoadValue	_jag_vidmem,IMAGE
		LoadValue	_realmin,REALMIN
		move		REALMIN,REAL0
		LoadValue	_deltareal,DELTAREAL
		LoadValue	_imag0,IMAG0
		LoadValue	_deltaimag,DELTAIMAG
		movei	#4*NORM_FACT,NORM_LIMIT
		movei	#MAXITERATE-1,MAX_ITERATIONS
		moveq	#0,YINDEX			; r18 y
		moveq	#0,ITERATIONS		; r19 iterations
		movei	#BMP_WIDTH,XMAX	; r20 x_max
		movei	#BMP_HEIGHT,YMAX	; r21 y_max
		movei	#iterate,r22
		movei	#xloopcont,r23
		movei	#iterate_loop,r24

yloop:
		moveq	#0,XINDEX			; r17 x
xloop:
		; parameters (REAL0,IMAG0)
		jump	(r22)
		nop
xloopcont:
		storeb	ITERATIONS,(IMAGE)
		add		DELTAREAL,REAL0
		addq	#1,XINDEX
		cmp		XMAX,XINDEX
		jr		ne,xloop
		addq	#1,IMAGE

		sub		DELTAIMAG,IMAG0
		addq	#1,YINDEX
		cmp		YMAX,YINDEX
		jr		ne,yloop
		move	REALMIN,REAL0

		moveq   #0,TEMP1         	; Stop GPU
		movei   #G_CTRL,TEMP2
		store   TEMP1,(TEMP2)
		nop
		nop

iterate:
		move	REAL0,REAL
		move	IMAG0,IMAG
		moveq	#0,ITERATIONS
		move	REAL,REALQ
iterate_loop:
		move	IMAG,IMAGQ
		imult	REAL,REALQ
		imult	IMAG,IMAGQ
		sharq	#NORM_BITS,REALQ
		sharq	#NORM_BITS,IMAGQ

		move	REALQ,TEMP1
		add		IMAGQ,TEMP1
		cmp		TEMP1,NORM_LIMIT
		jr		mi,iterate_exit

		sub		IMAGQ,REALQ
		add		REAL0,REALQ

		imult	REAL,IMAG
		sharq	#NORM_BITS-1,IMAG

		addq	#1,ITERATIONS

		add		IMAG0,IMAG

		cmp		ITERATIONS,MAX_ITERATIONS
		jump	ne,(r24)		;iterate_loop
		move	REALQ,REAL

iterate_exit:
		jump	(r23) ; return ITERATIONS
		nop

		.long
_realmin::		.dc.l 0
_deltareal::	.dc.l 0
_imag0::		.dc.l 0
_deltaimag::	.dc.l 0
		.68000
_mandcalc_end::
