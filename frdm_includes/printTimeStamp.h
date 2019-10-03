/*
 * @file printTimeStamp.h
 * @brief C Header file containing funciton prototypes and variables
 * used for logging
 *
 * This file contains the funciton prototypes and variables for the
 * logging debug function that prints the current and 
 * elapsed time on the freedom board
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */

#ifndef FRDM_INCLUDES_PRINTTIMESTAMP_H_
#define FRDM_INCLUDES_PRINTTIMESTAMP_H_

// Include the time library for time_t variable functions
#include <time.h>

// Declare epoch time that will get incremented in the RTC interrupt
extern volatile time_t currentEpoch;
time_t now;

// Variable that will get updated every mS in the sysTick ISR
uint32_t msTicks;

// Predefined variables for converting epoch to human readable format
struct tm  ts;
char buf[80];

// Values for calculating the elapsed time since the last LED toggle
int curMS = 0;
int prevMS = 0;

/*
 * @brief Prints the time for the logger
 * 
 * Prints the current time from the RTC and the elapsed time since the last
 * LED transition
 *
 * @return void
 */
void printTimeStamp(void);

#endif /* FRDM_INCLUDES_PRINTTIMESTAMP_H_ */
