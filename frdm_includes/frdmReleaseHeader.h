/*
 * @file Release.h
 * @brief Header file containing the function declarations and global
 * variables for the release version of the FRDM board
 *
 * This is a Header file containing the function declarations and global
 * variables for the Release version of the FRDM board, and provides a description of the
 * functions used in the same
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */
#ifndef RELEASE_H_
#define RELEASE_H_

/* Include FRDM board drivers, utilities and board header files */
#include "../drivers/fsl_clock.h"
#include <stdio.h>
#include "../board/board.h"
#include "../board/peripherals.h"
#include "../board/pin_mux.h"
#include "../board/clock_config.h"
#include "../CMSIS/MKL25Z4.h"
#include "../utilities/fsl_debug_console.h"
#include "../frdm_includes/Touch_Sensor.h"
#include "../frdm_includes/setLed_frdm.h"
#include "../frdm_includes/Touch_Sensor.h"

/* Force the counter to be placed into memory. */
volatile static int i = 0 ;

/*
 * @brief Initialization of board pins
 *
 * Initialsing the pins and leds on the board
 *
 * @return void.
 */
void init_pins()
{
	/* Init board hardware. */
		BOARD_InitBootPins();
		BOARD_InitBootClocks();
		BOARD_InitBootPeripherals();
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();

		/* Initialize LEDs */
		LED_RED_INIT(0);
		LED_GREEN_INIT(0);
		LED_BLUE_INIT(0);

		LED_RED_OFF();
		LED_GREEN_OFF();
		LED_BLUE_OFF();
}

/*
 * @brief FRDM Board Delay function
 *
 * Causes a delay by perform a NOP for x milliseconds
 *
 *@param delay value in milliseconds
 *
 * @return void.
 */
void delay(int x)
{
	for ( i = 0; i < x*((int)(1000*1000/542)); i++)
		{
			 __asm volatile ("NOP");       //Using NOP in FRDM board to not do any operation inside the delay loop
		}
}

#endif
