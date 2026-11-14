# CAT11 - TASK1: On-board LED Bring-Up

## Experiment Details
- **Course:** 25CS2741 Fundamentals of Internet of Things + Lab
- **Evaluation:** Continuous Lab Evaluation 11
- **Date:** 14/10/2026
- **Platform:** STM32F401RE Nucleo Development Board
- **Microcontroller:** STM32F401RE Cortex-M4
- **Development Tools:** STM32CubeMX and Keil MDK
- **Programming Library:** STM32 HAL

## Aim
To develop and program an STM32 application that verifies the NUCLEO-F401RE hardware and GPIO output configuration by blinking the on-board LED at a fixed interval.

## Hardware Requirements
1. STM32 NUCLEO-F401RE development board
2. USB cable for power and programming
3. Computer with STM32CubeMX and Keil MDK

## GPIO Configuration
- **PA5:** On-board LED (LD2), GPIO output
- **GPIO Mode:** Output push-pull
- **Output Type:** Push-pull
- **Pull-up/Pull-down:** No pull
- **Clock Configuration:** Configured using STM32CubeMX

## Working Principle
The STM32F401RE microcontroller controls the on-board LED through GPIO pin PA5.

The GPIO pin is configured as a digital output. The firmware periodically changes the output state between HIGH and LOW.

When PA5 is HIGH, the LED turns ON. When PA5 is LOW, the LED turns OFF.

A fixed software delay determines the blinking interval. Continuous toggling verifies the GPIO configuration and basic operation of the development board.

## Procedure
1. Open STM32CubeMX and select the STM32F401RE Nucleo board.
2. Configure PA5 as GPIO_Output.
3. Configure the system clock.
4. Generate the STM32 HAL initialization code.
5. Open the generated project in Keil MDK.
6. Implement periodic GPIO toggling using HAL_GPIO_TogglePin().
7. Use HAL_Delay() to maintain a fixed interval.
8. Build the project and flash the firmware onto the board.
9. Observe the on-board LED.

## Expected Output
- The on-board LED blinks continuously.
- The LED switches between ON and OFF at a fixed interval.
- The blinking behavior confirms successful GPIO output configuration.

## Result
The STM32 GPIO output application is designed to blink the on-board LED at a fixed interval, demonstrating GPIO output control and basic hardware bring-up.

## Circuit Diagram
<img width="1536" height="1024" alt="c3a75220-a311-4d8a-b312-bc23ebb23c62" src="https://github.com/user-attachments/assets/35a1cea2-d405-4f07-a89c-c9b4911e9173" />
