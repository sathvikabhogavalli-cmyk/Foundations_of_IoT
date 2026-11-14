# CONTINUOUS LAB EVALUATION – 12

**DATE:** 23-10-2026

**COURSE:** 25CS2741 – Fundamentals of Internet of Things + Lab

## NAME OF EXPERIMENT

BME280 Sensor Interfacing Using I²C and Bosch Sensor API

## HARDWARE SETUP / PLATFORM

- STM32 Nucleo Development Board
- BME280 Temperature, Pressure and Humidity Sensor
- STM32CubeMX
- Keil MDK / Keil µVision
- STM32 HAL Libraries
- Bosch Sensortec BME280 Sensor API
- I²C Communication Interface
- Debugger
- UART Terminal
- ESP8266 Wi-Fi Module (for HTTP communication)

## TASK NO

Develop an STM32-based environmental sensing application to interface a BME280 sensor using the I²C protocol and obtain compensated temperature, pressure and humidity measurements.

Use the official Bosch Sensortec BME280 Sensor API as the reference driver implementation.

The application shall acquire sensor measurements, apply the Bosch compensation algorithms and provide the measured values for display or transmission.

## STEP 1: DOWNLOAD AND ARRANGE THE DRIVER FILES

Download the official Bosch Sensortec BME280 Sensor API from:

https://github.com/boschsensortec/BME280_SensorAPI

### REQUIRED DRIVER FILES

- `bme280.c`
- `bme280.h`
- `bme280_defs.h`

### PROJECT FILE ORGANIZATION

Place the driver files in the STM32 project directory.

```text
STM32_Project/
├── Core/
│   ├── Inc/
│   │   ├── bme280.h
│   │   └── bme280_defs.h
│   └── Src/
│       └── bme280.c
```

### FUNCTIONAL REQUIREMENTS

1. Download the official Bosch BME280 Sensor API.
2. Copy `bme280.c` into `Core/Src`.
3. Copy `bme280.h` and `bme280_defs.h` into `Core/Inc`.
4. Add `bme280.c` to the Keil project workspace.
5. Verify the include paths in the Keil target configuration.
6. Ensure the Bosch driver header files are accessible during compilation.

## STEP 2: CONFIGURE THE BME280 SENSOR INTERFACE

Configure the STM32 I²C peripheral to communicate with the BME280 sensor.

### FUNCTIONAL REQUIREMENTS

1. Configure I²C communication using STM32CubeMX.
2. Initialize the I²C peripheral using STM32 HAL.
3. Configure the BME280 device structure.
4. Assign the I²C read and write functions.
5. Configure the delay callback function.
6. Initialize the BME280 sensor using the Bosch Sensor API.
7. Configure the sensor operating parameters.

### BME280 I²C ADDRESS

| Parameter | Value |
|---|---|
| Primary I²C Address | `0x76` |
| Secondary I²C Address | `0x77` |
| Chip ID Register | `0xD0` |
| Expected Chip ID | `0x60` |

The sensor address depends on the SDO pin configuration.

### SENSOR CONFIGURATION

Configure the following parameters using the Bosch Sensor API:

- Temperature oversampling
- Pressure oversampling
- Humidity oversampling
- Sensor operating mode
- Standby time
- Filter configuration

The compensation algorithms must be obtained from the official Bosch driver rather than rewritten manually.

## STEP 3: DEFINE HARDWARE ABSTRACTION FUNCTIONS

Develop STM32-specific interface functions required by the Bosch Sensor API.

### REQUIRED FUNCTIONS

```c
int8_t user_i2c_read(
    uint8_t reg_addr,
    uint8_t *reg_data,
    uint32_t len,
    void *intf_ptr
);

int8_t user_i2c_write(
    uint8_t reg_addr,
    const uint8_t *reg_data,
    uint32_t len,
    void *intf_ptr
);

void user_delay_us(
    uint32_t period,
    void *intf_ptr
);
```

### STM32 HAL FUNCTIONS

| HAL Function | Purpose |
|---|---|
| `HAL_I2C_Mem_Read()` | Read BME280 registers |
| `HAL_I2C_Mem_Write()` | Write BME280 registers |
| `HAL_Delay()` | Provide delay functionality |
| `HAL_Init()` | Initialize STM32 HAL |
| `MX_I2C1_Init()` | Initialize I²C1 |

### INTERFACE FLOW

```text
Bosch BME280 Sensor API
         |
         v
STM32 Interface Functions
         |
         v
STM32 HAL I2C
         |
         v
BME280 Sensor
```

## STEP 4: INITIALIZE AND READ SENSOR DATA

Develop the application using the Bosch BME280 Sensor API.

### INITIALIZATION REQUIREMENTS

1. Initialize the STM32 HAL library.
2. Configure the system clock.
3. Initialize GPIO and I²C peripherals.
4. Configure the Bosch BME280 device structure.
5. Assign the sensor communication callbacks.
6. Read and verify the BME280 chip ID.
7. Initialize the BME280 sensor.
8. Configure sensor settings.
9. Set the sensor operating mode.
10. Read and compensate the sensor measurements.

### BOSCH SENSOR API FUNCTIONS

| Function | Purpose |
|---|---|
| `bme280_init()` | Initialize BME280 and read calibration data |
| `bme280_set_sensor_settings()` | Configure sensor settings |
| `bme280_set_sensor_mode()` | Configure operating mode |
| `bme280_get_sensor_data()` | Read compensated measurements |

### SENSOR SETTINGS USED IN THE REFERENCE CODE

