/*
 * @file printTimeStamp.c
 * @brief C file containing the actual logging function
 * variables for the release version of the FRDM board
 *
 * This file contains the logging debug function that prints the current and 
 * elapsed time on the freedom board
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */

#include <stdio.h>
#include "../frdm_includes/printTimeStamp.h"


/*
 * @brief Prints the time for the logger
 * 
 * Prints the current time from the RTC and the elapsed time since the last
 * LED transition
 *
 * @return void
 */
//reference: https://www.epochconverter.com/programming/c
void printTimeStamp(void)
{
	prevMS = curMS;
	curMS = msTicks;
	now = currentEpoch;
	ts = *localtime(&now);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
	printf("%s ",buf);
	printf("%d\n", curMS - prevMS);
}

