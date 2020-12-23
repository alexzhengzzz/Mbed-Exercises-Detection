#include "mbed.h"
#include "FILTER.h"


FILTER::FILTER() {
}


float FILTER::filterAngle(int16_t zAccel) {
        /* normalise to 1g */
		g_z = (float)zAccel/17694.0;

		/* insert in to circular buffer */
		ringbuf[ringbuf_index++] = g_z;

		/* at the end of the buffer, wrap around to the beginning */
		if (ringbuf_index >= N) {
			ringbuf_index = 0;
		}

		/********** START of filtering ********************/
		
		float g_z_filt = 0;

		/* add all samples */
		for (uint8_t i = 0; i < N; i++) {
			g_z_filt += ringbuf[i];
		}

		/* divide by number of samples */
		g_z_filt /= (float)N;

		/* restrict to 1g (acceleration not decoupled from orientation) */
		if (g_z_filt > 1) {
			g_z_filt = 1;
		}

		/********** END of filtering **********************/
		return 180*acos(g_z_filt)/PI;
}