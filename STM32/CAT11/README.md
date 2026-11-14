
# CONTINUOUS LAB EVALUATION – 11

**DATE:** 14-10-2026

**COURSE:** 25CS2741 – Fundamentals of Internet of Things + Lab

## NAME OF EXPERIMENT

STM32F401RE Cortex-M4: GPIO and User Input Programming

## HARDWARE SETUP / PLATFORM

- STM32 Nucleo Development Board
- STM32F401RE Cortex-M4 Microcontroller
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- On-board LED
- On-board Push Button
- STM32 Nucleo Board Pinout and User Manual

## TASK NO

Develop embedded applications using the STM32F401RE Nucleo development board to verify GPIO output functionality, implement push-button-controlled LED operation with state remembrance, and distinguish between short and long button presses.

## PREREQUISITES

1. Observe the on-board oscillator frequency.
2. Identify the STM32 controller on the development board.
3. Understand the controller specifications, including:
   - Clock frequency
   - GPIO groups
   - Number of UART interfaces
   - Number of I2C interfaces
   - Number of SPI interfaces
4. Decide the clock configuration settings in STM32CubeMX.
5. Refer to the STM32F401RE/RB Nucleo board pinout.

**Reference Document:**

[STM32 Nucleo-64 Boards User Manual (UM1724)](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)

## TASK 1: ON-BOARD LED BRING-UP

Develop and program an STM32 application to verify the NUCLEO-F401RE hardware and GPIO output configuration by blinking the on-board LED at a fixed interval.

### FUNCTIONAL REQUIREMENTS

1. Configure the STM32F401RE microcontroller using STM32CubeMX.
2. Configure the GPIO pin connected to the on-board LED as a digital output.
3. Initialize the required GPIO peripherals.
4. Develop firmware to toggle the on-board LED.
5. Blink the LED at a fixed interval.
6. Verify the GPIO output operation on the Nucleo development board.

### CORE LOGIC / PSEUDOCODE

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize the GPIO peripheral.
4. Configure the on-board LED pin as output.
5. Toggle the LED state.
6. Wait for the configured interval.
7. Repeat continuously.

## TASK 2: ON-BOARD SWITCH CONTROL WITH STATE REMEMBRANCE

Modify the application so that the on-board push button controls the LED.

The LED shall toggle its state whenever a valid button press is detected and shall remember its previous state after the button is released.

### FUNCTIONAL REQUIREMENTS

1. Configure the on-board LED GPIO pin as output.
2. Configure the on-board push-button GPIO pin as input.
3. Continuously monitor the push-button state.
4. Detect a valid button press.
5. Toggle the LED state whenever a valid button press is detected.
6. Retain the LED state after the button is released.
7. Change the LED state only when another valid button press occurs.

### EXPECTED BEHAVIOR

| Button Action | LED Operation |
|---|---|
| Initial state | LED retains its initialized state |
| First valid press | Toggle LED |
| Button released | Retain previous LED state |
| Second valid press | Toggle LED again |
| Button released | Retain previous LED state |

### CORE LOGIC / PSEUDOCODE

1. Initialize the GPIO peripherals.
2. Configure the LED pin as output.
3. Configure the push-button pin as input.
4. Read the push-button state.
5. Detect a valid button press.
6. Toggle the LED output.
7. Retain the LED state after release.
8. Wait for the next valid button press.
9. Repeat continuously.

## TASK 3: SHORT-PRESS AND LONG-PRESS DETECTION

Extend the application to distinguish between a short button press and a long button press.

The STM32 shall perform different actions depending on the duration of the button press.

### FUNCTIONAL REQUIREMENTS

1. Configure the on-board push button as a digital input.
2. Detect when the push button is pressed.
3. Measure the duration of the button press.
4. Detect when the push button is released.
5. Distinguish between short and long button presses.
6. Perform different actions based on the detected press duration.

### BUTTON PRESS CLASSIFICATION

| Button Event | Description |
|---|---|
| Short Press | Button held for a duration shorter than the configured threshold |
| Long Press | Button held for a duration equal to or longer than the configured threshold |

**Note:** The evaluation sheet does not specify an exact duration threshold or the actions for short and long presses. These must be defined in the implementation.

### CORE LOGIC / PSEUDOCODE

1. Initialize the STM32 GPIO peripherals.
2. Configure the on-board push button as input.
3. Monitor the button state.
4. Detect the button-press event.
5. Record the press start time.
6. Detect the button-release event.
7. Record the release time.
8. Calculate the button-press duration.
9. Compare the duration with the configured threshold.
10. Classify the event as a short press or long press.
11. Execute the corresponding action.
12. Continue monitoring the push button.

## STM32 HAL FUNCTIONS

| HAL Function | Purpose |
|---|---|
| `HAL_Init()` | Initialize the HAL library |
| `HAL_GPIO_ReadPin()` | Read push-button input |
| `HAL_GPIO_WritePin()` | Control LED output |
| `HAL_GPIO_TogglePin()` | Toggle LED state |
| `HAL_GetTick()` | Obtain system tick for press-duration measurement |
| `HAL_Delay()` | Provide a delay for fixed-interval LED blinking |

## TOPICS / CONSTRAINTS

- STM32CubeMX
- Keil MDK
- STM32 Nucleo Development Board
- STM32F401RE Cortex-M4
- STM32 HAL Libraries
- On-board Oscillator
- System Clock Configuration
- GPIO Input/Output
- On-board LED Bring-Up
- Push-Button Interfacing
- LED State Remembrance
- Short-Press Detection
- Long-Press Detection
- Button Duration Measurement

**Implementation Requirements:**

- Use the STM32F401RE Nucleo development board.
- Configure the system clock using STM32CubeMX.
- STM32 HAL libraries are allowed.
- Verify the on-board LED through fixed-interval blinking.
- Detect valid push-button presses.
- Toggle the LED for each valid press in Task 2.
- Preserve the LED state after button release.
- Distinguish between short and long button presses in Task 3.
- Perform different actions based on press duration.

## INFERENCE

The experiment demonstrates GPIO configuration and user-input programming using the STM32F401RE Cortex-M4 microcontroller.

Task 1 provides an understanding of STM32 Nucleo hardware bring-up, clock configuration and GPIO output control through on-board LED blinking.

Task 2 demonstrates push-button interfacing, event-based LED toggling and state remembrance after button release.

Task 3 introduces button-press duration measurement and classification of short and long presses to perform different application actions.

The experiment provides practical understanding of STM32 GPIO programming, user-input handling and embedded application development using STM32CubeMX, Keil MDK and STM32 HAL libraries.

## CIRCUIT DIAGRAM

![706248575-28e1d7d7-eecc-4f6e-9358-a32b2e17c4c1](706248575-28e1d7d7-eecc-4f6e-9358-a32b2e17c4c1.png)
