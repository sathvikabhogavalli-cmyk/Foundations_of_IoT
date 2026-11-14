# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12

**NAME OF EXP:** STM32 GPIO Input/Output – Push Button-Controlled LED

**HARDWARE SETUP / PLATFORM:** STM32CubeMX + Keil MDK + STM32F401RE Development Board

---

## TASK 2 – On Board Switch Control with State Remembrance

### 1. Circuit Diagram

The experiment demonstrates GPIO input and output operations using the STM32 microcontroller. GPIO pin PC13 is configured as a digital input to detect push button presses, while PA5 is configured as a digital output to control the onboard LED.

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

The experiment demonstrates push button-controlled LED switching using the STM32 HAL library.

GPIO pin PC13 is configured as an input to detect the push button state, and PA5 is configured as an output to control the LED.

Initially, the LED is turned OFF. The program continuously monitors the push button input. When the button is pressed, the input changes from HIGH to LOW.

A falling-edge transition is detected by comparing the current button state with the previous button state. A debounce delay of 20 milliseconds is introduced to avoid false triggering due to mechanical switch bouncing.

After confirming the button press, the `ledState` variable is toggled. If the LED is OFF, it turns ON; if it is ON, it turns OFF.

The program waits until the button is released before accepting another press.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Enable GPIOA, GPIOC, and GPIOH peripheral clocks.
4. Configure PC13 as GPIO input.
5. Configure PA5 as GPIO output.
6. Initialize the LED state as OFF.
7. Initialize the previous button state as HIGH.
8. Continuously read the current button state from PC13.
9. Check whether a HIGH-to-LOW transition occurs.
10. Introduce a debounce delay of 20 milliseconds.
11. Verify that the button is still pressed.
12. Toggle the LED state.
13. If the LED state is ON, set PA5 HIGH.
14. Otherwise, set PA5 LOW.
15. Wait until the push button is released.
16. Introduce another 20 ms debounce delay.
17. Update the previous button state.
18. Repeat the process continuously.

**Code Base:**

The GPIO operations are performed using the following STM32 HAL functions and variables:

- `HAL_Init()` – Initializes the HAL library.
- `HAL_GPIO_Init()` – Configures GPIO pins as input or output.
- `HAL_GPIO_ReadPin()` – Reads the push button input state.
- `HAL_GPIO_WritePin()` – Sets or resets the LED output pin.
- `HAL_Delay()` – Introduces debounce delays.
- `GPIO_PIN_SET` – Represents the HIGH input/output state.
- `GPIO_PIN_RESET` – Represents the LOW input/output state.

**Important Variables:**

- `ledState` – Stores the current LED state.
- `lastButtonState` – Stores the previous push button state.
- `currentButtonState` – Stores the current push button state.

### 3. Inference

The STM32F401RE successfully detects push button presses through GPIO pin PC13 and controls the LED connected to PA5.

Each valid button press toggles the LED between ON and OFF states. The debounce mechanism prevents multiple unwanted toggles caused by mechanical switch bouncing.

This experiment demonstrates GPIO input/output configuration, edge detection, push button interfacing, and software debouncing using STM32 HAL functions.
