/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
#define WIFI_NAME     "SNUC"
#define WIFI_PASSWORD "snu12345"

extern UART_HandleTypeDef huart6;

char cmd[150];
char request[1200];
char response[1024];
char rxBuffer[500];

uint8_t rx;
int link_id;

UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	
int sendAT(char *command, uint32_t timeout)
{
    memset(rxBuffer, 0, sizeof(rxBuffer));

    HAL_UART_Transmit(&huart6, (uint8_t *)command,
                      strlen(command), HAL_MAX_DELAY);

    uint32_t start = HAL_GetTick();
    int i = 0;

    while (HAL_GetTick() - start < timeout)
    {
        if (HAL_UART_Receive(&huart6, &rx, 1, 100) == HAL_OK)
        {
            if (i < sizeof(rxBuffer) - 1)
            {
                rxBuffer[i++] = rx;
                rxBuffer[i] = '\0';
            }

            if (strstr(rxBuffer, "OK") != NULL ||
                strstr(rxBuffer, "ERROR") != NULL ||
                strstr(rxBuffer, "FAIL") != NULL)
            {
                break;
            }
        }
    }

    return (strstr(rxBuffer, "OK") != NULL &&
            strstr(rxBuffer, "ERROR") == NULL &&
            strstr(rxBuffer, "FAIL") == NULL);
}


int waitForPrompt(void)
{
    uint32_t start = HAL_GetTick();

    while (HAL_GetTick() - start < 5000)
    {
        if (HAL_UART_Receive(&huart6, &rx, 1, 100) == HAL_OK)
        {
            if (rx == '>')
                return 1;
        }
    }

    return 0;
}


int receiveRequest(void)
{
    int i = 0;
    memset(request, 0, sizeof(request));

    uint32_t start = HAL_GetTick();

    while (HAL_GetTick() - start < 10000 &&
           i < sizeof(request) - 1)
    {
        if (HAL_UART_Receive(&huart6, &rx, 1, 100) == HAL_OK)
        {
            request[i++] = (char)rx;
            request[i] = '\0';

            if (strstr(request, "\r\n\r\n") != NULL)
                return 1;
        }
    }

    return 0;
}

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	 HAL_Delay(2000);

    

    /* Test ESP8266 */
    if (!sendAT("AT\r\n", 3000))
        Error_Handler();

    /* Set Wi-Fi station mode */
    if (!sendAT("AT+CWMODE=1\r\n", 3000))
        Error_Handler();

    
    snprintf(cmd, sizeof(cmd),
             "AT+CWJAP=\"%s\",\"%s\"\r\n",
             WIFI_NAME, WIFI_PASSWORD);

    if (!sendAT(cmd, 40000))
        Error_Handler();

    
    sendAT("AT+CIFSR\r\n", 5000);

    
    if (!sendAT("AT+CIPMUX=1\r\n", 3000))
        Error_Handler();

    
    if (!sendAT("AT+CIPSERVER=1,80\r\n", 3000))
        Error_Handler();

    
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		 if (receiveRequest())
        {
            char *ipd = strstr(request, "+IPD,");

            if (ipd != NULL &&
                sscanf(ipd, "+IPD,%d,", &link_id) == 1)
            {
               
              char random_letter = 'A' + (rand() % 26);
                    char body[200];

int body_length = snprintf(
    body, sizeof(body),
    "<html><body>"
    "<h1>STM32 IoT Node</h1>"
    "<p>Hello from STM32</p>"
    "<p>Random letter = %c</p>"
    "</body></html>",
    random_letter
);

if (body_length < 0 || body_length >= sizeof(body))
    continue;

                body_length = strlen(body);

                
                int response_length = snprintf(
                    response, sizeof(response),
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: %d\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "%s",
                    body_length, body
                );

                if (response_length <= 0 ||
                    response_length >= sizeof(response))
                    continue;

               
                snprintf(cmd, sizeof(cmd),
                         "AT+CIPSEND=%d,%d\r\n",
                         link_id, response_length);

                HAL_UART_Transmit(
                    &huart6, (uint8_t *)cmd,
                    strlen(cmd), HAL_MAX_DELAY
                );

                
                if (waitForPrompt())
                {
                    
                    HAL_UART_Transmit(
                        &huart6, (uint8_t *)response,
                        response_length, HAL_MAX_DELAY
                    );

                    HAL_Delay(500);
                }

                
                snprintf(cmd, sizeof(cmd),
                         "AT+CIPCLOSE=%d\r\n", link_id);

                sendAT(cmd, 3000);
            }
        }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
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

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
