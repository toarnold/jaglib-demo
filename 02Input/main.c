#include <stdio.h>

char buffer[4096];

int main()
{
	printf("Type in your name\n");
	fprintf(stderr,"Type in your name:\n");
	printf("Hello, %s!",gets(buffer));
}