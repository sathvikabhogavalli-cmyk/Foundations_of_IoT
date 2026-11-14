# CAT11 - TASK2: On-board Switch Control with State Remembrance

## Experiment Details
- **Course:** 25CS2741 Fundamentals of Internet of Things + Lab
- **Evaluation:** Continuous Lab Evaluation 11
- **Date:** 14/10/2026
- **Platform:** STM32F401RE Nucleo Development Board
- **Microcontroller:** STM32F401RE Cortex-M4
- **Development Tools:** STM32CubeMX and Keil MDK
- **Programming Library:** STM32 HAL

## Aim
To develop an STM32 application in which the on-board push button controls the LED, toggling its state whenever a valid button press is detected and retaining its previous state after the button is released.

## Hardware Requirements
1. STM32 NUCLEO-F401RE development board
2. On-board user push button (B1)
3. On-board LED (LD2)
4. USB cable
5. Computer with STM32CubeMX and Keil MDK

## GPIO Configuration
- **PA5:** On-board LED (LD2), GPIO output
- **PC13:** On-board user push button (B1), GPIO input
- **LED Mode:** Output push-pull
- **Button Mode:** Digital input
- **Clock Configuration:** Configured using STM32CubeMX

## Working Principle
The STM32 microcontroller monitors the on-board push button through GPIO pin PC13.

The on-board LED is controlled through GPIO pin PA5.

Whenever a valid button press is detected, the firmware changes the LED state.

If the LED is OFF, pressing the button turns it ON.

If the LED is ON, pressing the button turns it OFF.

The application stores the current LED state in a software variable.

When the button is released, the LED retains its previous state.

Button debouncing and press-edge detection can be used to prevent multiple toggles during a single physical press.

## Procedure
1. Open STM32CubeMX and select the STM32F401RE Nucleo board.
2. Configure PA5 as GPIO_Output.
3. Configure PC13 as GPIO_Input.
4. Configure the system clock.
5. Generate the STM32 HAL project.
6. Open the project in Keil MDK.
7. Initialize a variable to track the LED state.
8. Read the button input using HAL_GPIO_ReadPin().
9. Detect each valid button press.
10. Toggle the stored LED state and update PA5.
11. Prevent repeated toggling while the button remains pressed.
12. Build and flash the application onto the STM32 board.
13. Test the button-controlled LED behavior.

## Expected Output
- Initially, the LED follows the configured starting state.
- The first valid button press toggles the LED.
- Releasing the button does not change the LED state.
- The next valid button press toggles the LED again.
- Each valid press causes only one state change.

## Result
The application demonstrates GPIO input handling, LED output control, button press detection, and software-based state remembrance on the STM32F401RE Nucleo board.

## Circuit Diagram
The experiment uses the on-board LED connected to PA5 and the on-board user push button connected to PC13.
<img width="1536" height="1024" alt="c3a75220-a311-4d8a-b312-bc23ebb23c62" src="https://github.com/user-attachments/assets/09818329-4a9b-4064-a264-036736900340" />
