#include <stdio.h>
#include <stdint.h>
#include <jagcore.h>
#include <jaglib.h>

extern uint8_t dsp_code_start[];
extern uint8_t dsp_code_end[];

extern volatile uint32_t counter;
extern volatile uint32_t stopJerry;

uint32_t lastCounter = 0;

#define DSP_CLOCK 26591000

int main()
{
	jag_dsp_load(D_RAM, dsp_code_start, dsp_code_end - dsp_code_start);
	*JPIT1=1000-1;
	*JPIT2=(DSP_CLOCK/1000)-1;
	puts("start timer");
	jag_dsp_go(D_RAM, 0);

	while (jag_dsp_is_running())
	{
		if (lastCounter != counter)
		{
			lastCounter = counter;
			printf("%u\n",lastCounter);
			if (lastCounter == 10)
			{
				stopJerry=1;
				puts("stop timer");
			}
		}
	}
}