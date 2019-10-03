/*
 * @file utilities_pc.c
 * @brief Contains the PC equivalent of freedom board functions 
 *
 * This file contains the delay, setLed and time stamp functions which are
 * the PC equivalent of the freedom board
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */

//Include relevant libraried for I/O and timekeeping
#include<time.h>
#include<stdio.h>

//Include the function prototypes which are common between multiple source files
#if defined pc_release || defined pc_debug
    #include "../pc_includes/common_pc.h"
#endif



/*
 * @brief Implements delay function
 *  
 * Do nothing for the given amount of time in mS
 *
 * @arguments int delayValue The amount of delay in mS
 * @return void
 */
void delay(int delayValue)
{
    /*returns the number of clock ticks elapsed since the program was launched.*/
    clock_t start1 = clock();  
    clock_t current;
    do{
        /* get current time */
        current=clock();
        /* break loop when the requested number of seconds have elapsed */
    }while((((double)(current-start1)/CLOCKS_PER_SEC)*1000) < delayValue);
}

/*
 * @brief Sets the colour of the LEDs according to the input
 * 
 * Change the LED colour accouding to input i and log the values on the 
 * console
 *
 * @return void
 */
void setLed(int i)
{
    // Check if input > range, and reduce it if needed
    if (i > 5) {
        while (i >= 5) {
            i -= 6;
        }
    }

    //Turn Red LED on and log
    if(i == 0)
    {
        #ifdef pc_debug
            printf("RED LED ON ");
            printTimeStamp();
        #endif

        #ifdef pc_release
            printf("\nRED LED ON\n");
        #endif
    }
    //Turn Green LED on and log
    else if(i == 2)
    {
        #ifdef pc_debug
            printf("GREEN LED ON ");
            printTimeStamp();
        #endif

        #ifdef pc_release
            printf("\nGREEN LED ON\n");
        #endif
    }
    //Turn Blue LED on and log
    else if(i == 4)
    {
        #ifdef pc_debug
            printf("BLUE LED ON ");
            printTimeStamp();
        #endif

        #ifdef pc_release
            printf("\nBLUE LED ON\n");
        #endif
    }
    //Turn all LEDs off and log
    else if(i == 1 || i == 3 || i == 5)
    {
        if(i == 1)
        {
            #ifdef pc_debug
                printf("RED LED OFF ");
                printTimeStamp();
            #endif

            #ifdef pc_release
                printf("\nRED LED OFF\n");
            #endif
        }
        else if(i == 3)
        {
            #ifdef pc_debug
                printf("GREEN LED OFF ");
                printTimeStamp();
            #endif

            #ifdef pc_release
                printf("\nGREEN LED OFF\n");
            #endif
        }
        else if(i == 5)
        {
            #ifdef pc_debug
                printf("BLUE LED OFF ");
                printTimeStamp();
            #endif

            #ifdef pc_release
                printf("\nBLUE LED OFF\n");
            #endif
        }
    }
}

/*
 * @brief Prints the time for the logger
 * 
 * Prints the current time from the RTC and the elapsed time since the last
 * LED transition
 *
 * @return void
 */
//reference: https://stackoverflow.com/questions/646241/
// 				c-run-a-system-command-and-get-output
void printTimeStamp()
{
    char number[100];
    FILE *f = popen("date +\"%T.%3N\"", "r");
    while (fgets(number, 100, f) != NULL)
        printf( "%s", number );
    pclose(f);
}

