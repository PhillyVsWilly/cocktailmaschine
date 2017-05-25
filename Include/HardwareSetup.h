#ifndef HardwareSetup_H_
#define HardwareSetup_H_

#include "stm32f3xx_hal.h"

/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef  GPIO_LED;
static GPIO_InitTypeDef  GPIO_BUTTON;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void hardware_prvHardwareSetup(void);
static void Error_Handler(void);

#endif
