
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/*MA SO DE TEST
189 33 204 129 76 201 44 98 143 21 90 67 85 p
*/
typedef enum bool{false,true}bool;
uint8_t receive;
char arr_receive[100];
bool en_write_arr=false ;
bool done_frame=false;
char count=0;
int mangSo[100];
int soluongso=0;
int dodai=0;
bool flag=false;
int sohientai=0;
char hienthi[10];
/* USER CODE END Includes */

void SystemClock_Config(void);

/* USER CODE BEGIN 0 */

void send_uart (char*string){
	uint8_t len = strlen(string);
	HAL_UART_Transmit(&huart2,(uint8_t *)string,len,2000);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 if(huart ->Instance ==huart2.Instance )
 {
	 if(en_write_arr == false ){
		 en_write_arr=true ;
		 done_frame=false;
 }
 if(en_write_arr==true){
	arr_receive[count]=receive;
	 if(arr_receive[count]>= '0' &&arr_receive[count]<='9') {
		 sohientai=sohientai *10 + (arr_receive[count]-48);
	 }
	if(arr_receive[count] == ' '){
		mangSo[soluongso++]=sohientai ;
		sohientai =0;
		dodai++;
	}
		for (int i = 0; i < dodai - 1; i++) {
      for (int j = 0; j <dodai - i - 1; j++) {
        if ((mangSo[j] > mangSo[j + 1]) ) {
          int temp = mangSo[j];
          mangSo[j] = mangSo[j + 1];
          mangSo[j + 1] = temp;
        }
      }
    }
		 count++;
 }
 if(receive=='p' && en_write_arr == true){
	 en_write_arr =false;
	 done_frame = true;
	 flag =true;
 }
 HAL_UART_Receive_IT (&huart2 ,&receive ,1);
 }
}
/* USER CODE END 0 */

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT (&huart2 ,&receive ,1);
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(flag ==true){
		 for(int k=0;k<dodai;k++){
			char hienthi2[10];
			sprintf(hienthi2,"\n%d\n",mangSo[k]);
			send_uart(hienthi2);
		 }
		send_uart("Finish\n");	
		count=0; 
		soluongso=0;
		dodai =0;
		memset(arr_receive,0,100);
		memset(mangSo,0,100);
		flag =false;			
	 }

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
  RCC_OscInitStruct.PLL.PLLN = 100;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
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
#endif 
