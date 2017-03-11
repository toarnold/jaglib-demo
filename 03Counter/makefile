BINFILE = jag$(notdir $(CURDIR)).jag

all: build

run: build upload

build:
	vc +jaguar -O2 -c99 -o $(BINFILE) main.c

upload:
	-jcp -r
	sleep 4
	jcp $(BINFILE)
	$(info >>>>>>>> You should see a running counter <<<<<<<<)

clean:
	rm $(BINFILE) -f
	rm *.txt -f
