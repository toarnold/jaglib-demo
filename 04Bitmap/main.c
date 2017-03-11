#include <jaglib.h>
#include <stdio.h>

int main()
{
	puts("Look at your remote console!");
	fprintf(stderr,"This text should appear on your remote console.\n");
	jag_console_save_bmp("test.bmp");
}