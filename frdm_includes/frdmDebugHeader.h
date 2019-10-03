/*
/*
 * @file Debug.h
 * @brief Header file containing the function declarations and global
 * variables for the Debug version of the FRDM board
 *
 * This is a Header file containing the function declarations and global
 * variables for the Debug version of the FRDM board, and provides a description of the
 * functions used in the same
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */

#ifndef DEBUG_H_
#define DEBUG_H_

// Include the release header as well, because the debug header is an
// extention of it
#include "frdmReleaseHeader.h"


/*
 * @brief Initialises the RTC
 * 
 * Initializes the RTC and the clocks required for the RTC.
 * Eanbles the RTC interrupt that gets triggered every second as well.
 *
 * @return void
 */
void rtc_init(void);

/*
 * @brief Prints the time elapsed since the last LED on/off instruction
 * 
 * Prints the time in hours, minutes, seconds and milliseconds
 * since when LED was switched on/off last
 *
 * @return void
 */
void printTimeStamp(void);

// Current UNIX time, updated later via a macro and the systick timer
time_t currentEpoch;

extern volatile uint32_t msTicks;

/*
 * @brief ISR for the sysTick timer
 * 
 * Increments the variable msTicks every mS for better logging resolution
 *
 * @return void
 */
void SysTick_Handler(void)
{
	msTicks++;
}


/*
 * @brief ISR for the RTC
 * 
 * Increments the variable currentEpoch every second for timekeeping
 *
 * @return void
 */
void RTC_Seconds_DriverIRQHandler(void)
{
	currentEpoch++;
}


#endif
