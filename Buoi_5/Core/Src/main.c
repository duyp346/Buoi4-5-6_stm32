
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN PD */
int check=1;
uint16_t milisecond;
uint32_t previousMillis = 0;
uint32_t currentMillis = 0;
void main1(void);
void main2(void);
/* USER CODE END PD */

void SystemClock_Config(void);

/* USER CODE BEGIN 0 */
void main1(){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,0);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
	milisecond=0;
}
void main2(){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,0);
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	milisecond=0;
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 currentMillis = HAL_GetTick();
	if (GPIO_Pin == GPIO_PIN_0 && (currentMillis - previousMillis >10))
  {
    check=!check;
    previousMillis = currentMillis;
  }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == htim1.Instance)
 {
	 milisecond ++;
	 if(milisecond ==10){
		 if(check==0) main1();
		 else main2();
  }
 }
}
/* USER CODE END 0 */

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
