#include <stdio.h>
#include <stdint.h>
#include <jaglib.h>
#include <jagcore.h>

volatile uint32_t counter=0;

uint16_t jag_custom_interrupt_handler()
{
	if (*INT1&C_PITENA) // Timer Interrupt?
	{
		++counter;
		return C_PITCLR; // Flag timer handled
	}
	return 0;
}

#define GPU_CLOCK 26591000

uint32_t lastCounter = 0;

int main()
{
	puts("start timer");
	*PIT0=1000-1;				// Set prescaler
	*PIT1=(GPU_CLOCK/1000)-1;	// and divider
	jag_set_cpu_int_mask(C_VIDENA | C_PITENA); // Enable timer and video interrupts

	while (lastCounter<10)
	{
		if (lastCounter != counter)
		{
			lastCounter = counter;
			printf("%u\n",lastCounter);
		}
	}

	puts("stop timer");
	*PIT0=0; // Stop timer
	jag_set_cpu_int_mask(C_VIDENA); // Disable Timer interrupt
}