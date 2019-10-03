/*
 * @file Touch_Sensor.h
 * @brief Header file containing the function declarations and global
 * variables for the Touch Sensor
 *
 * This is a Header file containing the function declarations and global
 * variables for theTouch Sensor of FRDM board, and provides a description of
 * thefunctions used in the same
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */

//reference: Touch sensor example code from FRDM KL25Z SDK

#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

/* Include FRDM board drivers, utilities and board header files */
#include "../board/board.h"
#include "../drivers/fsl_tsi_v4.h"
#include "../utilities/fsl_debug_console.h"
#include "../drivers/fsl_lptmr.h"

#include "../board/clock_config.h"
#include "../board/pin_mux.h"

/* Define the Touch sensor detection variables as extern */
extern bool checkTouchSlider;
extern int checkColor;

/* Available PAD names on board */
#define PAD_TSI_ELECTRODE_1_NAME "E1"

/* Get source clock for LPTMR driver */
#define LPTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_LpoClk)
/* Define LPTMR microseconds counts value */
#define LPTMR_USEC_COUNT (300000U)

/* Buffer to store Calibrated data */
tsi_calibration_data_t buffer;

/*
 * @brief ISR for Touch Sensor
 *
 * The Interrupt Service routine that is responsible for
 * changing the LED color every time the user touches the sensor
 *
 * @return void.
 */
void TSI0_IRQHandler(void);

/*
 * @brief Polling for Interrupts
 *
 * This function constantly polls to check for user inputs
 * and Triggers interrupt whenever the sensor is touched
 *
 * @return void.
 */
void poll(void);

#endif
