/*
 * @file setLed_frdm.c
 * @brief C file containing functions used to change LED colour
 *
 * This file conatins the C code that changes the LED colour accouding to
 * input i and print logs.
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */



//Include the relevant header file for the led blink
#include "../frdm_includes/setLed_frdm.h"

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
 * @brief Prints the time for the logger
 * 
 * Change the LED colour accouding to input i and log the values on the 
 * console
 *
 * @return void
 */
void setLed(int i)
{
	if( i >= 6)
	{
		// Check if input > range, and reduce it if needed
		while(i >= 6)
		{
			i -=6;
		}
	}
	//Turn Red LED on and log
	if(i == 0)
	{
		#ifdef frdm_debug
			LED_RED_ON();
			printf("\nRED LED ON ");
			printTimeStamp();
		#endif

		#ifdef frdm_release
			LED_RED_ON();
		#endif
	}
	//Turn Green LED on and log
	else if(i == 2)
	{
		#ifdef frdm_debug
			LED_GREEN_ON();
			printf("\nGREEN LED ON ");
			printTimeStamp();
		#endif

		#ifdef frdm_release
			LED_GREEN_ON();
		#endif
	}
	//Turn Blue LED on and log
	else if(i == 4)
	{
		#ifdef frdm_debug
			LED_BLUE_ON();
			printf("\nBLUE LED ON ");
			printTimeStamp();
		#endif

		#ifdef frdm_release
			LED_BLUE_ON();
		#endif
	}
	//Turn all LEDs off and log
	else if(i == 1 || i == 3 || i == 5)
	{
		#if defined frdm_release || defined frdm_debug
			LED_RED_OFF();
			LED_GREEN_OFF();
			LED_BLUE_OFF();
		#endif

		#ifdef frdm_debug
		{
			if(i == 1)
			{
				printf("\nRED LED OFF ");
				printTimeStamp();
			}
			else if(i == 3)
			{
				printf("\nGREEN LED OFF ");
				printTimeStamp();
			}
			else if(i == 5)
			{
				printf("\nBLUE LED OFF ");
				printTimeStamp();
			}
		}
		#endif
	}
}
