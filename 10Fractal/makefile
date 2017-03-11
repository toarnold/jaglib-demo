BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vasmjagrisc_madmac mand.s -I$(VBCC)/targets/m68k-jaguar/include -Fvobj -quiet -mgpu -o mand.o
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c mand.o

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> You will see a gpu rendered fractal <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.o -f
	rm *.txt -f
	rm *.bmp -f
