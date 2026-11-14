# CONTINUOUS LAB EVALUATION – 7

**COURSE:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**PLATFORM:** 8051 Microcontroller  
**MICROCONTROLLER:** AT89S52 / 8051-compatible microcontroller

## NAME OF EXPERIMENT

LCD Interfacing, Cursor Positioning, Dynamic Display, and Keypad-Based Character Movement Using 8051 Microcontroller

## AIM

To interface a 16×2 LCD with the 8051 microcontroller in 4-bit mode and implement three applications:

1. Displaying a predefined text message on the LCD.
2. Positioning the LCD cursor and displaying a continuously incrementing counter.
3. Controlling the position of a character on the LCD using a 4×4 matrix keypad.

## HARDWARE SETUP / PLATFORM

- AT89S52 / 8051-compatible microcontroller development board
- 16×2 character LCD (HD44780-compatible)
- 4×4 matrix keypad for Task C
- LCD contrast adjustment circuit
- Regulated power supply
- Crystal oscillator and supporting circuitry
- Keil µVision IDE
- Embedded C programming environment

## TASK NO

**CAT7 – LCD INTERFACING AND KEYPAD CONTROL**

### TASK A – LCD Interfacing in 4-bit Mode

Display the message `HELLO FROM 8051` on a 16×2 LCD using the 8051 microcontroller.

### TASK B – LCD Cursor Positioning and Dynamic Update

Display a predefined message on the first LCD row and a continuously incrementing counter on the second row.

### TASK C – LCD with Keypad-Based Character Movement

Interface a 4×4 matrix keypad and move the character `O` across the 16×2 LCD using directional keys.

These are three independent programs and must be compiled and executed separately.

## COMMON LCD PIN CONFIGURATION

All three tasks use the same LCD connections.

| LCD Signal | 8051 Pin | Function |
|---|---|---|
| RS | P3.2 | Register selection |
| E | P3.3 | LCD enable |
| D4 | P3.4 | Data bit 4 |
| D5 | P3.5 | Data bit 5 |
| D6 | P3.6 | Data bit 6 |
| D7 | P3.7 | Data bit 7 |
| RW | GND | Write-only operation |
| VSS | GND | Ground |
| VDD | +5 V | LCD supply |
| V0 | Contrast circuit | Display contrast adjustment |

The LCD operates in 4-bit mode, using only data pins D4–D7.

The LCD is controlled using the RS and E signals.

## COMMON LCD WORKING PRINCIPLE

### 1. Four-Bit Data Transmission

The LCD receives each command or character as two 4-bit transfers.

The higher nibble is transmitted first, followed by the lower nibble.

The statement:

`LCD_PORT = (LCD_PORT & 0x0F) | (nibble & 0xF0);`

updates the upper four bits of Port 3 while preserving the lower four bits.

### 2. Enable Signal

The `lcd_enable()` function generates a HIGH-to-LOW pulse on the LCD enable pin.

This pulse allows the LCD to accept the transmitted data.

### 3. Command Transmission

The `lcd_cmd()` function sets RS to LOW and sends the command in two 4-bit transfers.

RS = 0 indicates command-register access.

### 4. Character Transmission

The `lcd_data()` function sets RS to HIGH and transmits the character data.

RS = 1 indicates data-register access.

### 5. LCD Initialization

The `lcd_init()` function initializes the LCD and sends the following commands:

| Command | Function |
|---|---|
| 0x20 | Initial 4-bit interface selection |
| 0x28 | 4-bit mode, two display lines, 5×8 character format |
| 0x0C | Display ON, cursor OFF |
| 0x06 | Entry mode: increment cursor position |
| 0x01 | Clear LCD display |

Software delays are used between LCD operations.

---

## TASK A – LCD INTERFACING IN 4-BIT MODE

### OBJECTIVE

To interface a 16×2 LCD with the 8051 microcontroller and display the message `HELLO FROM 8051` using 4-bit communication.