```c
dev.settings.osr_h = BME280_OVERSAMPLING_1X;
dev.settings.osr_p = BME280_OVERSAMPLING_1X;
dev.settings.osr_t = BME280_OVERSAMPLING_1X;
dev.settings.filter = BME280_FILTER_COEFF_OFF;
```

Set the sensor to normal operating mode:

```c
bme280_set_sensor_mode(BME280_MODE_NORMAL, &dev);
```

### SENSOR DATA ACQUISITION

Read temperature, pressure and humidity using:

```c
bme280_get_sensor_data(
    BME280_ALL,
    &comp_data,
    &dev
);
```

### SENSOR MEASUREMENTS

| Parameter | Unit |
|---|---|
| Temperature | °C |
| Pressure | hPa |
| Humidity | %RH |

For the floating-point API configuration shown in the evaluation sheet, pressure is converted from Pa to hPa by dividing by 100.

## STEP 5: SENSOR VERIFICATION

The following operations must be demonstrated:

1. Establish I²C communication between STM32 and BME280.
2. Read the correct BME280 chip ID.
3. Initialize the Bosch Sensor API successfully.
4. Configure the sensor operating parameters.
5. Read the raw measurement registers.
6. Obtain valid compensated temperature, pressure and humidity measurements.
7. Transmit the sensor values through UART.
8. Verify that the measurements change when the sensor environment changes.

### SUGGESTED VERIFICATION SEQUENCE

1. Read the sensor chip ID.
2. Read the raw measurement registers.
3. Apply Bosch compensation.
4. Display compensated measurements.
5. Change oversampling and filter settings and compare the readings.

## REQUIRED OUTPUT

The STM32 application shall periodically obtain and display the following sensor measurements:

```text
Temperature : XX.XX °C
Pressure    : XXXX.XX hPa
Humidity    : XX.XX %RH
```

The measurements may initially be displayed through a UART terminal.

## HTTP AND JSON DATA REPRESENTATION

The STM32 shall construct a JSON payload using the compensated BME280 sensor readings.

### EXAMPLE JSON PAYLOAD

```json
{
  "status": "success",
  "temperature": 28.45,
  "humidity": 62.30,
  "pressure": 1008.72
}
```

### RAW HTTP RESPONSE FORMAT

```http
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: <calculated_length>

{"status":"success","temperature":28.45,"humidity":62.30,"pressure":1008.72}
```

The `Content-Length` must be calculated using the actual JSON string length.

### EXPECTED BROWSER RESPONSE

```json
{
  "status": "success",
  "temperature": 28.45,
  "humidity": 62.30,
  "pressure": 1008.72
}
```

## TOPICS / CONSTRAINTS

- STM32CubeMX
- Keil MDK
- STM32 Nucleo Development Board
- STM32 HAL Libraries
- I²C Communication
- BME280 Sensor Interfacing
- Bosch Sensortec Sensor API
- Sensor Register Reading
- Chip ID Verification
- Temperature Measurement
- Pressure Measurement
- Humidity Measurement
- Sensor Calibration and Compensation
- Sensor Oversampling
- Filter Configuration
- UART Data Transmission
- HTTP and JSON Data Representation

**Implementation Requirements:**

- Use the STM32 development board.
- Configure I²C communication using STM32CubeMX.
- STM32 HAL libraries are allowed.
- Use the official Bosch BME280 Sensor API.
- Implement STM32-specific I²C read, write and delay callbacks.
- Verify the BME280 chip ID.
- Initialize and configure the sensor.
- Obtain compensated temperature, pressure and humidity values.
- Do not manually rewrite the Bosch compensation equations.
- Display or transmit the measured values.
- Calculate HTTP Content-Length from the actual JSON payload length.

## CORE LOGIC / PSEUDOCODE

1. Initialize the STM32 HAL library.
2. Configure the system clock.
3. Initialize GPIO and I²C peripherals.
4. Configure the Bosch BME280 device structure.
5. Assign I²C read, write and delay callbacks.
6. Read the BME280 chip ID.
7. Verify that the correct sensor is connected.
8. Initialize the BME280 using the Bosch Sensor API.
9. Configure temperature, pressure and humidity oversampling.
10. Configure the filter and operating mode.
11. Trigger or obtain sensor measurements.
12. Read raw sensor data.
13. Apply Bosch compensation using the driver.
14. Obtain compensated temperature, pressure and humidity.
15. Display the measured values through UART.
16. Construct the JSON payload using the compensated values.
17. Calculate the actual JSON payload length for HTTP.
18. Repeat sensor data acquisition periodically.

## INFERENCE

The experiment demonstrates interfacing the BME280 environmental sensor with an STM32 microcontroller using the I²C communication protocol.

It provides an understanding of sensor initialization, register-level communication, chip ID verification, sensor configuration and data acquisition.

The Bosch Sensortec BME280 Sensor API enables compensated temperature, pressure and humidity measurements using the sensor calibration parameters.


The experiment also introduces UART-based sensor monitoring and JSON representation of environmental measurements for HTTP-based IoT applications.

## CIRCUIT DIAGRAM

<img width="1536" height="1024" alt="e891bd90-e4de-42b2-bd2f-fd236c46ad69" src="https://github.com/user-attachments/assets/98158e25-f281-4a73-9303-d578643fc896" />
<img width="1536" height="1024" alt="b16bdd27-7051-4573-97f3-d11a32f5be97" src="https://github.com/user-attachments/assets/56d697fb-ab4c-4d92-9a14-763b53096ba5" />
