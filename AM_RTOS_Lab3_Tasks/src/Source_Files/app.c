/*
 * letimer.c
 *
 *  Created on: May 13, 2019
 *      Author: kgraham
 */

//***********************************************************************************
// Include files
//***********************************************************************************
#include "app.h"

//***********************************************************************************
// defined files
//***********************************************************************************

//***********************************************************************************
// global variables
//***********************************************************************************

//***********************************************************************************
// function
//***********************************************************************************

/***************************************************************************//**
 * @brief
 *   SysTick_Handler. Interrupt Service Routine for system tick counter
 ******************************************************************************/
void SysTick_Handler(void)
{
  //Sample the touch sensor
	sample_cap();
	//set the LEDs accordingly
	set_LED0();
	set_LED1();
}


/***************************************************************************//**
 * @brief
 *   Sets up the SysTick timer to trigger every sample_period.
 *
 * @param sample_period
 * 		The time in ms to wait between each triggered interrupt.
 ******************************************************************************/
void SysTick_init(int sample_period) {
	if (SysTick_Config(SystemCoreClockGet()* sample_period / 1000)) {
		while (1);
	}
}

/***************************************************************************//**
 * @brief
 *   Sets up the peripherals used in the application.
 ******************************************************************************/
void app_peripheral_setup(void) {
//	cmu_open();
	gpio_open();
	/*
	//Set up the SysTick timer
	#ifdef (LAB2_USE_INTERRUPT)
		SysTick_init(100); //Set to trigger every 100 ms
	#endif
	*/
}