### WORKING PRINCIPLE

The program initializes the LCD in 4-bit mode.

After initialization, the program enters an infinite loop.

The `lcd_data()` function is called separately for each character in the message.

The transmitted characters form:

`HELLO FROM 8051`

Five additional space characters are transmitted after the message.

The program then executes:

`lcd_cmd(0x01);`

This clears the LCD display.

The sequence repeats continuously.

### TASK A ALGORITHM

1. Start the program.
2. Configure the LCD control and data connections.
3. Initialize the LCD in 4-bit mode.
4. Enter an infinite loop.
5. Send each character of `HELLO FROM 8051`.
6. Send five additional spaces.
7. Clear the LCD using command `0x01`.
8. Repeat the message transmission.

### TASK A EXPECTED OUTPUT

The LCD repeatedly receives the text:

```text
HELLO FROM 8051
```

The display is cleared after the message and then written again.

Because the program continuously writes and clears the display, visible flickering may occur depending on execution timing.

### TASK A RESULT

The program implements 4-bit LCD communication and repeatedly writes a predefined text message to the LCD.

---

## TASK B – LCD CURSOR POSITIONING AND DYNAMIC COUNTER

### OBJECTIVE

To display a fixed message on the first LCD row and a continuously incrementing counter on the second row using cursor-positioning commands.

### WORKING PRINCIPLE

The program uses the same LCD initialization and 4-bit data transmission functions as Task A.

Three additional functions are implemented.

### 1. LCD Cursor Positioning

Function: `lcd_goto()`

The function accepts a row and column position.

For row 0:

`lcd_cmd(0x80 + column);`

For row 1:

`lcd_cmd(0xC0 + column);`

These commands select the required LCD DDRAM address.

### 2. String Display

Function: `lcd_puts()`

The function accepts a null-terminated character string and transmits each character using `lcd_data()`.

### 3. Integer Display

Function: `lcd_print_number()`

The function converts an unsigned integer into decimal digits.

It extracts digits using modulus and division by 10, temporarily stores them, and displays them in the correct order.

Zero is handled separately.

### MAIN PROGRAM

The LCD first displays:

- Row 1: `Hello 8051`
- Row 2: `Count: `

The counter is initialized to zero.

Inside the infinite loop:

1. The cursor moves to row 1, column 7.
2. The current counter value is displayed.
3. Five spaces are transmitted to clear leftover digit positions.
4. The counter is incremented.
5. An approximate 500 ms software delay is executed.

### TASK B ALGORITHM

1. Start the program.
2. Initialize the LCD.
3. Position the cursor at row 0, column 0.
4. Display `Hello 8051`.
5. Position the cursor at row 1, column 0.
6. Display `Count: `.
7. Initialize the counter to zero.
8. Move the cursor to row 1, column 7.
9. Convert the counter value to decimal characters.
10. Display the counter value.
11. Write spaces after the number.
12. Increment the counter.
13. Execute the software delay.
14. Repeat continuously.

### TASK B EXPECTED OUTPUT

Initial display:

```text
Hello 8051
Count: 0
```

Subsequent display:

```text
Hello 8051
Count: 1
```

The counter continues increasing.

The counter is an `unsigned int`; on a typical Keil C51 target, it ranges from 0 to 65535 and then wraps to 0.

### TASK B RESULT

The program implements LCD cursor positioning, string display, decimal number conversion, and dynamic counter updates.

---

## TASK C – LCD WITH KEYPAD-BASED CHARACTER MOVEMENT

### OBJECTIVE

To interface a 4×4 matrix keypad with the 8051 microcontroller and use directional keys to move the character `O` within a 16×2 LCD.

### HARDWARE CONFIGURATION

Task C uses the same LCD connections as Tasks A and B.

Additionally, a 4×4 matrix keypad is connected to Port 1.

### KEYPAD PIN CONFIGURATION

