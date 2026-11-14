# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12

**NAME OF EXP:** STM32 GPIO Output Control – LED Blinking with Custom Time Intervals

**HARDWARE SETUP / PLATFORM:** STM32CubeMX + Keil MDK + STM32F401RE Development Board

---

## TASK 1 – On Board LED Bring UP

### 1. Circuit Diagram

The experiment demonstrates digital output control using the GPIO peripheral of the STM32 microcontroller. The GPIO pin PA5 is configured as an output to control the onboard LED.

**Hardware Components:**

- **Development Board:** STM32F401RE
- **Microcontroller IC:** STM32F401RE
- **GPIO Port:** GPIOA
- **GPIO Pin:** PA5
- **Peripheral:** Onboard LED

**Connections:**

- GPIO PA5 → Onboard LED
- GND → Common Ground

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment demonstrates GPIO output control using the STM32 HAL library. The GPIO pin PA5 is configured as a digital output to control the onboard LED.

The program generates a specific blinking pattern by switching the LED ON and OFF for different time intervals using `HAL_GPIO_WritePin()` and `HAL_Delay()`.

The LED follows the sequence:

1. LED ON for 200 milliseconds.
2. LED OFF for 200 milliseconds.
3. LED ON for 200 milliseconds.
4. LED OFF for 200 milliseconds.
5. LED ON for 2000 milliseconds.
6. LED OFF for 100 milliseconds.
7. Repeat the entire sequence continuously.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Enable GPIOA and GPIOH peripheral clocks.
4. Configure GPIO pin PA5 as output.
5. Turn the LED ON.
6. Introduce a delay of 200 ms.
7. Turn the LED OFF.
8. Introduce a delay of 200 ms.
9. Turn the LED ON.
10. Introduce a delay of 200 ms.
11. Turn the LED OFF.
12. Introduce a delay of 200 ms.
13. Turn the LED ON.
14. Introduce a delay of 2000 ms.
15. Turn the LED OFF.
16. Introduce a delay of 100 ms.
17. Repeat the process continuously.

**Code Base:**

The GPIO operations are performed using the following STM32 HAL functions:

- `HAL_Init()` – Initializes the HAL library.
- `HAL_GPIO_Init()` – Configures the GPIO pin as output.
- `HAL_GPIO_WritePin()` – Sets or resets the GPIO output pin to control the LED.
- `HAL_Delay()` – Introduces delays in milliseconds.
- `__HAL_RCC_GPIOA_CLK_ENABLE()` – Enables the GPIOA peripheral clock.
- `__HAL_RCC_GPIOH_CLK_ENABLE()` – Enables the GPIOH peripheral clock.

The `GPIO_PIN_SET` state turns the LED ON, while `GPIO_PIN_RESET` turns it OFF for the active-high LED configuration.

### 3. Inference

The STM32F401RE successfully controls the onboard LED connected to GPIO pin PA5 using predefined time intervals.

The LED produces a repeating blinking pattern consisting of short ON/OFF intervals followed by a longer ON duration.

This experiment demonstrates GPIO initialization, digital output control, and time-based LED sequencing using STM32 HAL functions.
![706250344-98158e25-f281-4a73-9303-d578643fc896](706250344-98158e25-f281-4a73-9303-d578643fc896.png)
