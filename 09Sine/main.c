#include <stdio.h>
#include <stdint.h>
#include <jagcore.h>
#include <jaglib.h>
#include <math.h>

extern uint8_t create_sine_table_start[];
extern uint8_t create_sine_table_end[];
int32_t sine_tab[128];

void plot(int x,int y,uint8_t c)
{
	jag_vidmem[y*CONSOLE_BMP_WIDTH+x]=c;
}

int main()
{
	jag_set_indexed_color(0,toRgb16(0,0xff,0));
	jag_set_indexed_color(1,toRgb16(0xff,0,0));
	jag_dsp_load(D_RAM,create_sine_table_start, create_sine_table_end-create_sine_table_start);

	jag_dsp_go(D_RAM, 0);
	jag_dsp_wait();

	// plot sine wave by scaled dsp table
	for (int i=0;i<CONSOLE_BMP_WIDTH;++i)
	{
		plot(i,120-sine_tab[i%128],0);
	}
	// plot sine wave by cpu
	for (int i=0;i<CONSOLE_BMP_WIDTH;++i)
	{
		plot(i,160-32*sin(2*M_PI/128*((i+1)%128)),1);
	}
}