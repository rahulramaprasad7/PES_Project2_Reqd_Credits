/*
 * @file rtcInit.c
 * @brief C  file containing functions used to initialize the timers
 *
 * This file contains the RTC and sysTick initialization and interrupt 
 * configuration for the freedom board
 *
 * @authors Rahul Ramaprasad, Prayag Milan Desai
 * @date October 3 2019
 * @verison 1.0
 */


//Include the drivers required for the RTC
#include "../CMSIS/MKL25Z4.h"
#include "../board/peripherals.h"
#include "../board/board.h"
#include "../board/pin_mux.h"

//reference: https://community.nxp.com/docs/DOC-94734

/*
 * @brief Initializes the RTC and the sysTick timer
 * 
 * Initializes the RTC registers and enables the relevant clock required
 * Also enables the RTC seconds interrupt
 * 
 * @return void
 */
void rtc_init()
{
	//Init clocks and peripherals
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	//Enable clocks to all ports
	SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK
			| SIM_SCGC5_PORTB_MASK
			| SIM_SCGC5_PORTC_MASK
			| SIM_SCGC5_PORTD_MASK
			| SIM_SCGC5_PORTE_MASK );

	MCG->C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG->C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow (~32Khz)

	PORTC->PCR[1] |= (PORTC->PCR[1] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(1);
	SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC


	SIM->SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz
	PORTC->PCR[3] |= (PORTC->PCR[3] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(5);
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear RTC Control Registers*/
	RTC->CR  = RTC_CR_SWR_MASK;
	RTC->CR  &= ~RTC_CR_SWR_MASK;

	//Clear RTC interrupt flags
	if (RTC->SR & RTC_SR_TIF_MASK){
		RTC->TSR = 0x00000000;   //  this action clears the TIF
	}

	/*Set time compensation parameters*/
	RTC->TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

	//Enable interrupts in the NVIC
	NVIC->ICPR[1<<16] |= 1;
	NVIC->ISER[1<<16] |= 1;


	/*Enable Seconds Interrupt*/
	RTC->IER |= 0x10;

	/*RTC enable*/
	RTC->SR |= RTC_SR_TCE_MASK;

	/*Configure the timer seconds registers*/
	RTC->TSR = 0xFF;

	//Enable the RTC seconds interrupt
	NVIC_EnableIRQ(RTC_Seconds_IRQn);

	//Reinit the board clocks, in case any of them have changed
	BOARD_InitBootPins();

	//Give the TSR an initial value
	RTC->TSR = 0xFF;
	//Enable timer
	RTC->SR |= RTC_SR_TCE_MASK;

	//Enable the sysTick timer for an interrupt in every 1mS
	SysTick_Config(SystemCoreClock / 1000);
}
