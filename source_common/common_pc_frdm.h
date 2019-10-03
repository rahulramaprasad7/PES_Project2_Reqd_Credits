 /*
 * @file common_pc_frdm.h
 * @brief File contains variable declarations common between PC and KL25Z
 *
 * All the variables that can be used in both PC and the KL25Z board are
 * declared here
 *
 * @author Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @version 1.0
 */

#ifndef COMMON_PC_FRDM_H_
#define COMMON_PC_FRDM_H_

//Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Index of the Look Up Table
int LUTindex = 0;

//ledIndex indicates the colour of the LED, as well as it's status
int ledIndex = 0;

//lookUpTable has all the delay value of the LED pattern, in milliseconds
int lookUpTable[20] = {3000,1000,2000,600,1000,400,1000,200,500,100,500,100, \
    500,100,1000,200,1000,400,2000,600};

#endif
