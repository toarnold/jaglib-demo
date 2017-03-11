BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> A red square should appear as an overlay - custom welcome messages <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.txt -f
