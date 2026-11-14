/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : STM32 + ESP8266 + MQTT + BME280
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ESPLib.h"
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
    uint16_t T1; int16_t T2; int16_t T3;
    uint16_t P1; int16_t P2; int16_t P3; int16_t P4; int16_t P5;
    int16_t  P6; int16_t P7; int16_t P8; int16_t P9;
    uint8_t  H1; int16_t H2; uint8_t H3; int16_t H4; int16_t H5; int8_t H6;
} BME280_Calib_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BME280_ADDR_LOW     (0x76 << 1)
#define BME280_ADDR_HIGH    (0x77 << 1)
#define BME280_CHIP_ID      0x60
#define BME280_REG_ID       0xD0
#define BME280_REG_RESET    0xE0
#define BME280_REG_CTRL_HUM 0xF2
#define BME280_REG_CTRL_MEAS 0xF4
#define BME280_REG_CONFIG   0xF5
#define BME280_REG_DATA     0xF7
#define BME280_I2C_TIMEOUT  100
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
I2C_HandleTypeDef hi2c1;
static BME280_Calib_t cal;
static uint16_t bme_addr = BME280_ADDR_LOW;
static int32_t t_fine;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
static void MY_I2C1_Init(void);
static HAL_StatusTypeDef BME280_Init(void);
static HAL_StatusTypeDef BME280_Read(int32_t *temp_c100, uint32_t *press_pa, uint32_t *hum_q10);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* ---------------- I2C1 init (PB6 = SCL, PB7 = SDA) ---------------- */
static void MY_I2C1_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    gpio.Pin       = GPIO_PIN_6 | GPIO_PIN_7;
    gpio.Mode      = GPIO_MODE_AF_OD;
    gpio.Pull      = GPIO_PULLUP;
    gpio.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &gpio);

    hi2c1.Instance             = I2C1;
    hi2c1.Init.ClockSpeed      = 100000;
    hi2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1     = 0;
    hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2     = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
}

/* ---------------- BME280 low level ---------------- */
static HAL_StatusTypeDef bme_read(uint8_t reg, uint8_t *buf, uint16_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, bme_addr, reg, I2C_MEMADD_SIZE_8BIT,
                            buf, len, BME280_I2C_TIMEOUT);
}

static HAL_StatusTypeDef bme_write(uint8_t reg, uint8_t val)
{
    return HAL_I2C_Mem_Write(&hi2c1, bme_addr, reg, I2C_MEMADD_SIZE_8BIT,
                             &val, 1, BME280_I2C_TIMEOUT);
}

static HAL_StatusTypeDef BME280_Init(void)
{
    uint8_t id = 0;
    uint8_t c1[26];
    uint8_t c2[7];

    /* Find the sensor at 0x76 or 0x77 */
    bme_addr = BME280_ADDR_LOW;
    if (bme_read(BME280_REG_ID, &id, 1) != HAL_OK)
    {
        bme_addr = BME280_ADDR_HIGH;
        if (bme_read(BME280_REG_ID, &id, 1) != HAL_OK)
        {
            return HAL_ERROR;           /* not found on I2C */
        }
    }
    if (id != BME280_CHIP_ID)
    {
        return HAL_ERROR;               /* 0x58 = BMP280 (no humidity!) */
    }

    /* Soft reset, wait for NVM copy */
    bme_write(BME280_REG_RESET, 0xB6);
    HAL_Delay(10);

    /* Calibration data */
    if (bme_read(0x88, c1, 26) != HAL_OK) return HAL_ERROR;   /* 0x88..0xA1 */
    if (bme_read(0xE1, c2, 7)  != HAL_OK) return HAL_ERROR;   /* 0xE1..0xE7 */

    cal.T1 = (uint16_t)(c1[1] << 8 | c1[0]);
    cal.T2 = (int16_t)(c1[3] << 8 | c1[2]);
    cal.T3 = (int16_t)(c1[5] << 8 | c1[4]);
    cal.P1 = (uint16_t)(c1[7] << 8 | c1[6]);
    cal.P2 = (int16_t)(c1[9] << 8 | c1[8]);
    cal.P3 = (int16_t)(c1[11] << 8 | c1[10]);
    cal.P4 = (int16_t)(c1[13] << 8 | c1[12]);
    cal.P5 = (int16_t)(c1[15] << 8 | c1[14]);
    cal.P6 = (int16_t)(c1[17] << 8 | c1[16]);
    cal.P7 = (int16_t)(c1[19] << 8 | c1[18]);
    cal.P8 = (int16_t)(c1[21] << 8 | c1[20]);
    cal.P9 = (int16_t)(c1[23] << 8 | c1[22]);
    cal.H1 = c1[25];

    cal.H2 = (int16_t)(c2[1] << 8 | c2[0]);
    cal.H3 = c2[2];
    cal.H4 = (int16_t)(((int16_t)(int8_t)c2[3] * 16) | (c2[4] & 0x0F));
    cal.H5 = (int16_t)(((int16_t)(int8_t)c2[5] * 16) | (c2[4] >> 4));
    cal.H6 = (int8_t)c2[6];

    /* Config: humidity x1 (must be written BEFORE ctrl_meas),
       temp x1, pressure x1, normal mode, standby 1 s, filter off */
    if (bme_write(BME280_REG_CTRL_HUM, 0x01) != HAL_OK) return HAL_ERROR;
    if (bme_write(BME280_REG_CONFIG,   0xA0) != HAL_OK) return HAL_ERROR;
    if (bme_write(BME280_REG_CTRL_MEAS, 0x27) != HAL_OK) return HAL_ERROR;

    HAL_Delay(20);
    return HAL_OK;
}

