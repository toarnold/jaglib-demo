#include <stdint.h>
#include <stdio.h>
#include <jagcore.h>
#include <jaglib.h>

volatile uint32_t ticks;
uint16_t jag_console_hide_startup=1; // Prevent initial console show

void jag_custom_interrupt_handler()
{
	if (*INT1&C_VIDENA)
	{
		++ticks;
	}

}

int main()
{
	uint32_t last=0;

	for (;;)
	{
		while (ticks==last);
		last=ticks;

		if (ticks==250) // Show console after 4-5 seconds
			jag_console_show();

		printf("%u\n",ticks);
	}
}