# CONTINUOUS LAB EVALUATION – 9

**DATE:** 28-09-2026

## NAME OF EXPERIMENT

STM32 UART Command Controlled LED

## HARDWARE SETUP / PLATFORM

- STM32 Development Board
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- PC / Laptop
- UART Serial Terminal (PuTTY)
- Onboard LED
- Board Schematics and Reference Manual

## TASK NO

Develop an embedded application using the STM32 microcontroller to establish UART communication with a PC terminal.

Implement character transmission, reception and echo functionality, followed by a UART-based command interface to control the onboard LED.

## TASK 9A: BASIC UART COMMUNICATION

Configure UART using STM32CubeMX and HAL libraries to establish communication between the STM32 microcontroller and a PC terminal.

### FUNCTIONAL REQUIREMENTS

1. Configure the STM32 UART peripheral using STM32CubeMX.
2. Initialize UART using HAL libraries.
3. Establish serial communication between the STM32 and PC terminal.
4. Transmit a character repeatedly to the PC terminal.
5. Receive characters transmitted from the PC.
6. Echo each received character back to the PC terminal.
7. Implement character and string transmission/reception.

### PART A: TRANSMIT A CHARACTER

Configure the STM32 UART for a standard serial configuration and transmit a character repeatedly to the PC terminal.

**Communication Flow:**

STM32 → UART TX → PC Terminal

### PART B: RECEIVE AND ECHO

Modify the application so that every character received from the PC is transmitted back to the PC.

**Communication Flow:**

PC Terminal → UART RX → STM32 → UART TX → PC Terminal

## TASK 9B: STRING-BASED APPLICATION LOGIC

Develop a UART-based command interface for the STM32 microcontroller.

The system must accept commands from a PC terminal and control the onboard LED according to the received command.

### FUNCTIONAL REQUIREMENTS

1. Receive commands through the UART interface.
2. Identify the received command.
3. Perform the corresponding LED operation.
4. Support LED ON, LED OFF and LED TOGGLE commands.
5. Continuously monitor the UART interface for new commands.

### UART COMMAND OPERATIONS

| UART Command | LED Operation |
|---|---|
| `LED ON` | Turn LED ON |
| `LED OFF` | Turn LED OFF |
| `LED TOGGLE` | Toggle LED state |

### EXPECTED BEHAVIOUR

**Command 1:**

```text
> LED ON
LED turned ON
```

**Command 2:**

```text
> LED OFF
LED turned OFF
```

**Command 3:**

```text
> LED TOGGLE
LED toggled
```

## STM32 HAL UART APIs

For the basic UART experiment, the first three APIs are the primary focus. The remaining APIs are suggested for later exploration.

| HAL API | Purpose |
|---|---|
| `HAL_UART_Init()` | Initialize UART peripheral |
| `HAL_UART_Transmit()` | Transmit characters or strings |
| `HAL_UART_Receive()` | Receive characters or strings |
| `HAL_UART_Transmit_IT()` | Interrupt-driven transmission |
| `HAL_UART_Receive_IT()` | Interrupt-driven reception |
| `HAL_UART_Transmit_DMA()` | DMA-based transmission |
| `HAL_UART_Receive_DMA()` | DMA-based reception |

## UART TERMINAL TESTING

Investigate the difference between carriage return and line feed characters.

- `\r` — Carriage Return
- `\n` — Line Feed

### TEST CASES

| Test | Transmitted String |
|---|---|
| Test 1 | `"HELLO\r\n"` |
| Test 2 | `"HELLO\r"` |
| Test 3 | `"HELLO\n"` |
| Test 4 | `"HELLO\r\nWORLD\r\n"` |

### OBSERVATION

Transmit each test string to the PuTTY terminal and observe the cursor position and displayed output.

Investigate the difference between carriage return and line feed and explain why both characters are commonly used together in serial terminal communication.

## TOPICS / CONSTRAINTS

- STM32CubeMX
- Keil MDK
- STM32 Development Board
- STM32 HAL Libraries
- UART Peripheral Configuration
- UART Initialization
- Character Transmission
- Character Reception
- UART Echo
- String-Based Command Processing
- Onboard LED Control
- PuTTY Serial Terminal Testing
- Carriage Return and Line Feed

**Implementation Requirements:**

- Configure UART using STM32CubeMX and HAL.
- Use STM32 HAL UART APIs for serial communication.
- Establish communication with a PC terminal.
- Implement character transmission and reception.
- Echo received characters to the terminal.
- Process UART commands for onboard LED control.
- Investigate carriage return and line feed behaviour in PuTTY.
- Interrupt-driven and DMA-based UART communication may be explored as advanced functionality.

## CORE LOGIC / PSEUDOCODE

### TASK 9A: BASIC UART COMMUNICATION

1. Configure the STM32 UART peripheral using STM32CubeMX.
2. Initialize UART using HAL.
3. Establish serial communication with the PC terminal.
4. Transmit a character repeatedly using the UART transmit function.
5. Receive a character from the PC terminal.
6. Transmit the received character back to the PC.
7. Repeat the communication process.

### TASK 9B: UART COMMAND CONTROLLED LED

1. Initialize the UART peripheral and onboard LED GPIO.
2. Receive characters from the PC terminal.
3. Form the received characters into a command string.
4. Identify the command entered by the user.
5. If the command is `LED ON`, turn the LED ON.
6. If the command is `LED OFF`, turn the LED OFF.
7. If the command is `LED TOGGLE`, toggle the LED state.
8. Continue receiving and processing subsequent commands.

### UART TERMINAL TESTING

1. Open the PuTTY serial terminal.
2. Establish UART communication with the STM32.
3. Transmit the test strings containing `\r` and `\n`.
4. Observe the displayed output and cursor movement.
5. Compare the results of the four test cases.
6. Identify the purpose of carriage return and line feed.

## INFERENCE

The experiment demonstrates UART serial communication using the STM32 microcontroller and STM32 HAL libraries.

Task 9A provides an understanding of UART configuration, character transmission, reception and echo functionality between the STM32 and a PC terminal.

Task 9B demonstrates string-based command processing to control the onboard LED through UART commands.

The terminal testing activity provides an understanding of carriage return and line feed characters in serial communication.

The experiment illustrates the development of a basic UART-based embedded command interface using STM32CubeMX, Keil MDK and STM32 HAL libraries.

## CIRCUIT DIAGRAM

<img width="3508" height="2481" alt="circuit" src="https://github.com/user-attachments/assets/cd063422-d5b3-40fb-8293-929a150426ab" />

