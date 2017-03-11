BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vasmjagrisc_madmac sintable.s -I$(VBCC)/targets/m68k-jaguar/include -Fvobj -quiet -mdsp -o sintable.o
	vc +jaguar -O2 -c99 -lm -o $(BINFILE) main.c sintable.o 

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> A DSP-RISC subroutine ist loaded, started and two sine wave should be displayed <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.o -f
	rm *.txt -f
