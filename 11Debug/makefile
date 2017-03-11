BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	-jcp -c $(BINFILE)
	$(info >>>>>>>> THie demo will launch the debugger <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.o -f
	rm *.txt -f
