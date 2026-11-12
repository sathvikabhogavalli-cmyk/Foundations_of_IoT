
# CONTINUOUS LAB EVALUATION – 10

**DATE:** 05-10-2026

## NAME OF EXPERIMENT

STM32–Wemos Wi-Fi Modem Interface Using AT Commands

## HARDWARE SETUP / PLATFORM

- STM32 Development Board
- Wemos D1 Mini / ESP8266 Wi-Fi Module
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- UART Communication Interface
- PC / Laptop
- PuTTY / Tera Term Serial Terminal
- Board Schematics and Reference Manual

## TASK NO

Interface an STM32 development board with a Wemos D1 Mini / ESP8266 module through UART.

Configure the Wi-Fi modem using AT commands, acquire sensor data through the STM32 and transmit the sensor data over a Wi-Fi network.

## TASK 10A: ESTABLISH STM32 ↔ WEMOS UART COMMUNICATION

Before attempting Wi-Fi communication, verify that the STM32 and Wemos boards can communicate successfully through UART.

### UART CONNECTIONS

| Wemos D1 Mini Pin | STM32 Pin | Description |
|---|---|---|
| TX | RX (e.g., PA3 / USART2_RX) | Wemos to STM32 |
| RX | TX (e.g., PA2 / USART2_TX) | STM32 to Wemos |
| GND | GND | Common ground |
| 5V / 3.3V | Appropriate supply | Power connection |

### FUNCTIONAL REQUIREMENTS

1. Configure the STM32 UART peripheral.
2. Establish UART communication between STM32 and Wemos.
3. Transmit the `AT` command from STM32 to Wemos.
4. Append carriage return and line feed (`\r\n`) to the command.
5. Receive the response from the Wemos module.
6. Forward the received response to the PC terminal.
7. Verify that the Wemos responds with `OK`.

### EXPECTED OUTPUT

```text
STM32 → Wemos
AT\r\n

Wemos → STM32
OK
```

### COMMUNICATION FLOW

STM32 TX → Wemos RX

STM32 RX ← Wemos TX

STM32 → UART → PC Terminal

## TASK 10B: EXPLORE THE ESP8266 AT COMMAND INTERFACE

Investigate the ESP8266 AT command interface and identify the appropriate commands for modem configuration, network discovery and communication.

### AT COMMAND INVESTIGATION

| Requirement | AT Command |
|---|---|
| Check modem response | `AT` |
| Check firmware/version | `AT+GMR` |
| Set Wi-Fi station mode | `AT+CWMODE=1` |
| Scan available networks | `AT+CWLAP` |
| Connect to an access point | `AT+CWJAP="SSID","password"` |
| Obtain network information | `AT+CIFSR` |
| Establish TCP connection | `AT+CIPSTART` |
| Send application data | `AT+CIPSEND` |

### FUNCTIONAL REQUIREMENTS

1. Identify the AT command used to test modem communication.
2. Determine the command used to check firmware information.
3. Configure the Wemos ESP8266 as a Wi-Fi station.
4. Scan available Wi-Fi networks.
5. Connect to a selected access point.
6. Obtain the network information.
7. Identify commands for establishing TCP connections.
8. Identify commands for sending application data.

### UART CONFIGURATION

If the STM32 board supports two UART interfaces, use them for separate communication purposes.

| UART | Connection | Purpose |
|---|---|---|
| UART1 | STM32 ↔ Wemos | AT commands and responses |
| UART2 | STM32 ↔ PC | Debugging and displaying responses |

## TASK 10C: CONNECT WEMOS TO WI-FI

Develop STM32 firmware that configures the Wemos ESP8266 as a Wi-Fi station and connects it to a university or local Wi-Fi network using AT commands.

### FUNCTIONAL REQUIREMENTS

1. Initialize the UART communication interface.
2. Send the `AT` command to check communication.
3. Receive and verify the `OK` response.
4. Configure the ESP8266 in Wi-Fi station mode.
5. Connect to the selected Wi-Fi access point.
6. Wait for the connection response.
7. Query the network status.
8. Display the Wi-Fi connection status and IP address on the PC terminal.

