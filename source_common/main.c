/*
 * @file main.c
 * @brief Solution for the second PES project
 *
 * This is a C program which blinks LED in 4 different targets:
 * frdm_release
 * frdm_debug
 * pc_release
 * pc_debug
 *
 * The debug targets log the led status and colour, as well as the
current
 * time and elapsed time since the last LED transition
 *
 * The release targets outputs only the LED colour
 *
 * The outputs of the PC targets can be viewed on the terminal,
and the
 * outputs of the FRDM targets can be viewed on the KL25Z
 *
 * This code implements the touch sensor and the RTC as well *
 * All the targets are compiled using a single main function * and a single makefile
 *
 * @author Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @version 1.0
 */
/* Including library file for IO functions */
#include <stdio.h>
/* Include the header file that contains common function declarations */
#include "common_pc_frdm.h"
/* These header files will be included only for frdm_release target */
#ifdef frdm_release
#include "../frdm_includes/frdmReleaseHeader.h"
#endif

/* These header files will be included only for frdm_debug target */
#ifdef frdm_debug
#include "../frdm_includes/frdmDebugHeader.h"
#include <time.h>
#endif
/* These header files will be included only for pc_release target */
#if defined pc_release || defined pc_debug
#include "../pc_includes/common_pc.h"
#endif
/* Defining clock variables of time.h library for calculating elapsed time in pc_debug */
#ifdef pc_debug
clock_t startElapseTimer;
clock_t stopElapseTimer;
#endif
/* Defining extern variables from Touch_Sensor.h to check the Touch slider input */
#if defined frdm_debug || defined frdm_release
int checkColor;
bool checkTouchSlider;
#endif
/* Main function definition */
int main(void) {
	/* Run the initialization function to initialise the pins and
hardware */
#if defined frdm_debug || defined frdm_release
	init_pins();
	poll();
#endif
#ifdef frdm_debug
	rtc_init();
	currentEpoch = epoch;
#endif
	/* Check if the touch slider was sensed and ledindex is not
equal to a LED off operaton index */
	for ( LUTindex = 0; LUTindex < 20; LUTindex++, ledIndex++)
	{
#if defined frdm_debug || defined frdm_release
		if ( checkTouchSlider == true && ledIndex != 1 && ledIndex != 3 && ledIndex != 5)
		{

			/* Switch off all LEDs before turning on the LED
due to touch slider interrupt */
			LED_RED_OFF();
			LED_GREEN_OFF();
			LED_BLUE_OFF();
			/* checkColor stores the ledIndex to turn on the
respective LED */
			ledIndex = checkColor;
			/* Change the value of the bool variable to false
to check for next touch slider interrupt */
			checkTouchSlider = false;
		}
#endif
#ifdef pc_debug
		/* Print the Elapsed time since last instruction by
subtracting clock ticks and dividing by the clock frequency*/
		printf("%.3f ", ((double)(stopElapseTimer - startElapseTimer) / CLOCKS_PER_SEC) * 1000);
		/* Start the elapse timer clock */
		startElapseTimer = clock();
#endif
		/* Check if ledIndex reaches 6 and set it to 0 so it can
start blinking from RED */
		if (ledIndex >= 6) ledIndex = 0;
		setLed(ledIndex);
		delay(lookUpTable[LUTindex]);
		/* Start the stop elapse timer clock to check the elapsed time in the begining of the next iteration of the loop */
#ifdef pc_debug
		stopElapseTimer = clock();
#endif
	}
	return 0 ;
}
