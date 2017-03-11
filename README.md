# jaglib-demo
Demo code for the ATARI Jaguar jaglib.

The jaglib is part of the ATARI Jaguar target in the [vbcc](http://sun.hasenbraten.de/vbcc/) package.
The library is designed to act in conjunction with the vclib, so it is easy to take first steps in ATARI Jaguar programming.
 
## Prerequisites

* First of all, you will need a [SkunkBoard](http://www.harmlesslion.com/cgi-bin/showprog.cgi?search=skunkboard).
* A working gcc installation (For windows you can take [MinGW](http://www.mingw.org/))
* You will need a working vbcc toolchain
	* Be sure to set up your working area according the [instructions](http://server.owl.de/~frank/vbcc/docs/vbcc.pdf).
	* Take the most recent version of the following tools. The tools must be compiled by yourself.
		* [vbcc](http://sun.hasenbraten.de/vbcc/)
		* [vasm](http://sun.hasenbraten.de/vasm/). [Compile](http://sun.hasenbraten.de/vasm/index.php?view=compile) this tool for the following targets
			* m68k
			* jagrisc
		* [vlink](http://sun.hasenbraten.de/vlink/)
	* Place the compiled tools in you _bin_ folder
	* The *jaglib* is a part of the vbcc distribution and resides in the _bin_ folder of the ATARI Jaguar target.
	* Copy the file *targets/m68k_jaguar/config/config_windows* (or *config_linux*) to your *config* folder and rename it to _jaguar_

## Running the demo

Be sure your Jaguar is switched on and *jcp* is working. Simply type
```
make
````
This will run all demos and write out small descriptions.

Using the following commands, you can compile and run each demo separatly.
```
make build
````

```
make run
````

