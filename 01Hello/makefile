BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> The console should come up and print a 'Hello, World!' message <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.txt -f
