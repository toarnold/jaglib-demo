#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <jaglib.h>

int main()
{
	puts("This code force an adress error.\nThe debugger will be launched on your\nskunk console.");
	char *ptxt="Hallo";
	skunkCONSOLEWRITE(ptxt+1);
}