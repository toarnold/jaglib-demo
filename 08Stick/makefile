BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
#	vasmm68k_mot handler.s  -Fvobj -quiet -o handler.o
	vc +jaguarMem -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> Test the joystick0 <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.txt -f
