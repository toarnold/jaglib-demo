#include <stdint.h>
#include <jaglib.h>
#include <jagcore.h>
#include <stdio.h>

op_bmp_object *overlay=0;
uint8_t *overlay_bmp;

void jag_init_message()
{
}

void jag_welcome_message()
{
}

uint16_t jag_custom_interrupt_handler()
{
	if (*INT1&C_VIDENA)
	{
		if (overlay && overlay_bmp)
		{
        	overlay->p0.height = 80;
        	overlay->p0.data = (uint32_t)overlay_bmp >> 3;
		}
	}
	return 0;
}

int main()
{
	jag_set_indexed_color(0,toRgb16(255,0,0));

	op_stop_object *stopobj=calloc(1,sizeof(op_stop_object));
	stopobj->type = STOPOBJ;
	stopobj->int_flag = 1;

	op_bmp_object *localoverlay=0;

	localoverlay=calloc(1,sizeof(op_bmp_object));
	overlay_bmp=calloc(80,80);
	localoverlay->p0.type = BITOBJ;
	localoverlay->p0.ypos = 100;
	localoverlay->p0.height = 80;
	localoverlay->p0.link = (uint32_t)stopobj >> 3;
	localoverlay->p0.data = (uint32_t)overlay_bmp >> 3;
	localoverlay->p1.xpos = 88;
	localoverlay->p1.depth = O_DEPTH8 >> 12;
	localoverlay->p1.pitch = 1;
	localoverlay->p1.dwidth = localoverlay->p1.iwidth = 80 / 8;
	localoverlay->p1.release=1;

	// prevent ISR to do something unexpected
	overlay=localoverlay;

	jag_append_olp(overlay);
	for(;;);
	
}