//***********************************************************************************
// Include files
//***********************************************************************************
#include "em_gpio.h"

//***********************************************************************************
// defined files
//***********************************************************************************

// LED 0 pin is
#define	LED0_port		gpioPortF
#define LED0_pin		04u
#define LED0_default	false 	// Default false (0) = off, true (1) = on
// LED 1 pin is
#define LED1_port		gpioPortF
#define LED1_pin		05u
#define LED1_default	false	// Default false (0) = off, true (1) = on

// BUTTON 0 pin is
#define	BUTTON0_port	gpioPortF
#define BUTTON0_pin		06u
#define BUTTON0_default	true	// Default false (0) = off, true (1) = on
// BUTTON 1 pin is
#define BUTTON1_port	gpioPortF
#define BUTTON1_pin		07u
#define BUTTON1_default	true	// Default false (0) = off, true (1) = on

// CAPSENSOR Channel definitions
#define LEFT_CHANNEL    0
#define LEFT_C_CHANNEL  1
#define RIGHT_CHANNEL   2
#define RIGHT_C_CHANNEL 3

//Defaults for global variables
#define PB0_STATUS_default false
#define PB1_STATUS_default false
#define CAP_STATUS_default -1

//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
void gpio_open(void);
void sample_pb0();
void sample_cap();
void sample_pb1();
void set_LED0();
void set_LED1();
void set_LED0_pbOnlyTest();
void set_LED1_pbOnlyTest();
