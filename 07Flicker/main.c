#include <stdint.h>
#include <stdio.h>
#include <jagcore.h>
#include <jaglib.h>

volatile uint32_t ticks;

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
	int console=1;

	for (;;)
	{
		while (ticks==last);
		last=ticks;

		printf("%u\n",ticks);

		if (ticks%256==0)
		{
			console=!console;
			if (console)
			{
				jag_console_show();
			}
			else
			{
				jag_console_hide();
			}
		}

	}
}