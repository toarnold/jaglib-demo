#include <stdint.h>
#include <stdio.h>
#include <jagcore.h>
#include <jaglib.h>

int main()
{
	for(;;)
	{
		jag_console_set_cursor(0,80);
		//uint32_t stick=jag_read_stick0(STICK_READ_DIRECTIONS_A_ONLY);
		uint32_t stick=jag_read_stick0(STICK_READ_ALL);
		if (stick&STICK_0) puts("0     ");
		else if (stick&STICK_1) puts("1     ");
		else if (stick&STICK_2) puts("2     ");
		else if (stick&STICK_3) puts("3     ");
		else if (stick&STICK_4) puts("4     ");
		else if (stick&STICK_5) puts("5     ");
		else if (stick&STICK_6) puts("6     ");
		else if (stick&STICK_7) puts("7     ");
		else if (stick&STICK_8) puts("8     ");
		else if (stick&STICK_9) puts("9     ");
		else if (stick&STICK_STAR) puts("*     ");
		else if (stick&STICK_HASH) puts("#     ");
		else if (stick&STICK_A) puts("A     ");
		else if (stick&STICK_B) puts("B     ");
		else if (stick&STICK_C) puts("C     ");
		else if (stick&STICK_OPTION) puts("OPTION");
		else if (stick&STICK_PAUSE) puts("PAUSE ");
		else if (stick&STICK_UP) {putchar(28); puts("     ");}
		else if (stick&STICK_DOWN) {putchar(29); puts("     ");}
		else if (stick&STICK_LEFT) {putchar(30); puts("     ");}
		else if (stick&STICK_RIGHT) {putchar(31); puts("     ");}
		else puts("      ");
	}
}