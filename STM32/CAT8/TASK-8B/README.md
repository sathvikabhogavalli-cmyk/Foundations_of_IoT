# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8

**DATE:** 18/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** STM32CubeMX + Keil MDK + STM32 Development Board (Blue Pill – STM32F103C8T6)

---

## TASK 8B – Event-Based Control

### 1. Circuit Diagram

The experiment uses a push-button connected to the STM32 GPIO input pin and the onboard LED connected to the GPIO output pin.

- **Development Board:** STM32 Blue Pill
- **Microcontroller IC:** STM32F103C8T6
- **GPIO Input Pin:** PA3 – Push-button
- **GPIO Output Pin:** PC13 – Onboard LED
- **Button Configuration:** Input with internal pull-up resistor
- **LED Configuration:** Output push-pull

**Hardware Connections:**

- Connect one terminal of the push-button to PA3.
- Connect the other terminal of the push-button to GND.
- The onboard LED is controlled through PC13.

![alt text](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

This experiment demonstrates event-based LED control using a push-button and STM32 GPIO pins.

The push-button is connected to PA3, which is configured as an input with an internal pull-up resistor. When the button is pressed, PA3 reads LOW (GPIO_PIN_RESET).

When a button press is detected, a 20 ms delay is introduced to reduce switch bounce. The button state is then checked again. If the button is still pressed, the LED connected to PC13 is toggled using `HAL_GPIO_TogglePin()`.

The program waits until the button is released before detecting another press. This ensures that one valid button press produces only one LED toggle.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO peripherals.
4. Configure PA3 as an input with an internal pull-up resistor.
5. Configure PC13 as an output push-pull pin.
6. Continuously monitor the state of PA3.
7. If the button is pressed (LOW):
   - Introduce a 20 ms debounce delay.
   - Read the button state again.
   - If it is still LOW, toggle the LED on PC13.
   - Wait until the button is released.
8. Repeat the process continuously.

**Code Base:**

The experiment uses the following STM32 HAL functions:

| Purpose | HAL Function |
|---|---|
| Read push-button state | `HAL_GPIO_ReadPin()` |
| Toggle LED state | `HAL_GPIO_TogglePin()` |
| Introduce debounce delay | `HAL_Delay()` |
| Initialize GPIO | `HAL_GPIO_Init()` |
| Initialize HAL library | `HAL_Init()` |

### 3. INFERENCE

The experiment successfully demonstrates event-based control using the STM32 Blue Pill development board. The onboard LED connected to PC13 toggles its state whenever the push-button connected to PA3 is pressed.

A 20 ms debounce delay reduces the effect of mechanical switch bouncing, while waiting for the button release prevents multiple toggles from a single press. This demonstrates GPIO input reading, LED state toggling and basic software debouncing using STM32 HAL functions.
