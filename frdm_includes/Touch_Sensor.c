
/*
 * @file Touch_Sensor.c
 * @brief File containing the calibration and execution function for the 
 * capacitive touch sensor
 *
 * This file contains code for touch sensor initialization, calibartion,
 * enabling interrupts, and storing values of inputs 
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */

//Include relevant libraries for the drivers and storing outputs
#include "Touch_Sensor.h"
#include <stdio.h>
#include "../board/board.h"
#include "../drivers/fsl_tsi_v4.h"
#include "../utilities/fsl_debug_console.h"
#include "../drivers/fsl_lptmr.h"
//Extern variables passing the input to the main.c code
bool checkTouchSlide = false;
int checkColor = 10;
#include "../board/clock_config.h"
#include "../board/pin_mux.h"


/*
 * @brief ISR for the touch sensor
 * 
 * Reads the input from the capacitive touch sensor and saves those values
 * for use in main.c
 *
 * @return void
 */
void TSI0_IRQHandler(void)
{
    //Get raw channel value
    if (TSI_GetMeasuredChannelNumber(TSI0) == BOARD_TSI_ELECTRODE_1)
    {
        //Compare against calibrated values and set outputs accordingly
        if ((TSI_GetCounter(TSI0)-buffer.calibratedData[BOARD_TSI_ELECTRODE_1])>=100 && (TSI_GetCounter(TSI0)-buffer.calibratedData[BOARD_TSI_ELECTRODE_1])<=500)
        {
        	checkTouchSlider = true;
        	checkColor = 0;
        }
        else if ((TSI_GetCounter(TSI0)-buffer.calibratedData[BOARD_TSI_ELECTRODE_1])>500 && (TSI_GetCounter(TSI0)-buffer.calibratedData[BOARD_TSI_ELECTRODE_1])<=1500)
		{
        	checkTouchSlider = true;
        	checkColor = 2;
		}
        else if ((TSI_GetCounter(TSI0)-buffer.calibratedData[BOARD_TSI_ELECTRODE_1])>1500)
		{
        	checkTouchSlider = true;
        	checkColor = 4;
		}
    }

    /* Clear flags */
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    TSI_ClearStatusFlags(TSI0, kTSI_OutOfRangeFlag);
}


/*
 * @brief Initialize the touch sensor
 * 
 * Initializes the touch sensor and the low power timer required for sampling
 * of the timer. Also runs calibration and sets up interrupts for the same
 *
 * @return void
 */
void poll(void)
{
    volatile uint32_t i = 0;
    tsi_config_t tsiConfig_normal = {0};
    lptmr_config_t lptmrConfig;
    memset((void *)&lptmrConfig, 0, sizeof(lptmrConfig));

    /* Initialize standard SDK demo application pins */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    LPTMR_GetDefaultConfig(&lptmrConfig);
    /* TSI default hardware configuration for normal mode */
    TSI_GetNormalModeDefaultConfig(&tsiConfig_normal);

    /* Initialize the LPTMR */
    LPTMR_Init(LPTMR0, &lptmrConfig);
    /* Initialize the TSI */
    TSI_Init(TSI0, &tsiConfig_normal);

    /* Set timer period */
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(LPTMR_USEC_COUNT, LPTMR_SOURCE_CLOCK));

    NVIC_EnableIRQ(TSI0_IRQn);
    TSI_EnableModule(TSI0, true); /* Enable module */

    /*********  CALIBRATION PROCESS ************/
    memset((void *)&buffer, 0, sizeof(buffer));
    TSI_Calibrate(TSI0, &buffer);
    for (i = 0U; i < FSL_FEATURE_TSI_CHANNEL_COUNT; i++)
	{
    	// printf("Calibrated counters for channel %d is: %d \r\n", i, buffer.calibratedData[i]);
	}


    /********** HARDWARE TRIGGER SCAN ********/
    TSI_EnableModule(TSI0, false);
    TSI_EnableHardwareTriggerScan(TSI0, true);
    TSI_EnableInterrupts(TSI0, kTSI_GlobalInterruptEnable);
    TSI_EnableInterrupts(TSI0, kTSI_EndOfScanInterruptEnable);
    TSI_ClearStatusFlags(TSI0, kTSI_EndOfScanFlag);
    /* Select BOARD_TSI_ELECTRODE_1 as detecting electrode. */
    TSI_SetMeasuredChannelNumber(TSI0, BOARD_TSI_ELECTRODE_1);
    TSI_EnableModule(TSI0, true);
    LPTMR_StartTimer(LPTMR0); /* Start LPTMR triggering */
}
