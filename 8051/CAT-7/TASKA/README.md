
# CONTINUOUS LAB EVALUATION – 7

**DATE:** 24-08-2026

## NAME OF EXPERIMENT

16×2 LCD Initialization and Character/String Display

## HARDWARE SETUP / PLATFORM

- 8051 Toolchain Setup
- AT89S52 Development Board
- 16×2 HD44780-Compatible LCD
- Board Schematics and LCD Datasheet

## TASK NO

**TASK 7A: LCD INITIALIZATION AND CHARACTER/STRING DISPLAY**

Develop a 4-bit GPIO-based LCD driver using bare-metal Embedded C programming for the AT89S52 microcontroller.

The LCD driver must initialize the display and support the transmission of commands, characters and strings.

## PROBLEM STATEMENT

Interface a 16×2 HD44780-compatible LCD with the AT89S52 microcontroller using a 4-bit parallel interface.

Configure the LCD for 4-bit, 2-line operation and develop functions to initialize the LCD, send commands and display characters and strings.

## FUNCTIONAL REQUIREMENTS

1. Configure the LCD in 4-bit interface mode.
2. Initialize the LCD for 2-line operation.
3. Configure the LCD display and cursor settings.
4. Implement functions for sending LCD commands and character data.
5. Display characters and strings on the LCD.
6. Display text on both rows of the LCD.

## REQUIRED FUNCTIONS

```c
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
```

## LCD INTERFACE

| LCD Signal | Function |
|---|---|
| RS | Register Select |
| RW | Read/Write |
| E | Enable |
| D4–D7 | 4-bit Data Lines |
| VCC | Power Supply |
| GND | Ground |
| V0 | Contrast Control |

## LCD INITIALIZATION

The LCD initialization sequence configures the HD44780 controller for the required operating mode.

The configuration includes:

- 4-bit interface mode
- 2-line display
- 5×8 character font
- Display ON/OFF configuration
- Cursor configuration
- Entry mode configuration
- Display clear and cursor positioning

## TOPICS / CONSTRAINTS

- AT89S52 Microcontroller
- Bare-Metal Embedded C
- Direct GPIO Register Access
- HD44780 LCD Controller
- 4-bit Parallel LCD Interface
- LCD Initialization
- LCD Command and Data Transfer
- Character and String Display

**Implementation Constraints:**

- Do not use Arduino APIs.
- Do not use HAL libraries.
- Do not use RTOS services.
- Use direct GPIO access.
- Refer to the HD44780-compatible LCD datasheet for initialization commands.

## CORE LOGIC / PSEUDOCODE

1. Initialize the GPIO pins connected to the LCD.
2. Configure the LCD for 4-bit communication.
3. Send the required LCD initialization commands.
4. Configure the LCD for 2-line operation.
5. Configure display and cursor settings.
6. Clear the LCD.
7. Send character data to the LCD.
8. Display strings on the required LCD rows.

## INFERENCE

The experiment demonstrates interfacing a 16×2 HD44780-compatible LCD with the AT89S52 microcontroller using a 4-bit parallel interface.

It provides an understanding of LCD initialization, command and data transmission, display configuration and character/string display using bare-metal Embedded C programming.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
