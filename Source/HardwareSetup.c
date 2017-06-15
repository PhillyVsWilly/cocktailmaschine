#include "HardwareSetup.h"
#include "main.h"

#define DEBUG_ENABLED 1
#include "debug.h"


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = RCC_PREDIV_DIV2 (2)
  *            PLLMUL                         = RCC_PLL_MUL16 (16)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
	
	
/********************************************/
//Configuration variables
GPIO_InitTypeDef  GPIO_LED;
GPIO_InitTypeDef  GPIO_BUTTON;
ADC_HandleTypeDef HS_ADC_Conf;
/********************************************/
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* HSI Oscillator already ON after system reset, activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}


void hardware_prvHardwareSetup()
{
	
  /* STM32F3xx HAL library initialization:
       - Configure the Flash prefetch
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
	


  /* Configure the system clock to 64 MHz */
  SystemClock_Config();
	
	hADC_Init();
	
	vButton_Init();
	
	vLED_Init();

	
	
	
}

/* Buttons*/
void vButton_Init()
{	
	  /* Enable GPIOC clock */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Configure PC.13 pin as input floating */
  GPIO_BUTTON.Mode = GPIO_MODE_INPUT;
  GPIO_BUTTON.Pull = GPIO_NOPULL;
  GPIO_BUTTON.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC, &GPIO_BUTTON);
	return;
}

void vLED_Init()
{
		/*LED */
  LED2_GPIO_CLK_ENABLE();

  GPIO_LED.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_LED.Pull  = GPIO_PULLUP;
  GPIO_LED.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_LED.Pin = LED2_PIN;
  HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_LED);
}
	

HAL_StatusTypeDef hADC_Init()
{
	
		/***** ADC Einstellungen  *****/
	HS_ADC_Conf.Instance = ADC1;
	
	if(HAL_ADC_GetState(&HS_ADC_Conf) == HAL_ADC_STATE_RESET)
	{
		HS_ADC_Conf.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;      /* ADC clock of STM32F37x devices must not exceed 16MHz (ADC clock of other STMF3 devices can be set up to 72MHz) */
    HS_ADC_Conf.Init.Resolution            = ADC_RESOLUTION_12B;
    HS_ADC_Conf.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    HS_ADC_Conf.Init.ScanConvMode          = ADC_SCAN_DISABLE;              /* Sequencer enabled, many Channels in one Step */
    HS_ADC_Conf.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
    HS_ADC_Conf.Init.LowPowerAutoWait      = DISABLE;
    HS_ADC_Conf.Init.ContinuousConvMode    = DISABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
    HS_ADC_Conf.Init.NbrOfConversion       = 1;                             /* Parameter discarded because sequencer is disabled */
    HS_ADC_Conf.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    HS_ADC_Conf.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
    HS_ADC_Conf.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Software start to trig the 1st conversion manually, without external event */
    HS_ADC_Conf.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because trig by software start */
    HS_ADC_Conf.Init.DMAContinuousRequests = DISABLE;
    HS_ADC_Conf.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
	}
	
	/***** Pin Einstellungen *****/
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*** Configure the GPIOs ***/  
	/* Enable GPIO clock */
	//Depending on the Pin, this must be changed/augmented to GPIOB or GPIOC
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = 0;   //A0
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*** Configure the ADC peripheral ***/ 
	/* Enable ADC clock */
	__HAL_RCC_ADC12_CLK_ENABLE();
    
    /* Initialize ADC */
    if (HAL_ADC_Init(&HS_ADC_Conf) != HAL_OK)
    {
			DPRINT_ERROR("HAL Error\r\n");
      return HAL_ERROR;
    }
    
    /* Run ADC calibration */
    if (HAL_ADCEx_Calibration_Start(&HS_ADC_Conf, ADC_SINGLE_ENDED) != HAL_OK)
    {
			DPRINT_ERROR("HAL Error\r\n");
      return HAL_ERROR;
    }
		
		//Configure ADC Channels: Here the Pins are "connected" to the ADCs
		ADC_ChannelConfTypeDef ChannelConf;
		ChannelConf.Channel	 			= ADC_CHANNEL_1;
		ChannelConf.Rank		 			= ADC_REGULAR_RANK_1;
		ChannelConf.SamplingTime	= ADC_SAMPLETIME_19CYCLES_5;
		ChannelConf.SingleDiff 		= ADC_SINGLE_ENDED;
		ChannelConf.Offset 				= 0;
		
		HAL_ADC_ConfigChannel(&HS_ADC_Conf, &ChannelConf);
		
  
	return HAL_OK;
}
	

