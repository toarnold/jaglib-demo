BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> Use the GPU PIT timer handled by CPU <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.txt -f
