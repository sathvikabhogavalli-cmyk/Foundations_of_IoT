# CONTINUOUS LAB EVALUATION – 8

**DATE:** 18/09/2026  
**COURSE:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**PLATFORM:** STM32 Development Board (Blue Pill / Nucleo)  
**TOOLS:** STM32CubeMX, Keil MDK, STM32 HAL Libraries

## NAME OF EXPERIMENT
STM32 GPIO Bring-Up and Switch-Controlled LED

## TASK NO
Task 8C – Short Press vs Long Press

## AIM
To distinguish between short and long push-button presses using non-blocking timing and control an LED according to the detected button event.

## HARDWARE REQUIREMENTS
- STM32 development board (Blue Pill / Nucleo)
- Push-button switch
- LED
- Current-limiting resistor
- Connecting wires and suitable power supply

## SOFTWARE REQUIREMENTS
- STM32CubeMX
- Keil MDK
- STM32 HAL Libraries

## FUNCTIONAL REQUIREMENTS

Classify button presses according to their duration:

- **Short press:** Less than 1 second.
- **Long press:** Greater than or equal to 1 second.

### Required LED Behavior

| User Action | System Response |
|---|---|
| Short press | Toggle LED |
| Long press | LED enters continuous blinking mode |
| Next short press | Stop blinking |
| Long press again | Return to blinking mode |

## IMPORTANT CONSTRAINT
The application must not use a blocking delay to determine whether the button is a long press.

Button-press duration must be measured using a non-blocking millisecond time base.

## CORE LOGIC / PSEUDOCODE
1. Initialize HAL, the system clock, and GPIO.
2. Initialize variables for button state, press time, release time, and LED mode.
3. Continuously monitor the button.
4. When a valid press is detected, record the starting time using `HAL_GetTick()`.
5. Continue executing the application while the button remains pressed.
6. When the button is released, record the release time.
7. Calculate:

   `press_duration = release_time - start_time`

8. Classify the press:
   - If duration is less than 1000 ms, identify a short press.
   - If duration is 1000 ms or more, identify a long press.
9. For a short press:
   - Toggle the LED in normal mode.
   - If blinking is active, stop blinking.
10. For a long press:
    - Activate continuous LED blinking mode.
11. While blinking mode is active, use elapsed-time checks to toggle the LED periodically without blocking the main application.
12. Repeat the process for subsequent button events.

## IMPORTANT HAL FUNCTIONS
- `HAL_GPIO_ReadPin()` – Reads the push-button input.
- `HAL_GPIO_WritePin()` – Sets the LED state.
- `HAL_GPIO_TogglePin()` – Toggles the LED.
- `HAL_GetTick()` – Measures press duration and blinking intervals.

## EXPECTED OUTPUT
1. A short press toggles the LED.
2. A long press activates continuous blinking.
3. The next short press stops blinking.
4. Another long press activates blinking again.
5. The program remains responsive while measuring button duration.

## INFERENCE
This task demonstrates non-blocking time measurement, button-event classification, GPIO control, and state-based LED behavior using STM32 HAL functions.

## CIRCUIT DIAGRAM
![Circuit Diagram](circuit.png)
