//***********************************************************************************
// Include files
//***********************************************************************************

#include <stdint.h>
#include <stdbool.h>

//***********************************************************************************
// defined files
//***********************************************************************************
//#define LAB2_USE_INTERRUPT
#define	INFINITE_LOOP		true

// Micrium OS Defines
#define  EX_MAIN_START_TASK_PRIO		21u
#define  EX_MAIN_START_TASK_STK_SIZE    512u
#define  EX_BUTTON_INPUT_TASK_PRIO      2u
#define  EX_BUTTON_INPUT_TASK_STK_SIZE  512u
#define  EX_SLIDER_INPUT_TASK_PRIO      1u
#define  EX_SLIDER_INPUT_TASK_STK_SIZE  512u
#define  EX_LED_OUTPUT_TASK_PRIO       	3u
#define  EX_LED_OUTPUT_TASK_STK_SIZE    512u
#define	 EX_BUTTON_INPUT_TASK_DELAY		100u
#define	 EX_SLIDER_INPUT_TASK_DELAY		100u
#define	 EX_LED_OUTPUT_TASK_DELAY		100u

//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