/* ---------------- Compensation (Bosch datasheet, 32-bit integer) ---------------- */
static int32_t comp_temp(int32_t adc_T)
{
    int32_t var1, var2;
    var1 = ((((adc_T >> 3) - ((int32_t)cal.T1 << 1))) * ((int32_t)cal.T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)cal.T1)) *
              ((adc_T >> 4) - ((int32_t)cal.T1))) >> 12) * ((int32_t)cal.T3)) >> 14;
    t_fine = var1 + var2;
    return (t_fine * 5 + 128) >> 8;              /* 0.01 degC */
}

static uint32_t comp_press(int32_t adc_P)
{
    int32_t var1, var2;
    uint32_t p;

    var1 = (t_fine >> 1) - (int32_t)64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)cal.P6);
    var2 = var2 + ((var1 * ((int32_t)cal.P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)cal.P4) << 16);
    var1 = (((cal.P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) +
            ((((int32_t)cal.P2) * var1) >> 1)) >> 18;
    var1 = ((((32768 + var1)) * ((int32_t)cal.P1)) >> 15);
    if (var1 == 0) return 0;

    p = (((uint32_t)(((int32_t)1048576) - adc_P) - (var2 >> 12))) * 3125;
    if (p < 0x80000000)
        p = (p << 1) / ((uint32_t)var1);
    else
        p = (p / (uint32_t)var1) * 2;

    var1 = (((int32_t)cal.P9) * ((int32_t)(((p >> 3) * (p >> 3)) >> 13))) >> 12;
    var2 = (((int32_t)(p >> 2)) * ((int32_t)cal.P8)) >> 13;
    p = (uint32_t)((int32_t)p + ((var1 + var2 + cal.P7) >> 4));
    return p;                                    /* Pa */
}

static uint32_t comp_hum(int32_t adc_H)
{
    int32_t v = t_fine - (int32_t)76800;

    v = (((((adc_H << 14) - (((int32_t)cal.H4) << 20) -
            (((int32_t)cal.H5) * v)) + (int32_t)16384) >> 15) *
         (((((((v * (int32_t)cal.H6) >> 10) *
              (((v * (int32_t)cal.H3) >> 11) + (int32_t)32768)) >> 10) +
            (int32_t)2097152) * (int32_t)cal.H2 + 8192) >> 14));

    v = v - (((((v >> 15) * (v >> 15)) >> 7) * (int32_t)cal.H1) >> 4);
    if (v < 0) v = 0;
    if (v > 419430400) v = 419430400;
    return (uint32_t)(v >> 12);                  /* %RH in Q22.10 */
}

static HAL_StatusTypeDef BME280_Read(int32_t *temp_c100, uint32_t *press_pa, uint32_t *hum_q10)
{
    uint8_t d[8];
    int32_t adc_P, adc_T, adc_H;

    if (bme_read(BME280_REG_DATA, d, 8) != HAL_OK) return HAL_ERROR;

    adc_P = ((int32_t)d[0] << 12) | ((int32_t)d[1] << 4) | (d[2] >> 4);
    adc_T = ((int32_t)d[3] << 12) | ((int32_t)d[4] << 4) | (d[5] >> 4);
    adc_H = ((int32_t)d[6] << 8)  |  d[7];

    *temp_c100 = comp_temp(adc_T);      /* must be first: sets t_fine */
    *press_pa  = comp_press(adc_P);
    *hum_q10   = comp_hum(adc_H);
    return HAL_OK;
}
/* USER CODE END 0 */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  HAL_Init();

  /* USER CODE BEGIN Init */
  uint32_t previousTime = HAL_GetTick();
  /* USER CODE END Init */

  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  /* 0. Sensor first */
  MY_I2C1_Init();
  uint8_t bmeOK = (BME280_Init() == HAL_OK);

  /* 1. Wi-Fi + MQTT (unchanged) */
  ESP8266_Init(StationMode, huart1);
  ESP8266_wifiConnect("SNUC", "snu12345");
  ESP8266_portConnect("TCP", "broker.emqx.io", "1883");

  MQTT_InitTypeDef_t mqttSetting;
  mqttSetting.keepAlive = 500;
  mqttSetting.connectFlag = CleanSession;
  mqttSetting.clientID = "Sathvika";
  MQTT_connectBroker(&mqttSetting);

  char payload[96];
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN 3 */
    if (HAL_GetTick() - previousTime >= 1000)
    {
        previousTime = HAL_GetTick();

        if (!bmeOK)
        {
            /* try to bring the sensor up again if it wasn't found */
            bmeOK = (BME280_Init() == HAL_OK);
        }

        int32_t  t100;
        uint32_t pPa, hQ10;

        if (bmeOK && BME280_Read(&t100, &pPa, &hQ10) == HAL_OK)
        {
            uint32_t h100 = (hQ10 * 100u) >> 10;          /* %RH x100 */
            uint32_t tAbs = (t100 < 0) ? (uint32_t)(-t100) : (uint32_t)t100;

            snprintf(payload, sizeof(payload),
                     "{\"temp\":%s%lu.%02lu,\"hum\":%lu.%02lu,\"pres\":%lu.%02lu}",
                     (t100 < 0) ? "-" : "",
                     (unsigned long)(tAbs / 100), (unsigned long)(tAbs % 100),
                     (unsigned long)(h100 / 100), (unsigned long)(h100 % 100),
                     (unsigned long)(pPa / 100),  (unsigned long)(pPa % 100));
            /* temp in degC, hum in %RH, pres in hPa */
        }
        else
        {
            snprintf(payload, sizeof(payload), "{\"error\":\"BME280 not found\"}");
            bmeOK = 0;
        }

        MQTT_publishTopic("stm32/Anam/data", payload, QoS0);
    }
    /* USER CODE END 3 */
  }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

static void MX_USART1_UART_Init(void)
{
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
}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif