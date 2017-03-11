BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	jcp -c $(BINFILE)
	$(info >>>>>>>> A screen shot named 'test.bmp' and a message should be written to your remote console <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm test.bmp -f
	rm *.txt -f
