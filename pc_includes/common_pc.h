/*
 * @file common_pc.h
 * @brief Header file which contains info shared between different .c files
 *
 * This header file  contains info shared between different .c files for the
 * PC target
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */



#ifndef COMMON_PC_H_
#define COMMON_PC_H_


/*
 * @brief Sets the colour of the LEDs according to the input
 * 
 * Change the LED colour accouding to input i and log the values on the 
 * console
 *
 * @return void
 */
void setLed(int);

/*
 * @brief Prints the time for the logger
 * 
 * Prints the current time from the RTC and the elapsed time since the last
 * LED transition
 *
 * @return void
 */
void printTimeStamp(void);


/*
 * @brief Implements delay function
 *  
 * Do nothing for the given amount of time in mS
 *
 * @arguments int delayValue The amount of delay in mS
 * @return void
 */
void delay(int delayValue);

#endif