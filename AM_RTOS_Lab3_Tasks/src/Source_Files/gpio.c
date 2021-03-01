//***********************************************************************************
// Include files
//***********************************************************************************
#include "gpio.h"
#include "capsense.h"

//***********************************************************************************
// defined files
//***********************************************************************************

//***********************************************************************************
// global variables
//***********************************************************************************
bool pb0_status;
bool pb1_status;
int cap_status;

//***********************************************************************************
// function prototypes
//***********************************************************************************

//***********************************************************************************
// functions
//***********************************************************************************
/***************************************************************************//**
 * @brief Unified GPIO Interrupt handler (pushbuttons)
 *        PB0 Switches between analog and digital clock modes
 *        PB1 Increments the time by one minute
 *****************************************************************************/
void GPIO_Unified_IRQ(void) {
	/* Get and clear all pending GPIO interrupts */
	uint32_t interruptMask = GPIO_IntGet();
	GPIO_IntClear(interruptMask);

	/* Act on interrupts */
	//Check Button 0
	if (interruptMask & (1 << BUTTON0_pin	)) {
		//get status of the push button
		sample_pb0();

	}
	//Check Button 1
	if (interruptMask & (1 << BUTTON1_pin)) {
		//get status of the push button
		sample_pb1();
	}

	//Update the LEDS accordingly
	set_LED0();
	set_LED1();
}

/***************************************************************************//**
 * @brief GPIO Interrupt handler for even pins
 ******************************************************************************/
void GPIO_EVEN_IRQHandler(void) {
	GPIO_Unified_IRQ();
}

/***************************************************************************//**
 * @brief GPIO Interrupt handler for odd pins
 ******************************************************************************/
void GPIO_ODD_IRQHandler(void) {
	GPIO_Unified_IRQ();
}

/***************************************************************************//**
 * @brief  Sets up all GPIO pins. This case the LEDS and BUTTONS
 ******************************************************************************/
void gpio_open(void) {

	/*LED 0 SETUP*/
	// Set LED ports to be standard output drive with default off (cleared)
	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, LED0_default);

	/*LED 1 SETUP*/
	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, LED1_default);

	/*BUTTON 0 SETUP*/
	GPIO_PinModeSet(BUTTON0_port, BUTTON0_pin, gpioModeInputPull,
	BUTTON0_default);

	/*BUTTON 1 SETUP*/
	GPIO_PinModeSet(BUTTON1_port, BUTTON1_pin, gpioModeInputPull,
	BUTTON1_default);

	/*CAPSENSOR Setup*/
	CAPSENSE_Init();

	//Set global variables to default values
	pb0_status = PB0_STATUS_default;
	pb1_status = PB1_STATUS_default;
	cap_status = CAP_STATUS_default;

	/*Enable interrupts*/
	/*
	#ifdef (LAB2_USE_INTERRUPT)
		//enable a rising and falling edge interrupt on each push button
		GPIO_IntConfig(BUTTON0_port, BUTTON0_pin, true, true, true);
		GPIO_IntConfig(BUTTON1_port, BUTTON1_pin, true, true, true);

		//Enable GPIO interupts
		NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
		NVIC_EnableIRQ(GPIO_EVEN_IRQn);

		NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
		NVIC_EnableIRQ(GPIO_ODD_IRQn);
	#endif
	*/
}

/*
 * Sets the global variable pb0_status to the current state of the button,
 * where 1 means the button is pressed and 0 means that the button is not pressed.
 */
void sample_pb0() {
	pb0_status = !GPIO_PinInGet(BUTTON0_port, BUTTON0_pin);
}

/*
 * @brief Sets the global variable pb1_status to the current state of the button,
 * where 1 means the button is pressed and 0 means that the button is not pressed.
 */
void sample_pb1() {
	pb1_status = !GPIO_PinInGet(BUTTON1_port, BUTTON1_pin);
}

/*
 * Sets the global variable cap_status to the state of the capacitive sensor, where 0 means the left side is pressed, 1 means that
 * the right side is pressed, and -1 means that either no side is pressed or both are.
 */
void sample_cap() {
	CAPSENSE_Sense();
	bool left_pressed = CAPSENSE_getPressed(LEFT_CHANNEL)
			|| CAPSENSE_getPressed(LEFT_C_CHANNEL);
	bool right_pressed = CAPSENSE_getPressed(RIGHT_CHANNEL)
			|| CAPSENSE_getPressed(RIGHT_C_CHANNEL);
	if (left_pressed && !right_pressed) { //left side pressed
		cap_status = 0;
	} else if (!left_pressed && right_pressed) { //right side pressed
		cap_status = 1;
	} else { //both or no side is pressed
		cap_status = -1;
	}

}
/*
 * Turns on LED0 if the left side of the touch sensor is touched or push button 0 is pressed.
 * If both buttons is pressed or the opposite button and side of the touch sensor are pressed,
 * the LED will not turn on.
 * */
void set_LED0() {
	if ((cap_status == 0)
			|| (pb0_status && !pb1_status)) { //Turn on LED0
		GPIO_PinOutSet(LED0_port, LED0_pin);
	} else { //Turn off the LEDS
		GPIO_PinOutClear(LED0_port, LED0_pin);
	}

}
/*
 * Turns on LED1 if the right side of the touch sensor is touched or push button 1 is pressed.
 * If both buttons is pressed or the opposite button and side of the touch sensor are pressed,
 * the LED will not turn on.
 * */
void set_LED1() {
	if ((cap_status == 1)
			|| (!pb0_status && pb1_status)) { //Turn on LED1
		GPIO_PinOutSet(LED1_port, LED1_pin);
	} else { //Turn off the LED
		GPIO_PinOutClear(LED1_port, LED1_pin);
	}

}

/*
 * Turns on LED0 if the left side of the touch sensor is touched or push button 0 is pressed.
 * If both buttons is pressed or the opposite button and side of the touch sensor are pressed,
 * the LED will not turn on.
 * */
void set_LED0_pbOnlyTest() {
	if (pb0_status && !pb1_status) { //Turn on LED0
		GPIO_PinOutSet(LED0_port, LED0_pin);
	} else { //Turn off the LEDS
		GPIO_PinOutClear(LED0_port, LED0_pin);
	}

}
/*
 * Turns on LED1 if the right side of the touch sensor is touched or push button 1 is pressed.
 * If both buttons is pressed or the opposite button and side of the touch sensor are pressed,
 * the LED will not turn on.
 * */
void set_LED1_pbOnlyTest() {
	if (!pb0_status && pb1_status) { //Turn on LED1
		GPIO_PinOutSet(LED1_port, LED1_pin);
	} else { //Turn off the LED
		GPIO_PinOutClear(LED1_port, LED1_pin);
	}

}
