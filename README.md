# STM32 Experiments
# STM32 Microcontroller | Embedded Systems & IoT Development

## Overview

This repository showcases my hands-on experience in **embedded systems programming and Internet of Things (IoT) development** using STM32 microcontrollers.

The projects focus on developing embedded firmware, interfacing hardware peripherals, implementing communication protocols, and connecting microcontroller-based systems to network applications.

Through these experiments, I explored the complete development process, from hardware configuration and firmware programming to sensor data acquisition and IoT communication.

## Technical Skills

- **Embedded C Programming:** Developed microcontroller firmware using STM32 HAL libraries.
- **ARM Cortex-M Development:** Worked with STM32F103 and STM32F401 microcontrollers.
- **GPIO Programming:** Implemented LED control, push-button interfacing, and input-state detection.
- **Timers and Timing Logic:** Implemented software-controlled timing sequences and button debouncing.
- **UART Communication:** Configured serial interfaces for communication with external devices.
- **I2C Communication:** Interfaced digital environmental sensors using I2C.
- **Sensor Integration:** Acquired temperature, humidity, and atmospheric pressure measurements using the BME280 sensor.
- **Wi-Fi Integration:** Interfaced STM32 with ESP8266-based Wi-Fi modules using AT commands.
- **Network Programming:** Explored TCP communication and HTTP server functionality.
- **IoT Communication:** Worked with MQTT-based messaging and IoT dashboards.

## Key Implementations

### 1. GPIO and Digital Input/Output Control

Developed firmware to control LEDs through GPIO pins and implement customized blinking patterns.

Implemented push-button-based LED toggling with software debouncing and state remembrance.

### 2. UART Serial Communication

Configured UART peripherals for bidirectional serial communication.

Developed applications for transmitting commands, receiving responses, and controlling hardware through serial communication.

### 3. STM32 and ESP8266 Wi-Fi Integration

Interfaced STM32 microcontrollers with ESP8266/Wemos D1 Mini modules using UART and AT commands.

Implemented Wi-Fi station configuration, network connection establishment, and TCP server initialization.

### 4. HTTP-Based IoT Application

Developed an embedded HTTP application that processes incoming requests and generates dynamic HTML responses.

Explored how microcontrollers can interact with network clients through Wi-Fi connectivity.

### 5. BME280 Environmental Sensor Interfacing

Integrated the BME280 sensor with STM32 using the I2C protocol.

Configured sensor operating modes, oversampling settings, and data acquisition to obtain temperature, humidity, and atmospheric pressure readings.

### 6. MQTT and IoT Dashboard Integration

Explored MQTT publish-subscribe communication for transmitting embedded system data.

Worked with Node-RED dashboards to visualize information and support interactive IoT applications.

## Tools and Technologies

| Category | Technologies |
|---|---|
| Microcontrollers | STM32F103, STM32F401 |
| Architecture | ARM Cortex-M |
| Programming | Embedded C |
| Development Tools | STM32CubeMX, STM32CubeIDE, Keil µVision |
| Firmware Libraries | STM32 HAL, BME280 Driver |
| Communication Protocols | UART, I2C, MQTT, HTTP, TCP/IP |
| Wireless Connectivity | ESP8266, Wemos D1 Mini |
| IoT Tools | Node-RED, MQTT Broker |
| Debugging | ST-Link, Serial Monitor, Keil Debugger |

## Engineering Concepts Explored

- Microcontroller architecture and peripheral configuration
- Register-level understanding and HAL-based firmware development
- Digital input/output and state-based control
- Serial communication and peripheral interfacing
- Sensor calibration and data acquisition
- Network connectivity and communication protocols
- Embedded debugging and troubleshooting
- Integration of hardware, firmware, and IoT applications

## Learning Outcomes

These projects strengthened my understanding of how embedded hardware and software work together to create connected systems.

I gained practical exposure to configuring microcontroller peripherals, debugging firmware, interfacing sensors, establishing wireless communication, and developing network-enabled embedded applications.

This experience provides a foundation for further work in **Embedded Systems, IoT Engineering, Firmware Development, and Software Engineering**.
