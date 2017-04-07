BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vasmjagrisc_madmac clock.s -I$(VBCC)/targets/m68k-jaguar/include -Fvobj -quiet -mdsp -o clock.o
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c clock.o

upload:
	-jcp -r
	sleep 4
	-jcp $(BINFILE)
	$(info >>>>>>>> Use the DSP JPIT1 timer handled by DSP <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.o -f
	rm *.txt -f
