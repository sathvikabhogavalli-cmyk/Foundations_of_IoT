# CONTINUOUS LAB EVALUATION – 7

**DATE:** 24-08-2026

## NAME OF EXPERIMENT

16×2 LCD Driver Development and Dynamic Display Control

## HARDWARE SETUP / PLATFORM

- 8051 Toolchain Setup
- AT89S52 Development Board
- 16×2 HD44780-Compatible LCD
- 4×4 Matrix Keypad
- Digital Multimeter
- Digital Storage Oscilloscope (DSO)
- Board Schematics and HD44780 Datasheet

## TASK NO

Develop an Embedded C LCD driver for the AT89S52 microcontroller that initializes a 16×2 character LCD, positions the cursor, displays characters and strings, updates values, and clears the display.

The LCD driver must use direct GPIO interfacing and bare-metal Embedded C programming.

## TASK 7A: LCD INITIALIZATION AND CHARACTER/STRING DISPLAY

Develop a 4-bit GPIO-based LCD driver by deriving the required command sequence from the HD44780-compatible LCD datasheet.

**Activities to be performed:**

1. Configure the LCD in 4-bit, 2-line mode.
2. Implement the required LCD initialization function.
3. Develop functions to send commands and data to the LCD.
4. Display individual characters and strings.
5. Display text on both rows of the LCD.

### REQUIRED FUNCTIONS

```c
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
```

### LCD INTERFACE

The standard 16×2 HD44780-compatible LCD uses a parallel interface.

The relevant interface signals are:

- RS – Register Select
- RW – Read/Write
- E – Enable
- D4–D7 – Four-bit data lines
- VCC – Power Supply
- GND – Ground
- V0 – Contrast Control

### LCD INITIALIZATION

LCD initialization involves sending a defined sequence of commands to configure the LCD controller.

The initialization process includes:

1. Selecting the interface mode.
2. Configuring the number of display lines.
3. Configuring the character font.
4. Configuring display ON/OFF settings.
5. Configuring cursor settings.
6. Configuring the entry mode.
7. Clearing the display and setting the cursor position.

### LCD CONFIGURATION

| Parameter | Configuration |
|---|---|
| LCD Type | HD44780-Compatible |
| Display Size | 16×2 |
| Interface | 4-bit |
| Display Lines | 2 |
| Character Font | 5×8 |
| Data Pins | D4–D7 |

## TASK 7B: CURSOR POSITIONING AND DYNAMIC VALUE UPDATE

Develop LCD cursor-positioning and data-update functions.

### REQUIRED FUNCTIONS

```c
lcd_goto(row, column);
lcd_puts(string);
lcd_print_number(value);
```

**Activities to be performed:**

1. Develop a function to position the cursor at the required row and column.
2. Display strings at the selected cursor position.
3. Display numerical values on the LCD.
4. Update displayed values dynamically.
5. Use the LCD's DDRAM addressing mechanism for cursor positioning.

### LCD DISPLAY ORGANIZATION

The LCD consists of two rows, each capable of displaying 16 characters.

The HD44780 controller maintains an internal Display Data RAM (DDRAM), which stores the characters displayed on the LCD.

The first and second rows correspond to different DDRAM address ranges.

Cursor positioning is performed by sending the appropriate DDRAM address command to the LCD controller.

## TASK 7C: 4×4 KEYPAD-BASED CHARACTER MOVEMENT

Develop an interactive LCD application in which a character is moved across the 16×2 LCD using a 4×4 matrix keypad.

Assign four keys as directional controls.

### KEYPAD FUNCTIONAL REQUIREMENTS

| Key Press | Direction | Operation |
|---|---|---|
| 2 | ↑ | Move Up |
| 8 | ↓ | Move Down |
| 4 | ← | Move Left |
| 6 | → | Move Right |

**Activities to be performed:**

1. Interface the 4×4 matrix keypad with the AT89S52.
2. Scan the keypad to identify the pressed key.
3. Display a character at the current LCD position.
4. Move the character based on the corresponding directional key.
5. Update the character position on the LCD.

## TOPICS / CONSTRAINTS

- 8051 Toolchain Setup
- AT89S52 Development Board
- Bare-Metal Embedded C Programming
- 16×2 LCD Interfacing
- HD44780 LCD Controller
- 4-bit Parallel Communication
- LCD Initialization
- LCD Command and Data Transfer
- DDRAM Addressing
- Cursor Positioning
- Character and String Display
- Dynamic Value Updating
- 4×4 Matrix Keypad Interfacing

**Implementation Constraints:**

- Strictly use bare-metal Embedded C programming.
- Do not use Arduino APIs.
- Do not use HAL libraries.
- Do not use RTOS services.
- Use direct GPIO register access for LCD and keypad interfacing.
- Configure the LCD in 4-bit, 2-line mode.
- Refer to the HD44780-compatible LCD datasheet for initialization commands.

## CORE LOGIC / PSEUDOCODE

### 1. LCD Initialization and Display

1. Initialize the GPIO pins connected to the LCD.
2. Configure the LCD for 4-bit communication.
3. Send the initialization command sequence.
4. Configure the LCD for 2-line operation.
5. Configure display, cursor and entry-mode settings.
6. Clear the display.
7. Send characters and strings to the LCD.
8. Display text on both rows.

### 2. Cursor Positioning and Dynamic Value Update

1. Identify the required row and column.
2. Determine the corresponding DDRAM address.
3. Send the cursor-positioning command.
4. Display the required string or numerical value.
5. Update the displayed value when necessary.

### 3. Keypad-Based Character Movement

1. Initialize the LCD and keypad interface.
2. Display a character at the initial LCD position.
3. Continuously scan the keypad.
4. Identify directional key presses.
5. Update the character position according to the selected direction.
6. Refresh the LCD to display the character at its updated position.
7. Repeat for subsequent keypad inputs.

## INFERENCE

The experiment demonstrates the development of a 4-bit LCD driver using the AT89S52 microcontroller and an HD44780-compatible 16×2 character LCD.

It provides an understanding of LCD initialization, command and data transmission, DDRAM addressing, cursor positioning, character display and dynamic numerical value updating.

The keypad-based character movement task demonstrates interactive user input and display control using a 4×4 matrix keypad.

The experiment illustrates the implementation of a basic embedded human-machine interface using direct GPIO access and bare-metal Embedded C programming without Arduino APIs, HAL libraries or RTOS services.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
