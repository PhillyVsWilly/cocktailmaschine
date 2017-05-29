/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    16-December-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F3xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "HardwareSetup.h"

#include "FreeRTOS.h"
#include "task.h"

#include "Sensors.h"
#include "Evaluation.h"
#include "Actuators.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAIN_CYCLE_PRIORITY (tskIDLE_PRIORITY+1)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
InputValues_t Input_Storage;
OutputValues_t Output_Storage;
SystemState_t System_State;
/* Private function prototypes -----------------------------------------------*/


/* Task Functions */
static void vMainCycle(void* pvParameters);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

	
	
	/* Hardware Initial Settings */
	hardware_prvHardwareSetup();
	
	xTaskCreate(vMainCycle, "Main Cycle", 100, NULL, MAIN_CYCLE_PRIORITY, NULL);
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	
			BSP_LED_On(LED2);
	


}


/***********************/
//Tasks
/***********************/
/* Once every 1000ms, the following Code is executed:
* Read all Sensor Values (in this case: The blue Button)
*Based on the Sensor Values: Calculate the output values 
*Write the output values
*The starting time is stored in the beginning. vTaskDelayUntil() then waits until it is 1000ms after the stored time to make the 
*task ready again.*/

void vMainCycle(void* pvParameters)
{
	  /* -3- Toggle IOs in an infinite loop */
  while (1)
  {
		

		//Store Tick Count
		TickType_t xLastWakeTime;
		xLastWakeTime = xTaskGetTickCount();
		
		//Sensoren lesen
		vReadSensorValues(&Input_Storage);
				
		//Berechnen
		vEvaluate(Input_Storage,&System_State, &Output_Storage);

		//Ausgabe schreiben
		vWriteActuatorValues(Output_Storage);
		
		
		//Delay until next Second
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));	
		
		
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

