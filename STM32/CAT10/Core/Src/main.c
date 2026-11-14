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
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Send data to PC/PuTTY */
void UART_Send(char *msg)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)msg,
                      strlen(msg), HAL_MAX_DELAY);
}

/* Send data to Wemos/ESP8266 */
void Wemos_Send(char *msg)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)msg,
                      strlen(msg), HAL_MAX_DELAY);
}

/* Send one AT command and receive its response */
void Send_AT_Command(char *command)
{
    uint8_t rx;
    uint8_t received = 0;

    /* Display the command being sent on PuTTY */
    UART_Send(">> ");
    UART_Send(command);
    UART_Send("\r\n");

    /* Send the AT command to Wemos/ESP8266 */
    Wemos_Send(command);
    Wemos_Send("\r\n");

    /* Receive the response from Wemos/ESP8266 */
    while (HAL_UART_Receive(&huart1, &rx, 1, 5000) == HAL_OK)
    {
        received = 1;

        /* Display the received response on PuTTY */
        HAL_UART_Transmit(&huart2, &rx, 1, HAL_MAX_DELAY);
    }

    /* Check whether any response was received */
    if (received == 0)
    {
        UART_Send("No response from Wemos\r\n");
    }

    /* Add a blank line before the next command */
    UART_Send("\r\n");

    /* Small delay before sending the next command */
    HAL_Delay(1000);
}

void Send_Webpage(int id)
{
    char command[40];

    char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 23\r\n"
        "Connection: close\r\n"
        "\r\n"
        "Hi, hello from bluepill";

    sprintf(command, "AT+CIPSEND=%d,%d",
            id, (int)strlen(response));

    Wemos_Send(command);
    Wemos_Send("\r\n");

    uint8_t ch;
    int prompt_found = 0;

    for (int i = 0; i < 50; i++)
    {
        if (HAL_UART_Receive(&huart1, &ch, 1, 100) == HAL_OK)
        {
            if (ch == '>')
            {
                prompt_found = 1;
                break;
            }
        }
    }

    if (prompt_found)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)response,
                          strlen(response), 5000);

        UART_Send("\r\nHTTP response sent\r\n");

        HAL_Delay(500);

        sprintf(command, "AT+CIPCLOSE=%d", id);
        Wemos_Send(command);
        Wemos_Send("\r\n");
    }
    else
    {
        UART_Send("\r\nESP8266 send prompt not received\r\n");
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration------------------------------------------------------*/

    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    /* USER CODE BEGIN 2 */

    /* Startup messages */
    UART_Send("STM32 Wemos UART TEST\r\n");
    UART_Send("Communication Started\r\n\r\n");

    /* ===== SEND AT COMMANDS ===== */

    /* Check whether ESP8266 responds */
    Send_AT_Command("AT");

    /* Get ESP8266 firmware version */
    Send_AT_Command("AT+GMR");

    /* Configure ESP8266 as Wi-Fi station */
    Send_AT_Command("AT+CWMODE=1");

    /* Scan for available Wi-Fi networks */
    Send_AT_Command("AT+CWLAP");

    /* Connect ESP8266 to the Wi-Fi network */
    Send_AT_Command("AT+CWJAP=\"SNUC\",\"snu12345\"");

    /* Get network information including IP address */
    Send_AT_Command("AT+CIFSR");

    /* Check current Wi-Fi connection status */
    Send_AT_Command("AT+CIPSTATUS");

    Send_AT_Command("AT+CIPMUX=1");
		Send_AT_Command("AT+CIPSERVER=1,80");
    /* ============================ */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    /* Stay here - do NOT send AT commands again */
    
while (1)
{
    static char rxBuffer[512] = {0};
    static int pos = 0;
    uint8_t ch;

    if (HAL_UART_Receive(&huart1, &ch, 1, 100) == HAL_OK)
    {
        // Display incoming ESP8266 data on the PC terminal
        HAL_UART_Transmit(&huart2, &ch, 1, HAL_MAX_DELAY);

        if (pos < (int)sizeof(rxBuffer) - 1)
        {
            rxBuffer[pos++] = ch;
            rxBuffer[pos] = '\0';
        }
        else
        {
            memset(rxBuffer, 0, sizeof(rxBuffer));
            pos = 0;
            continue;
        }

        char *ipd = strstr(rxBuffer, "+IPD,");

        if (ipd != NULL)
        {
            char *colon = strchr(ipd, ':');

            // Wait for the complete HTTP request header
            if (colon != NULL &&
                strstr(colon + 1, "\r\n\r\n") != NULL)
            {
                int id;

                if (sscanf(ipd, "+IPD,%d,", &id) == 1 &&
                    strstr(colon + 1, "GET /") != NULL)
                {
                    UART_Send("\r\nBrowser request received!\r\n");

                    // Clear the buffer before sending the response
                    memset(rxBuffer, 0, sizeof(rxBuffer));
                    pos = 0;

                    Send_Webpage(id);
                }
            }
        }
    }
}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                   RCC_CLOCKTYPE_SYSCLK |
                                   RCC_CLOCKTYPE_PCLK1 |
                                   RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                            FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{
    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{
    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */
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
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

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

    /* USER CODE END 6 */
}

#endif /* USE_FULL_ASSERT */