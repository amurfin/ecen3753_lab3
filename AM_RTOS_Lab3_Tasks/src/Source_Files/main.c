/***************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for SLSTK3402A
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"
#include "bsp.h"
#include "main.h"
#include "app.h"
#include "gpio.h"
#include "capsense.h"

// Micrium OS Includes
#include  <bsp_os.h>
#include  "bsp.h"
#include  <cpu/include/cpu.h>
#include  <common/include/common.h>
#include  <kernel/include/os.h>
#include  <kernel/include/os_trace.h>
#include  <common/include/lib_def.h>
#include  <common/include/rtos_utils.h>
#include  <common/include/toolchains.h>

volatile uint32_t msTicks; /* counts 1ms timeTicks */

/* LOCAL TASK STATIC PROTOTYPES */
static  void  Ex_MainStartTask (void  *p_arg);
static  void  Ex_ButtonInputTask (void  *p_arg);
static  void  Ex_SliderInputTask (void  *p_arg);
static  void  Ex_LEDOutputTask (void  *p_arg);

// Micrium OS Globals
/* Start Task Stack.                                    */
static  CPU_STK  Ex_MainStartTaskStk[EX_MAIN_START_TASK_STK_SIZE];
/* Start Task TCB.                                      */
static  OS_TCB   Ex_MainStartTaskTCB;
/* Button Input Stack.                                    */
static  CPU_STK  Ex_ButtonInputTaskStk[EX_BUTTON_INPUT_TASK_STK_SIZE];
/* Button Input TCB.                                      */
static  OS_TCB   Ex_ButtonInputTaskTCB;
/* Slider Input Stack.                                    */
static  CPU_STK  Ex_SliderInputTaskStk[EX_SLIDER_INPUT_TASK_STK_SIZE];
/* Slider Input TCB.                                      */
static  OS_TCB   Ex_SliderInputTaskTCB;
/* LED Output Stack.                                    */
static  CPU_STK  Ex_LEDOutputTaskStk[EX_LED_OUTPUT_TASK_STK_SIZE];
/* LED Output TCB.                                      */
static  OS_TCB   Ex_LEDOutputTaskTCB;



int main(void) {
	RTOS_ERR err;
/*
	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;


	CHIP_Init();


	EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;
	EMU_DCDCInit(&dcdcInit);
	em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
	EMU_EM23Init(&em23Init);
	CMU_HFXOInit(&hfxoInit);


	CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	CMU_OscillatorEnable(cmuOsc_HFXO, false, false);


	CMU_ClockEnable(cmuClock_GPIO, true);
*/
	  BSP_SystemInit();
	  CPU_Init();                                                 /* Initialize CPU.                                      */

	  OS_TRACE_INIT();
	  OSInit(&err);                                               /* Initialize the Kernel.                               */
	                                                              /*   Check error code.                                  */
	  APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);

	  // add startupt task & start OS kernel
	  OSTaskCreate(&Ex_MainStartTaskTCB,                          /* Create the Start Task.                               */
	               "Ex Main Start Task",
	                Ex_MainStartTask,
	                DEF_NULL,
	                EX_MAIN_START_TASK_PRIO,
	               &Ex_MainStartTaskStk[0],
	               (EX_MAIN_START_TASK_STK_SIZE / 10u),
	                EX_MAIN_START_TASK_STK_SIZE,
	                0u,
	                0u,
	                DEF_NULL,
	               (OS_OPT_TASK_STK_CLR),
	               &err);
	                                                              /*   Check error code.                                  */
	  APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);

	  OSStart(&err);                                              /* Start the kernel.                                    */
	  /*   Check error code.                                  */
	  APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);

	  /*

	while (1) {

		#if !(LAB2_USE_INTERRUPT)
			//wait 100 ms
			for (int i = 0; i < 100; i++)
				;
			//get status of the push buttons
			sample_pb0();
			sample_pb1();
			//get status of the touch sensor
			sample_cap();
			//set the LEDs accordingly
			set_LED0();
			set_LED1();
			#endif

		#if (LAB2_USE_INTERRUPT)
		 EMU_EnterEM1();
		#endif
	}
	*/
	  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////
// OS Task Functions //
/*
*********************************************************************************************************
*                                          Ex_MainStartTask()
*
* Description : This is the task that will be called by the Startup when all services are initializes
*               successfully.
*
* Argument(s) : p_arg   Argument passed from task creation. Unused, in this case.
*
* Return(s)   : None.
*
* Notes       : None.
*********************************************************************************************************
*/

