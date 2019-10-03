/*
 * @file setLed_frdm.h
 * @brief Header file containing the function declarations and global
 * variables for the LEDBlink version of the FRDM board
 *
 * This is a Header file containing the function declarations and global
 * variables for the LEDBLink version of the FRDM board, and provides a description of the
 * functions used in the same
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */
#ifndef SET_LED_FRDM_H
#define SET_LED_FRDM_H

/* Including library file for LED pins */
#include "../board/board.h"

#include <stdio.h>


/*
 * @brief LED blink function
 *
 * This function blinks the LED in the required pattern
 * using the LookUp Table values
 *
 *@param Integer value which is the blinkIndex variable
 *
 * @return void.
 */
void setLed(int i);

#endif
