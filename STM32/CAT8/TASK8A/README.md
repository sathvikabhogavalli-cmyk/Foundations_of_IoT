# CAT 8 – STM32 GPIO Bring-Up and Switch-Controlled LED

## EXP
CAT 8 – TASK 8A

## DATE
18/09/2026

## NAME OF EXP
GPIO Input/Output

## HARDWARE SETUP / PLATFORM
- Development Board: STM32F103C8T6 Blue Pill
- Microcontroller: STM32F103C8T6
- Push Button: PA9
- LED: PA4
- Software: STM32CubeMX and Keil MDK-ARM

## TASK NO
Task 8A

Interface a push-button and LED with the STM32. Configure the corresponding GPIO pins and develop firmware so that the LED follows the switch state.

## Circuit Diagram

![Circuit Diagram](circuit.png)

### Pin Connections
- PA9 – Push-button input (internal pull-up enabled).
- PA4 – LED output.

## Core Logic / Pseudocode / Code Base

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO pins PA9 and PA4.
4. Configure PA9 as input with an internal pull-up resistor.
5. Configure PA4 as output push-pull.
6. Continuously read the push-button state.
7. If the button is pressed (`GPIO_PIN_RESET`), turn ON the LED.
8. Otherwise, turn OFF the LED.

### HAL Functions Used
- `HAL_Init()`
- `HAL_GPIO_ReadPin()`
- `HAL_GPIO_WritePin()`
- `HAL_RCC_OscConfig()`
- `HAL_RCC_ClockConfig()`

**Source File:** `Core/Src/main.c`

## INFERENCE

Successfully interfaced a push-button and LED with the STM32F103C8T6 Blue Pill using GPIO. The LED turns ON when the push-button is pressed and turns OFF when it is released.