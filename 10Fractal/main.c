/* Copyright 2015 Bernhard R. Fischer, 2048R/5C5FFD47 <bf@abenteuerland.at>
 *
 * IntFract is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * IntFract is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IntFract. If not, see <http://www.gnu.org/licenses/>.
 */

/* This program calculates fractal images. It shows how to use integer
 * arithmetics instead of floating point operations.
 *
 * I wrote this program originally at about 1990 for the Amiga 500 in C and
 * also wrote an assembler version which contain some additional speed
 * improvements.
 *
 * Compile this program with
 * gcc -Wall -O2 -std=c99 `pkg-config --cflags --libs cairo` -o intfract intfract.c
 *
 * @author Bernhard R. Fischer
 * @version 2015/10/11 (this version)
 */

// https://www.cypherpunk.at/2015/10/calculating-fractals-with-integer-operations/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jaglib.h>
#include <jagcore.h>

// maximum number of iterations of the inner loop
#define MAXITERATE 64

#define NORM_BITS 13
#define NORM_FACT ((nint_t)1 << NORM_BITS)
#define NORM_LIMT ((nint_t) 4 * NORM_FACT)
typedef int nint_t;

/*! This function contains the iteration loop using integer arithmetics.
 * @param real0 Real coordinate of pixel within the complex plane.
 * @param imag0 Imaginary coordinate of the pixel.
 * @return Returns the number of iterations to reach the break condition.
 */
int iterate(nint_t real0, nint_t imag0)
{
	 nint_t realq, imagq, real, imag;
	 int i;

	 real = real0;
	 imag = imag0;
	 for (i = 0; i < MAXITERATE-1; i++)
	 {
		 realq = (real * real) >> NORM_BITS;
		 imagq = (imag * imag) >> NORM_BITS;

		 if ((realq + imagq) > NORM_LIMT)
				break;

		 imag = ((real * imag) >> (NORM_BITS - 1)) + imag0;
		 real = realq - imagq + real0;
	 }
	 return i;
}

/*! This function contains the outer loop, i.e. calculate the coordinates
 * within the complex plane for each pixel and then call iterate().
 * @param image Pointer to image array of size hres * vres elements.
 * @param realmin Minimun real value of image.
 * @param imagmin Minimum imaginary value of image.
 * @param realmax Maximum real value.
 * @param imagmax Maximum imaginary value.
 */
void mand_calc(char *image, nint_t realmin, nint_t deltareal, nint_t imag0, nint_t deltaimag)
{
	nint_t real0;
	int x, y;

	for (y=0;y<CONSOLE_BMP_HEIGHT;++y)
	{
		real0=realmin;
		for (x=0;x<CONSOLE_BMP_WIDTH;++x)
		{
			*image++=iterate(real0,imag0);
			real0+=deltareal;
		}
		imag0-=deltaimag;
	}
}

// GPU parameters
extern int32_t realmin;
extern int32_t deltareal;
extern int32_t imag0;
extern int32_t deltaimag;

// GPU routine
extern uint8_t mandcalc[];
extern uint8_t mandcalc_end[];

int main()
{
	 double bbox[] = {-2.0, -1.2, 0.7, 1.2};   // realmin, imagmin, realmax, imagmax
	 //double bbox[] = {-1.82, -0.07, -1.7, 0.07};   // realmin, imagmin, realmax, imagmax
	 //double bbox[] = {-1.3, 0.03, -1.24, 0.1};   // realmin, imagmin, realmax, imagmax

	 // Color Setup
	 for (int i=0;i<MAXITERATE;++i)
	 	jag_set_indexed_color(i,toRgb16(0,(63-i)<<2,0));

	nint_t _realmin=bbox[0] * NORM_FACT;
	nint_t _imagmin=bbox[1] * NORM_FACT;
	nint_t _realmax=bbox[2] * NORM_FACT;
	nint_t _imagmax=bbox[3] * NORM_FACT;
	nint_t _deltareal = (_realmax - _realmin) / CONSOLE_BMP_WIDTH;
	nint_t _deltaimag = (_imagmax - _imagmin) / CONSOLE_BMP_HEIGHT;

	puts("Press stick(0) 'up' to CPU render\nor 'down' to GPU render the fractal.");

	uint32_t stick;
	do {
		stick=jag_read_stick0(STICK_READ_DIRECTIONS_A_ONLY);

		if (stick&STICK_UP)
		{
			mand_calc(jag_vidmem, _realmin, _deltareal, _imagmax, _deltaimag);
		}
		if (stick&STICK_DOWN)
		{
			jag_gpu_load(G_RAM,mandcalc, mandcalc_end-mandcalc);

			// pass parameters
			realmin=_realmin;
			deltareal=_deltareal;
			imag0=_imagmax;
			deltaimag=_deltaimag;

			jag_gpu_go((uint32_t *)G_RAM, 0);
			jag_gpu_wait();
		}
	} while (stick==0);

	for(;;);
}