### WI-FI CONFIGURATION COMMANDS

**Step 1: Check modem response**

```text
AT
```

Expected response:

```text
OK
```

**Step 2: Configure station mode**

```text
AT+CWMODE=1
```

Expected response:

```text
OK
```

**Step 3: Connect to Wi-Fi**

```text
AT+CWJAP="MyWiFi","password"
```

Expected response:

```text
WIFI CONNECTED
WIFI GOT IP
OK
```

**Step 4: Query IP address**

```text
AT+CIFSR
```

### EXPECTED PC TERMINAL OUTPUT

```text
STM32-WiFi MODEM TEST

>> AT
<< OK

>> AT+CWMODE=1
<< OK

>> AT+CWJAP="MyWiFi","password"
<< WIFI CONNECTED
<< WIFI GOT IP
<< OK

WIFI MODE    : STATION
WIFI STATUS  : CONNECTED
IP ADDRESS   : xxx.xxx.xxx.xxx
```

### COMMUNICATION FLOW

1. STM32 sends an AT command.
2. Wemos receives the command through UART.
3. ESP8266 processes the command.
4. Wemos transmits the response to STM32.
5. STM32 receives the response through UART.
6. STM32 forwards the response to the PC terminal.
7. The PC terminal displays the response and connection status.

## TOPICS / CONSTRAINTS

- STM32CubeMX
- Keil MDK
- STM32 Development Board
- Wemos D1 Mini / ESP8266
- STM32 HAL Libraries
- UART Communication
- AT Command Interface
- ESP8266 Wi-Fi Station Mode
- Wi-Fi Network Scanning
- Access Point Connection
- TCP Communication
- Serial Debugging
- Network Status Verification

**Implementation Requirements:**

- STM32 HAL libraries are allowed.
- Establish UART communication between STM32 and Wemos.
- Use AT commands to configure the ESP8266.
- Send AT commands with carriage return and line feed.
- Receive and display modem responses.
- Configure ESP8266 in Wi-Fi station mode.
- Connect to a university or local Wi-Fi network.
- Verify the Wi-Fi connection status and IP address.
- Use two UART interfaces for modem communication and PC debugging if supported.

## CORE LOGIC / PSEUDOCODE

### TASK 10A: STM32–WEMOS UART COMMUNICATION

1. Initialize STM32 UART peripherals.
2. Establish UART communication with the Wemos ESP8266.
3. Send `AT\r\n` to the Wemos.
4. Receive the modem response.
5. Forward the response to the PC terminal.
6. Verify the `OK` response.

### TASK 10B: ESP8266 AT COMMAND INVESTIGATION

1. Identify the ESP8266 AT commands.
2. Check modem communication using `AT`.
3. Check firmware information using `AT+GMR`.
4. Configure station mode using `AT+CWMODE=1`.
5. Scan networks using `AT+CWLAP`.
6. Connect to an access point using `AT+CWJAP`.
7. Obtain network information using `AT+CIFSR`.
8. Identify commands for TCP connection and data transmission.

### TASK 10C: WI-FI CONNECTION

1. Initialize the STM32 UART interfaces.
2. Send the AT command and verify the response.
3. Configure the ESP8266 as a Wi-Fi station.
4. Send the Wi-Fi connection command.
5. Wait for the ESP8266 response.
6. Verify the Wi-Fi connection.
7. Query the assigned IP address.
8. Forward the network information to the PC terminal.

## INFERENCE

The experiment demonstrates UART communication between an STM32 microcontroller and a Wemos D1 Mini / ESP8266 Wi-Fi module.

Task 9A provides an understanding of UART communication, AT command transmission and modem response verification.

Task 9B introduces the ESP8266 AT command interface for modem configuration, Wi-Fi network scanning, access point connection and TCP communication.

Task 9C demonstrates Wi-Fi station configuration, connection to an access point and verification of network status through the PC terminal.

The experiment illustrates the use of STM32 HAL libraries and UART communication to interface a microcontroller with an external Wi-Fi modem for IoT applications.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