static  void  Ex_MainStartTask (void  *p_arg)
{
    RTOS_ERR  err;


    PP_UNUSED_PARAM(p_arg);                                     /* Prevent compiler warning.                            */

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();                                /* Initialize interrupts disabled measurement.          */
#endif

    Common_Init(&err);                                          /* Call common module initialization example.           */
    APP_RTOS_ASSERT_CRITICAL(err.Code == RTOS_ERR_NONE, ;);

	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;


	CHIP_Init();


	EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;
	EMU_DCDCInit(&dcdcInit);
	em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
	EMU_EM23Init(&em23Init);
	CMU_HFXOInit(&hfxoInit);


	CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	CMU_OscillatorEnable(cmuOsc_HFXO, false, false);


	CMU_ClockEnable(cmuClock_GPIO, true);

    app_peripheral_setup();

    // add calls to create other tasks
    // button input task
    OSTaskCreate(&Ex_ButtonInputTaskTCB,                          /* Create the Start Task.                               */
                 "Ex Button Input Task",
                  Ex_ButtonInputTask,
                  DEF_NULL,
				  EX_BUTTON_INPUT_TASK_PRIO,
                 &Ex_ButtonInputTaskStk[0],
                 (EX_BUTTON_INPUT_TASK_STK_SIZE / 10u),
				  EX_BUTTON_INPUT_TASK_STK_SIZE,
                  0u,
                  0u,
                  DEF_NULL,
                 (OS_OPT_TASK_STK_CLR),
                 &err);
                                                                /*   Check error code.                                  */
    APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);

    // slider input task
    OSTaskCreate(&Ex_SliderInputTaskTCB,                          /* Create the Start Task.                               */
                 "Ex Slider Input Task",
                  Ex_SliderInputTask,
                  DEF_NULL,
				  EX_LED_OUTPUT_TASK_PRIO,
                 &Ex_SliderInputTaskStk[0],
                 (EX_LED_OUTPUT_TASK_STK_SIZE / 10u),
				 EX_LED_OUTPUT_TASK_STK_SIZE,
                  0u,
                  0u,
                  DEF_NULL,
                 (OS_OPT_TASK_STK_CLR),
                 &err);
                                                                /*   Check error code.                                  */
    APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);

    // led output task
    OSTaskCreate(&Ex_LEDOutputTaskTCB,                          /* Create the Start Task.                               */
                 "Ex LED Output Task",
                  Ex_LEDOutputTask,
                  DEF_NULL,
				  EX_LED_OUTPUT_TASK_PRIO,
                 &Ex_LEDOutputTaskStk[0],
                 (EX_LED_OUTPUT_TASK_STK_SIZE / 10u),
				 EX_LED_OUTPUT_TASK_STK_SIZE,
                  0u,
                  0u,
                  DEF_NULL,
                 (OS_OPT_TASK_STK_CLR),
                 &err);
                                                                /*   Check error code.                                  */
    APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);

    // delete self task & check error code
    OSTaskDel(NULL, &err);
    APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);
}

/*
*********************************************************************************************************
*                                          Ex_ButtonInputTask()
*
* Description : Task to handle button input processing
*
* Argument(s) : p_arg   Argument passed from task creation. Unused, in this case.
*
* Return(s)   : None.
*
* Notes       : None.
*********************************************************************************************************
*/

static  void  Ex_ButtonInputTask (void  *p_arg)
{
    RTOS_ERR  err;


    PP_UNUSED_PARAM(p_arg);                                     /* Prevent compiler warning.                            */

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();                                /* Initialize interrupts disabled measurement.          */
#endif

    // hardware init completed by Ex_MainStartTask()

    // infinite while loop w/task processing
    while (INFINITE_LOOP)
    {
    	sample_pb0();
    	sample_pb1();
    	OSTimeDly(EX_BUTTON_INPUT_TASK_DELAY, OS_OPT_TIME_DLY, &err);
        APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);
    }
}

/*
*********************************************************************************************************
*                                          Ex_LEDOutputTask()
*
* Description : Task to handle output of LEDs
*
* Argument(s) : p_arg   Argument passed from task creation. Unused, in this case.
*
* Return(s)   : None.
*
* Notes       : None.
*********************************************************************************************************
*/

static  void  Ex_LEDOutputTask (void  *p_arg)
{
    RTOS_ERR  err;


    PP_UNUSED_PARAM(p_arg);                                     /* Prevent compiler warning.                            */

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();                                /* Initialize interrupts disabled measurement.          */
#endif

    // hardware init completed by Ex_MainStartTask()

    // infinite while loop w/task processing
    while (INFINITE_LOOP)
    {
    	set_LED0();
    	set_LED1();
    	OSTimeDly(EX_LED_OUTPUT_TASK_DELAY, OS_OPT_TIME_DLY, &err);
        APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);
    }
}

/*
*********************************************************************************************************
*                                          Ex_SliderInputTask()
*
* Description : Task to handle input of cap slider
*
* Argument(s) : p_arg   Argument passed from task creation. Unused, in this case.
*
* Return(s)   : None.
*
* Notes       : None.
*********************************************************************************************************
*/

static  void  Ex_SliderInputTask (void  *p_arg)
{
    RTOS_ERR  err;


    PP_UNUSED_PARAM(p_arg);                                     /* Prevent compiler warning.                            */

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();                                /* Initialize interrupts disabled measurement.          */
#endif

    // hardware init completed by Ex_MainStartTask()

    // infinite while loop w/task processing
    while (INFINITE_LOOP)
    {
    	sample_cap();
    	OSTimeDly(EX_SLIDER_INPUT_TASK_DELAY, OS_OPT_TIME_DLY, &err);
        APP_RTOS_ASSERT_DBG((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE), 1);
    }
}
