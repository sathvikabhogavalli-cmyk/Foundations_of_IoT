# CONTINUOUS LAB EVALUATION – 4

**DATE:** 03-08-2026

## NAME OF EXPERIMENT
Human-Machine Interface Using Matrix Keypad, LEDs and Seven-Segment Display

## HARDWARE SETUP / PLATFORM
- AT51 Programming Setup
- AT89S52 Development Board
- Matrix Keypad
- Seven-Segment Display
- LEDs
- Hardware Debugging using Multimeter

## TASK NO
Design and implement a simple embedded user interface using the AT89S52 microcontroller, in which the matrix keypad acts as the input device, the seven-segment display provides visual feedback, and the LEDs indicate different operating modes.

Whenever a valid key is pressed, the corresponding key value must be displayed on the seven-segment display, and the associated LED operation must be executed.

## TOPICS / CONSTRAINTS
- AT51 Programming Setup
- AT89S52 Development Board
- Board Schematics
- AT51 Pin Diagram
- Hardware Debugging using Multimeter
- Human-Machine Interface using Matrix Keypad, LEDs and Seven-Segment Display

**Implementation Constraints:**
- Strictly use embedded C programming for AT89S52.
- Do not use Arduino APIs.
- Do not use Keil/CMSIS HAL libraries.
- Do not use RTOS services.

## FUNCTIONAL REQUIREMENTS

The system shall perform the following operations based on the key pressed on the matrix keypad.

| Key Press | Seven-Segment Display | LED Operation |
|---|---|---|
| 1 | Displays 1 | LED 1 ON |
| 2 | Displays 2 | LED 2 ON |
| 3 | Displays 3 | LED 3 ON |
| 4 | Displays 4 | LED 4 ON |
| 5 | Displays 5 | Running LED Pattern |
| 6 | Displays 6 | Alternate LED Pattern (1010 / 0101) |
| 7 | Displays 7 | Binary Counter (0 to 15) |
| 8 | Displays 8 | All LEDs Blink |
| 9 | Displays 9 | All LEDs OFF |
| 0 | Displays 0 | Reset System |

## CORE LOGIC / PSEUDOCODE

1. Initialize the matrix keypad, seven-segment display and LED ports.
2. Continuously scan the matrix keypad to detect a valid key press.
3. Once a valid key is detected:
   - Display the corresponding key value on the seven-segment display.
   - Pass the key value to the LED control function.
4. Based on the received key:
   - Keys 1–4: Turn ON the corresponding individual LED.
   - Key 5: Execute the running LED pattern.
   - Key 6: Execute the alternate LED pattern.
   - Key 7: Execute the binary counter from 0 to 15.
   - Key 8: Blink all LEDs.
   - Key 9: Turn OFF all LEDs.
   - Key 0: Reset the system.
5. Continue scanning the keypad for subsequent inputs.

## REQUIRED FUNCTION DEFINITIONS

The program shall be modular and consist of the following separate functions:

```c
void keypad_scan(void);

void display_digit(unsigned char value);

void LED_control(unsigned char key);

void running_LED(void);

void binary_counter(void);

void alternate_LED(void);

void blink_all(void);
```

Each function shall perform its designated operation independently.

## INFERENCE

The experiment demonstrates the implementation of a basic embedded Human-Machine Interface using the AT89S52 microcontroller. The matrix keypad is used to provide user input, the seven-segment display provides visual feedback, and the LEDs indicate different operating modes based on the selected key.

The experiment also demonstrates modular embedded C programming, GPIO interfacing, keypad scanning, display interfacing and control of external hardware peripherals without relying on Arduino APIs, HAL libraries or RTOS services.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
