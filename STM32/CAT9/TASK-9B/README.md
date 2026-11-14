CONTINUOUS LAB EVALUATION – 9

**DATE:** 28/09/2026  
**COURSE:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**PLATFORM:** STM32 Development Board  
**TOOLS:** STM32CubeMX, Keil MDK, STM32 HAL Libraries

## NAME OF EXPERIMENT
STM32 UART Command Controlled LED

## TASK NO
Task 9B – String-Based Application Logic

## AIM
To develop a UART-based command interface that receives text commands from a PC terminal and controls the onboard LED of an STM32 microcontroller.

## HARDWARE REQUIREMENTS
- STM32 development board with onboard LED
- PC with serial terminal software
- UART communication interface
- USB cable and connecting wires, as required

## SOFTWARE REQUIREMENTS
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- PuTTY or equivalent serial terminal

## FUNCTIONAL REQUIREMENTS
1. Configure UART communication between STM32 and the PC.
2. Receive command strings entered through the terminal.
3. Identify the received command.
4. Control the onboard LED according to the command.

## SUPPORTED COMMANDS

| UART Command | Required Operation |
|---|---|
| `LED ON` | Turn ON the onboard LED |
| `LED OFF` | Turn OFF the onboard LED |
| `LED TOGGLE` | Toggle the current LED state |

## HAL APIs
- `HAL_UART_Init()` – Initialize UART communication.
- `HAL_UART_Receive()` – Receive command characters.
- `HAL_UART_Transmit()` – Send terminal responses, if implemented.
- `HAL_GPIO_WritePin()` – Set the LED output state.
- `HAL_GPIO_TogglePin()` – Toggle the LED state.

## CORE LOGIC / PSEUDOCODE
1. Initialize HAL, system clock, GPIO, and UART.
2. Configure the onboard LED as a GPIO output.
3. Receive characters from the PC terminal.
4. Store incoming characters in a command buffer.
5. Identify the end of a command.
6. Compare the received string with the supported commands.
7. If the command is `LED ON`, turn ON the LED.
8. If the command is `LED OFF`, turn OFF the LED.
9. If the command is `LED TOGGLE`, toggle the LED.
10. Clear or reset the command buffer for the next command.
11. Repeat continuously.

## EXPECTED OUTPUT
- Entering `LED ON` turns ON the onboard LED.
- Entering `LED OFF` turns OFF the onboard LED.
- Entering `LED TOGGLE` changes the LED to its opposite state.

## INFERENCE
This experiment demonstrates string-based UART communication and command interpretation using STM32 HAL libraries. It shows how text commands received from a serial terminal can control a microcontroller peripheral.






