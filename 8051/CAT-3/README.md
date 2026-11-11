# CONTINUOUS LAB EVALUATION – 3

**DATE:** 27-07-2026

## NAME OF EXPERIMENT

Timer-Based LED Pattern Generator and Button Interrupt Controller

## HARDWARE SETUP / PLATFORM

- 8051 Toolchain Setup
- AT89S52 Development Board
- Four LEDs
- One Push Button
- Digital Multimeter
- Board Schematics and 8051 Pin Diagram

##TASK

Design and implement a register-level GPIO controller using the AT89S52 microcontroller.

Configure four LEDs as digital outputs and one push button as a digital input using bare-metal embedded C and direct register access.

Develop a four-state LED control system in which each valid button press advances the system to the next operating mode.

Implement switch debouncing to ensure that one physical button press produces exactly one state transition.

## PROBLEM STATEMENT

Develop a basic user interface subsystem for an IoT sensor node consisting of:

- Four LEDs connected to four GPIO pins.
- One push button connected to a GPIO input.
- An AT89S52 microcontroller controlling the LED patterns.

The system must respond to button presses by changing the LED operating mode.

Initially, all LEDs remain OFF. Each valid button press advances the system through the following four operating modes.

## FUNCTIONAL REQUIREMENTS

### MODE 1: RUNNING LED PATTERN

**First Button Press**

The LEDs turn ON sequentially, one at a time.

| Step | LED1 | LED2 | LED3 | LED4 |
|---|---|---|---|---|
| 1 | 1 | 0 | 0 | 0 |
| 2 | 0 | 1 | 0 | 0 |
| 3 | 0 | 0 | 1 | 0 |
| 4 | 0 | 0 | 0 | 1 |

The sequence repeats continuously until the next valid button press.

### MODE 2: BINARY COUNTER

**Second Button Press**

The four LEDs represent a 4-bit binary counter from 0000 to 1111.

| Decimal | LED1 | LED2 | LED3 | LED4 |
|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 |
| 2 | 0 | 0 | 1 | 0 |
| 3 | 0 | 0 | 1 | 1 |
| ... | ... | ... | ... | ... |
| 15 | 1 | 1 | 1 | 1 |

The counter repeats until the next valid button press.

### MODE 3: ALTERNATING LED PATTERN

**Third Button Press**

The LEDs alternate between two patterns.

| Step | LED1 | LED2 | LED3 | LED4 |
|---|---|---|---|---|
| 1 | 1 | 0 | 1 | 0 |
| 2 | 0 | 1 | 0 | 1 |
| 3 | 1 | 0 | 1 | 0 |
| 4 | 0 | 1 | 0 | 1 |

The alternating pattern repeats until the next valid button press.

### MODE 4: ALL LED FLASHING

**Fourth Button Press**

All four LEDs blink simultaneously.

| Step | LED1 | LED2 | LED3 | LED4 |
|---|---|---|---|---|
| 1 | 1 | 1 | 1 | 1 |
| 2 | 0 | 0 | 0 | 0 |
| 3 | 1 | 1 | 1 | 1 |
| 4 | 0 | 0 | 0 | 0 |

The flashing pattern repeats until the next valid button press.

## TOPICS / CONSTRAINTS

- 8051 Toolchain Setup
- AT89S52 Development Board
- Timer-Based LED Pattern Generation
- Button Interrupt Control
- GPIO Input and Output Interfacing
- Register-Level Programming
- Switch Debouncing
- Four-State LED Control System

**Implementation Constraints:**

- Use only bare-metal embedded C.
- Use direct access to AT89S52 GPIO Special Function Registers (SFRs).
- Do not use Arduino APIs.
- Do not use HAL libraries.
- Do not use RTOS services.
- Ensure that one physical button press causes exactly one state transition.

## CORE LOGIC / PSEUDOCODE

1. Initialize the GPIO pins connected to the four LEDs and push button.
2. Set the initial state to Mode 0, with all LEDs OFF.
3. Configure the button input and detect valid button-press events.
4. Apply switch debouncing to prevent multiple state transitions caused by a single press.
5. When a valid button press is detected, advance the operating mode.
6. Execute the LED pattern corresponding to the selected mode:
   - Mode 1: Running LED pattern.
   - Mode 2: Binary counter from 0 to 15.
   - Mode 3: Alternating LED pattern.
   - Mode 4: All LEDs flashing.
7. Continue executing the selected LED pattern while monitoring for the next button press.
8. Repeat the four-mode sequence for subsequent valid button presses.

## SWITCH DEBOUNCING

Mechanical push buttons may generate multiple electrical transitions during a single physical press.

To prevent unintended mode changes:

1. Detect a button-press event.
2. Apply a short debounce interval.
3. Confirm that the button remains pressed.
4. Register only one valid press event.
5. Wait for the button to be released before accepting another press.

This ensures that one physical button press results in exactly one state transition.

## INFERENCE

The experiment demonstrates the implementation of a four-state LED control system using the AT89S52 microcontroller.

It provides practical understanding of register-level GPIO programming, digital input interfacing, LED pattern generation, timer-based control and button-event handling.

Switch debouncing improves the reliability of the user interface by preventing multiple mode transitions from a single physical button press.

The experiment illustrates how a simple push-button interface can control multiple operating modes in an embedded IoT sensor node without using Arduino APIs, HAL libraries or RTOS services.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
