
# CONTINUOUS LAB EVALUATION – 4

**COURSE:** Fundamentals of Internet of Things + Lab  
**PLATFORM:** 8051 Microcontroller  
**MICROCONTROLLER:** 8051 (REG51-compatible)

## NAME OF EXPERIMENT

Keypad Interfacing with Seven-Segment Display and Multiple LED Patterns Using 8051

## AIM

To develop an Embedded C program to interface a 4×3 matrix keypad, a seven-segment display, and four LEDs with the 8051 microcontroller, enabling keypad-controlled LED operations and numerical display.

## HARDWARE SETUP / PLATFORM

- 8051 microcontroller development board
- 4×3 matrix keypad (or compatible keypad)
- Seven-segment display
- Four LEDs
- Current-limiting resistors
- Suitable display-driving circuitry
- Regulated power supply
- Keil µVision IDE

## TASK NO

**CAT4 – Keypad-Controlled LED Patterns and Seven-Segment Display**

Implement a keypad-controlled system in which keys 0–9 are detected, the corresponding digit is displayed on a seven-segment display, and different LED operations are executed based on the key pressed.

## PIN CONFIGURATION

| Component | 8051 Port / Pin | Function |
|---|---|---|
| LED 1 | P1.0 | LED output |
| LED 2 | P1.1 | LED output |
| LED 3 | P1.2 | LED output |
| LED 4 | P1.3 | LED output |
| Seven-segment display | P0 | Segment pattern output |
| Keypad row 1 | P2.7 | Row scanning |
| Keypad row 2 | P2.6 | Row scanning |
| Keypad row 3 | P2.5 | Row scanning |
| Keypad row 4 | P2.4 | Row scanning |
| Keypad column 1 | P2.3 | Key input |
| Keypad column 2 | P2.2 | Key input |
| Keypad column 3 | P2.1 | Key input |

The code uses common-cathode seven-segment encoding. The actual hardware must provide the appropriate segment-driving circuitry. On a classic 8051, Port 0 also requires suitable pull-up or driver circuitry for HIGH outputs.

## KEYPAD MAPPING

| Row | Column 1 | Column 2 | Column 3 |
|---|---|---|---|
| Row 1 | 1 | 2 | 3 |
| Row 2 | 4 | 5 | 6 |
| Row 3 | 7 | 8 | 9 |
| Row 4 | Not used | 0 | Not used |

The program scans each row by driving it LOW and checking the three column inputs.

## WORKING PRINCIPLE

### 1. Keypad Scanning

The `keypad_scan()` function scans the four keypad rows sequentially.

The row-selection values are:

- `0x7F` – Select row 1
- `0xBF` – Select row 2
- `0xDF` – Select row 3
- `0xEF` – Select row 4

When a column becomes LOW, the corresponding key is detected.

The program executes a software delay, displays the detected digit, waits for key release, and returns the key value.

If no supported key is pressed, the function returns `0xFF`.

### 2. Seven-Segment Display

The seven-segment display is connected to Port 0.

The array `seg_cod[10]` stores common-cathode segment codes for digits 0–9.

| Digit | Hexadecimal Code |
|---|---|
| 0 | 0x3F |
| 1 | 0x06 |
| 2 | 0x5B |
| 3 | 0x4F |
| 4 | 0x66 |
| 5 | 0x6D |
| 6 | 0x7D |
| 7 | 0x07 |
| 8 | 0x7F |
| 9 | 0x6F |

The function `display_digit()` writes the selected digit's segment code to Port 0.

### 3. Keypad-Based LED Operations

The main program uses a `switch(key)` statement to select the LED operation.

| Key | LED Operation |
|---|---|
| 1 | Set P1.0 HIGH |
| 2 | Set P1.1 HIGH |
| 3 | Set P1.2 HIGH |
| 4 | Set P1.3 HIGH |
| 5 | Running LED pattern |
| 6 | Alternating LED pattern |
| 7 | Four-bit binary counter |
| 8 | Blink all four LEDs |
| 9 | Clear LED outputs |
| 0 | Clear LED outputs and display 0 |

For keys 1–4, the code writes `0x01`, `0x02`, `0x04`, or `0x08` to Port 1. These operations set the selected LED output HIGH and clear the other Port 1 outputs.

### 4. Running LED Pattern

Function: `running_led()`

The program generates the sequence:

`0001 → 0010 → 0100 → 1000`

Each output pattern is followed by a software delay.

### 5. Alternating LED Pattern

Function: `alternate_led()`

The output alternates between:

`1010 → 0101`

This creates alternating LED groups when active-HIGH LEDs are used.

### 6. Four-Bit Binary Counter

Function: `binary_counter()`

The program increments a counter from 0 to 15 and writes the value to Port 1.

The lower four LED outputs represent the binary sequence:

`0000 → 0001 → 0010 → ... → 1111`

### 7. Blinking All LEDs

Function: `blink_all()`

The program alternates between:

`1111 → 0000`

This switches all four LED outputs HIGH and LOW with software delays.

## SOFTWARE DELAY

The `delay()` function uses two nested `for` loops, each running up to 200 iterations.

This provides an approximate delay between LED output changes and during keypad handling.

The delay duration depends on the microcontroller clock frequency and compiled instructions.

## ALGORITHM

1. Start the program.
2. Initialize Port 1 and Port 0 to `0x00`.
3. Enter an infinite loop.
4. Scan keypad rows sequentially through Port 2.
5. Check the column inputs for a pressed key.
6. When a supported key is detected, execute the delay function.
7. Display the corresponding digit on the seven-segment display.
8. Wait until the key is released.
9. Return the detected key value.
10. Execute the corresponding LED operation using the `switch` statement.
11. Repeat the keypad scanning process continuously.

## SOURCE CODE

The experiment is implemented in Embedded C using `reg51.h`.

The major functions are:

- `delay()` – Generates software delay
- `display_digit()` – Displays a decimal digit on the seven-segment display
- `keypad_scan()` – Scans the keypad and identifies a pressed key
- `running_led()` – Generates the running LED sequence
- `binary_counter()` – Displays a four-bit binary count using LEDs
- `alternate_led()` – Generates alternating LED patterns
- `blink_all()` – Flashes all four LEDs simultaneously
- `main()` – Performs initialization, keypad scanning, and operation selection

The complete implementation is available in the accompanying Embedded C source file.

## EXPECTED OUTPUT

When a supported numerical key is pressed, the corresponding digit is written to the seven-segment display.

The four LEDs perform the operation assigned to the selected key.

Keys 1–4 select individual LED outputs, while keys 5–8 execute predefined LED patterns.

Keys 9 and 0 clear the LED outputs.

The program then returns to keypad scanning and waits for another input.

## RESULT

The Embedded C program implements keypad-based selection of LED operations and numerical output through a seven-segment display using the 8051 microcontroller.

## INFERENCE

This experiment demonstrates matrix keypad scanning, digital input detection, GPIO output control, seven-segment display encoding, and conditional program execution.

It also illustrates how multiple embedded operations can be controlled through a single keypad interface.

## CIRCUIT DIAGRAM
![706234531-ed44d29f-1d8b-4396-abe5-7934b9ed8cbd](706234531-ed44d29f-1d8b-4396-abe5-7934b9ed8cbd.jpg
)
