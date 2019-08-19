#include <stdio.h>
#include <string.h>
#include "7seg_bp_ada.h"

int main(int argc, char ** argv)
{
	int rc;
	int i;
	int l;
	int d;

	// prepare the backpack driver
        // (the first parameter is the i2c master controller attached to the HT16K33, the second is the i2c selection jumper)
        // The i2c selection address can be one of HT16K33_ADDR_01 to HT16K33_ADDR_08
	HT16K33 led_backpack1 = HT16K33_INIT(2, HT16K33_ADDR_01);
	
	// initialize the backpack
	rc = HT16K33_OPEN(&led_backpack1);
	if(rc != 0) {
		fprintf(stderr, "Error initializing HT16K33 led backpack (%s). Check your i2c bus (es. i2cdetect)\n", strerror(led_backpack1.lasterr));
		// you don't need to HT16K33_CLOSE() if HT16K33_OPEN() failed, but it's safe doing it.
		HT16K33_CLOSE(&led_backpack1);
		return 1;
	}
	
	// power on the ht16k33
	rc = HT16K33_ON(&led_backpack1);
	if(rc != 0) {
		fprintf(stderr, "Error putting the HT16K33 led backpack ON (%s). Check your i2c bus (es. i2cdetect)\n", strerror(led_backpack1.lasterr));
		// you don't need to HT16K33_OFF() if HT16K33_ON() failed, but it's safe doing it.
		HT16K33_OFF(&led_backpack1);
		HT16K33_CLOSE(&led_backpack1);
		return 1;
	}
	
	// make it shining bright
	HT16K33_BRIGHTNESS(&led_backpack1, 0x0F);
	
	// make it not blinking
	HT16K33_BLINK(&led_backpack1, HT16K33_BLINK_OFF);
	
	// power on the display
	HT16K33_DISPLAY(&led_backpack1, HT16K33_DISPLAY_ON);
	
	/* display first 4 digits of text string */
	/* really need to take a float arg and print out nn.nn */
	l = strlen(argv[1]);
	if (l > 4)
		l = 4;
	d = 0;
	for (i = 0; i < l; i++) {
		if (i == 2) {
			/* Skip the colon */
			d++;
		}
		HT16K33_UPDATE_DIGIT(&led_backpack1, d++, argv[1][i], 0);
	}
	// HT16K33_UPDATE_DIGIT(&led_backpack1, 2, HT16K33_COLON_OFF, 0);
	HT16K33_COMMIT(&led_backpack1);
	
	// close things (the display remains in the conditions left)
	HT16K33_CLOSE(&led_backpack1);
	
	return 0;
}
