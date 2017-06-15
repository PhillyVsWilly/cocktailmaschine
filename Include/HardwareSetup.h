#ifndef HardwareSetup_H_
#define HardwareSetup_H_

#include "stm32f3xx_hal.h"

/* Private variables ---------------------------------------------------------*/
extern GPIO_InitTypeDef  GPIO_LED;
extern GPIO_InitTypeDef  GPIO_BUTTON;
extern ADC_HandleTypeDef HS_ADC_Conf;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void hardware_prvHardwareSetup(void);
static void Error_Handler(void);

static HAL_StatusTypeDef hADC_Init(void);
	
static void vButton_Init(void);
	
static void vLED_Init(void);

#endif
