# CONTINUOUS LAB EVALUATION – 9

**DATE:** 28/09/2026  
**COURSE:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**PLATFORM:** STM32 Development Board  
**TOOLS:** STM32CubeMX, Keil MDK, STM32 HAL Libraries

## NAME OF EXPERIMENT
STM32 UART Command Controlled LED

## TASK NO
Task 9A – Basic UART Communication

## AIM
To configure UART communication between an STM32 microcontroller and a PC terminal using STM32CubeMX and HAL libraries, and implement character transmission, reception, and echo.

## HARDWARE REQUIREMENTS
- STM32 development board
- PC with serial terminal software
- UART communication interface
- USB cable and connecting wires, as required

## SOFTWARE REQUIREMENTS
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- PuTTY or equivalent serial terminal

## FUNCTIONAL REQUIREMENTS

### Part 1 – Transmit a Character
1. Configure the STM32 UART peripheral using STM32CubeMX.
2. Set a standard UART serial configuration.
3. Initialize the UART peripheral using HAL.
4. Repeatedly transmit a character from the STM32 to the PC terminal.

### Part 2 – Receive and Echo
1. Receive characters transmitted from the PC terminal.
2. Read incoming characters using the UART receiver.
3. Transmit each received character back to the PC.
4. Verify the echoed characters in the terminal.

## HAL APIs
- `HAL_UART_Init()` – Initialize the UART peripheral.
- `HAL_UART_Transmit()` – Transmit characters or strings.
- `HAL_UART_Receive()` – Receive characters or strings.

## CORE LOGIC / PSEUDOCODE
1. Initialize HAL and configure the system clock.
2. Initialize the UART peripheral.
3. Establish serial communication with the PC terminal.
4. Transmit a character repeatedly using `HAL_UART_Transmit()`.
5. Receive an incoming character using `HAL_UART_Receive()`.
6. Echo the received character back to the PC terminal.
7. Repeat the communication process.

## UART TERMINAL TESTING
Investigate the behavior of carriage return (`\r`) and line feed (`\n`) using the following strings:

- Test 1: `HELLO\r\n`
- Test 2: `HELLO\r`
- Test 3: `HELLO\n`
- Test 4: `HELLO\r\nWORLD\r\n`

Observe and record how each sequence appears in PuTTY.

## EXPECTED OUTPUT
- Characters transmitted by STM32 appear in the PC terminal.
- Characters entered in the PC terminal are received by STM32.
- Received characters are echoed back to the terminal.
- Carriage return and line feed produce different cursor-positioning behavior.

## INFERENCE
This experiment demonstrates UART initialization, serial character transmission, character reception, and echo communication using STM32 HAL libraries. It also illustrates the role of carriage return and line feed in terminal output formatting.

## CIRCUIT DIAGRAM
![Circuit Diagram](circuit.png)
