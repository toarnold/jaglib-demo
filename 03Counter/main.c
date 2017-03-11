#include <stdint.h>
#include <stdio.h>
#include <jagcore.h>

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

	for (;;)
	{
		while (ticks==last);
		last=ticks;

		printf("%u\n",ticks);
	}
}