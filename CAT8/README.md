# CONTINUOUS LAB EVALUATION – 8

**DATE:** 18-09-2026

## NAME OF EXPERIMENT

STM32 GPIO Bring-Up and Switch-Controlled LED

## HARDWARE SETUP / PLATFORM

- STM32 Development Board (Blue Pill / Nucleo)
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries
- Push Button
- LED
- Board Schematics

## TASK NO

Develop an embedded application using the STM32 microcontroller to interface a push button and LED.

Configure the GPIO pins and implement switch-controlled LED operations, including direct switch-state control, event-based toggling and short-press/long-press detection.

## TASK 8A: GPIO INPUT/OUTPUT

Interface a push button and LED with the STM32 microcontroller.

### FUNCTIONAL REQUIREMENTS

1. Configure the GPIO pin connected to the LED as a digital output.
2. Configure the GPIO pin connected to the push button as a digital input.
3. Read the push-button state.
4. Control the LED according to the current switch state.
5. Ensure that the LED follows the switch state.

## TASK 8B: EVENT-BASED CONTROL

Modify the firmware so that each valid switch press toggles the LED state.

### FUNCTIONAL REQUIREMENTS

1. Detect a valid button-press event.
2. Toggle the LED state whenever the button is pressed.
3. Investigate the effect of mechanical switch bounce.
4. Implement a simple software debounce mechanism.
5. Ensure that one physical button press produces exactly one LED toggle.

## TASK 8C: SHORT PRESS VS LONG PRESS

Modify the application to classify a button press based on how long the button remains pressed.

### PRESS DURATION

| Button Press | Duration |
|---|---|
| Short Press | Less than 1 second |
| Long Press | Greater than or equal to 1 second |

### FUNCTIONAL REQUIREMENTS

| User Action | System Response |
|---|---|
| Short press | Toggle LED |
| Long press | LED enters continuous blinking mode |
| Next short press | Stop blinking |
| Long press again | Return to blinking mode |

### BUTTON PRESS DETECTION FLOW

1. Detect when the button is pressed.
2. Record the button-press start time.
3. Continue executing the application.
4. Detect when the button is released.
5. Record the button-release time.
6. Calculate the press duration.

   `Duration = Release Time - Start Time`

7. Classify the event as a short press or long press.
8. Perform the corresponding LED operation.

## STM32 HAL FUNCTIONS

| Purpose | HAL Function | Application |
|---|---|---|
| Read switch | `HAL_GPIO_ReadPin()` | Determine pressed/released state |
| Control LED | `HAL_GPIO_WritePin()` | Turn LED ON/OFF |
| Toggle LED | `HAL_GPIO_TogglePin()` | Toggle LED on short press |
| Millisecond time base | `HAL_GetTick()` | Measure button-press duration |
| Delay, if needed | `HAL_Delay()` | Simple initial testing only |

## TOPICS / CONSTRAINTS

- STM32CubeMX
- Keil MDK
- STM32 Development Board (Blue Pill / Nucleo)
- STM32 HAL Libraries
- GPIO Input/Output Configuration
- Switch-Controlled LED
- Event-Based LED Control
- Software Debouncing
- Short-Press and Long-Press Detection
- Non-Blocking Button Duration Measurement

**Implementation Constraints:**

- STM32 HAL libraries are allowed.
- Configure the GPIO pins for the LED and push button.
- Ensure one valid button press produces one LED toggle in Task 8B.
- Classify short presses as less than 1 second.
- Classify long presses as greater than or equal to 1 second.
- Do not use a blocking delay to determine whether a button press is a long press.
- Use elapsed-time measurement for press-duration detection.

## CORE LOGIC / PSEUDOCODE

### TASK 8A: GPIO INPUT/OUTPUT

1. Initialize the STM32 GPIO peripherals.
2. Configure the LED GPIO pin as output.
3. Configure the push-button GPIO pin as input.
4. Continuously read the push-button state.
5. Update the LED output according to the switch state.

### TASK 8B: EVENT-BASED CONTROL

1. Initialize the LED and push-button GPIO pins.
2. Monitor the push-button input.
3. Detect a new button-press event.
4. Apply software debouncing.
5. Confirm the valid button press.
6. Toggle the LED state once.
7. Wait for the next valid press event.

### TASK 8C: SHORT PRESS VS LONG PRESS

1. Initialize the GPIO peripherals.
2. Detect the button-press event.
3. Record the start time using `HAL_GetTick()`.
4. Continue executing the application without blocking.
5. Detect button release.
6. Record the release time.
7. Calculate the press duration.
8. If the duration is less than 1000 ms, classify it as a short press.
9. If the duration is greater than or equal to 1000 ms, classify it as a long press.
10. Perform the corresponding LED operation.
11. Continue monitoring for subsequent button presses.

## INFERENCE

The experiment demonstrates STM32 GPIO interfacing and switch-controlled LED operation using STM32 HAL libraries.

Task 8A provides an understanding of digital input and output configuration.

Task 8B demonstrates event-based LED toggling and software debouncing to prevent multiple toggles from a single physical button press.

Task 8C demonstrates non-blocking press-duration measurement and classification of short and long button presses to control LED operating modes.

The experiment provides practical understanding of GPIO configuration, switch-event handling and timing-based embedded control using STM32.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