| Keypad Signal | 8051 Pin | Function |
|---|---|---|
| Row 1 | P1.0 | Row output |
| Row 2 | P1.1 | Row output |
| Row 3 | P1.2 | Row output |
| Row 4 | P1.3 | Row output |
| Column 1 | P1.4 | Column input |
| Column 2 | P1.5 | Column input |
| Column 3 | P1.6 | Column input |
| Column 4 | P1.7 | Column input |

### KEYPAD LAYOUT

| Row | Column 1 | Column 2 | Column 3 | Column 4 |
|---|---|---|---|---|
| 1 | 1 | 2 | 3 | A |
| 2 | 4 | 5 | 6 | B |
| 3 | 7 | 8 | 9 | C |
| 4 | * | 0 | # | D |

### DIRECTIONAL KEY MAPPING

| Key | Direction | Operation |
|---|---|---|
| 2 | Up | Decrease row |
| 8 | Down | Increase row |
| 4 | Left | Decrease column |
| 6 | Right | Increase column |

Other detected keys do not change the character's position.

### WORKING PRINCIPLE

The program initializes the keypad port and LCD.

Initially:

`row = 0`

`col = 0`

The character `O` is displayed at the first row and first column.

The program continuously scans the keypad.

### 1. Keypad Scanning

Function: `keypad_scan()`

The program scans the four keypad rows sequentially.

For each row, one row output is driven LOW while the remaining row bits and column bits are written HIGH.

The upper four bits of Port 1 are read to detect a pressed key.

If a LOW column is detected, the program executes an approximate 20 ms delay and reads the columns again.

The detected row and column are used to identify the corresponding character from the keypad map.

If no key is detected, the function returns zero.

### 2. Character Movement

When a key is detected:

1. The existing character position is cleared by writing a space.
2. The program checks whether the key is 2, 8, 4, or 6.
3. The row or column position is updated if movement is permitted.
4. The character `O` is written at the new position.

### 3. Boundary Conditions

The program restricts movement to the available LCD positions.

- Row range: 0–1
- Column range: 0–15

Movement beyond the LCD boundaries is prevented.

### 4. Key Release Handling

Function: `wait_key_release()`

The program waits until the keypad scanning function detects no pressed key.

An additional software delay is executed after release.

This is intended to prevent a held key from repeatedly moving the character.

### TASK C ALGORITHM

1. Start the program.
2. Initialize Port 1 for keypad scanning.
3. Initialize the LCD in 4-bit mode.
4. Set row and column to zero.
5. Display `O` at the initial position.
6. Scan the keypad continuously.
7. When a key is detected, erase the previous character.
8. Check the pressed key.
9. Update the row or column according to the directional mapping.
10. Ensure the position remains within the LCD boundaries.
11. Display `O` at the updated position.
12. Wait for key release.
13. Repeat continuously.

### TASK C EXPECTED OUTPUT

Initially:

```text
O
```

Pressing key 6 moves the character one column to the right.

Pressing key 4 moves it one column to the left.

Pressing key 8 moves it to the second row when it is on the first row.

Pressing key 2 moves it to the first row when it is on the second row.

Only one movement is intended per recognized key press.

### TASK C RESULT

The program implements keypad scanning and LCD cursor positioning to control a movable character within the boundaries of a 16×2 display.

---

## OVERALL RESULT

Three Embedded C programs were developed for LCD interfacing and keypad-based control using the 8051 microcontroller.

- Task A implements repeated text display using 4-bit LCD communication.
- Task B implements cursor positioning and dynamic numerical display.
- Task C implements keypad-controlled character movement on a 16×2 LCD.

## INFERENCE

This experiment demonstrates 4-bit parallel LCD interfacing, LCD command and data registers, cursor addressing, character display, decimal number conversion, and matrix keypad scanning.

It illustrates how the 8051 microcontroller can interface with output peripherals and input devices to implement both static and interactive embedded applications.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
