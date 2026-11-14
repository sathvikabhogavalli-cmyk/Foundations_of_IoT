# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12

**NAME OF EXP:** STM32 GPIO – Short Press and Long Press Detection for LED Control

**HARDWARE SETUP / PLATFORM:** STM32CubeMX + Keil MDK + STM32F401RE Development Board

---

## TASK 3 – Short Press and Long Press Detection

### 1. Circuit Diagram

The experiment demonstrates GPIO input and output operations using the STM32 microcontroller. GPIO pin PC13 is configured as a digital input to detect push button presses, while PA5 is configured as a digital output to control the LED.

**Hardware Components:**

- **Development Board:** STM32F401RE
- **Microcontroller IC:** STM32F401RE
- **Input GPIO Pin:** PC13
- **Output GPIO Pin:** PA5
- **Input Device:** Push Button
- **Output Device:** LED

**Connections:**

- Push Button → GPIO PC13
- LED → GPIO PA5
- Common Ground → GND

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment demonstrates short press and long press detection using the STM32 HAL library.

GPIO pin PC13 is configured as an input to detect push button presses, while PA5 is configured as an output to control the LED.

Initially, the LED is turned OFF. When the push button is pressed, the program introduces a debounce delay of 20 milliseconds and verifies that the button is still pressed.

The program records the button press start time using `HAL_GetTick()`. It continuously monitors the button until it is released and calculates the total press duration.

Based on the duration, two operations are performed:

- **Short Press (less than 1000 ms):** The LED state is toggled. If the LED is OFF, it turns ON; if it is ON, it turns OFF.
- **Long Press (1000 ms or more):** The LED starts blinking continuously with an ON/OFF interval of 500 milliseconds.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Enable GPIOA, GPIOC, and GPIOH peripheral clocks.
4. Configure PC13 as GPIO input.
5. Configure PA5 as GPIO output.
6. Initialize the LED state as OFF.
7. Continuously monitor the push button state.
8. Check whether the button is pressed (LOW state).
9. Introduce a debounce delay of 20 milliseconds.
10. Verify that the button is still pressed.
11. Record the button press start time using `HAL_GetTick()`.
12. Wait until the push button is released.
13. Calculate the button press duration.
14. Introduce a debounce delay of 20 milliseconds.
15. Check the press duration:
    - If the duration is less than 1000 ms, toggle the LED state.
    - If the duration is 1000 ms or more, enter continuous blinking mode.
16. In long press mode, toggle the LED every 500 milliseconds.
17. Repeat the process continuously for short presses.

**Code Base:**

The GPIO operations and button press duration measurement are performed using the following STM32 HAL functions and variables:

- `HAL_Init()` – Initializes the HAL library.
- `HAL_GPIO_Init()` – Configures GPIO pins as input or output.
- `HAL_GPIO_ReadPin()` – Reads the push button input state.
- `HAL_GPIO_WritePin()` – Sets or resets the LED output pin.
- `HAL_GPIO_TogglePin()` – Toggles the LED state.
- `HAL_GetTick()` – Returns the system tick count in milliseconds.
- `HAL_Delay()` – Introduces debounce delays and blinking intervals.

**Important Variables:**

- `ledState` – Stores the current LED state.
- `pressStartTime` – Stores the time when the button is pressed.
- `pressDuration` – Stores the total duration of the button press.

The difference between the current tick count and the recorded press start time is used to calculate the button press duration.

### 3. Inference

The STM32F401RE successfully detects short and long push button presses through GPIO pin PC13 and controls the LED connected to PA5.

A short press toggles the LED between ON and OFF states, while a long press activates continuous LED blinking at 500-millisecond intervals.

This experiment demonstrates GPIO input/output configuration, button press duration measurement, software debouncing, and short press/long press detection using STM32 HAL functions.
