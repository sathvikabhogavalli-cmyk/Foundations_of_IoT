# CONTINUOUS LAB EVALUATION – 2

**DATE:** 20-07-2026

## NAME OF EXPERIMENT

8051 Toolchain Setup, Hardware Bring-Up and Bare-Metal LED Interfacing Using AT89S52

## HARDWARE SETUP / PLATFORM

- 8051 Toolchain Setup
- AT89S52 Development Board
- Debugger / Programmer
- Digital Multimeter
- User LED
- Host Computer

##

### TASK 1: HARDWARE BOARD BRING-UP

Perform the initial hardware board bring-up by identifying and verifying the essential components of the AT89S52 development board.

**Activities to be performed:**

1. Identify the microcontroller present on the development board.
2. Identify the debugger/programmer and power source.
3. Identify the user LED and its corresponding GPIO pin.
4. Verify the board's power rails using a Digital Multimeter (DMM).
5. Identify the LED GPIO port and pin using the datasheet or board schematic.
6. Establish communication between the host computer and the target microcontroller.

### TASK 2: BARE-METAL LED BLINK

Develop a minimal bare-metal C program to control an LED by directly accessing the microcontroller's GPIO I/O registers.

**Activities to be performed:**

1. Configure the LED GPIO pin as an output using direct register access.
2. Write a delay mechanism using a simple software loop.
3. Toggle the LED between ON and OFF states.
4. Blink the LED at approximately 1 Hz.
5. Program the target device and verify the LED blinking operation.

### TASK 3: CUSTOM LIBRARY FUNCTION FOR DELAY

Develop a custom library function to provide delay functionality for the bare-metal embedded C program.

**Activities to be performed:**

1. Create a separate function for generating software delays.
2. Implement the delay using suitable software loops.
3. Reuse the custom delay function in the LED blinking program.
4. Verify the LED blinking operation using the developed delay function.

## TOPICS / CONSTRAINTS

- 8051 Toolchain Setup
- AT89S52 Development Board
- Hardware Board Bring-Up
- Direct Memory-Mapped GPIO I/O Register Access
- Bare-Metal Embedded C Programming
- Software-Based Delay Mechanism
- Custom Library Function Development

**Implementation Constraints:**

- Strictly use bare-metal embedded C programming.
- Do not use Arduino APIs.
- Do not use HAL libraries.
- Do not use RTOS services.
- Control the GPIO using direct microcontroller register access.

## CORE LOGIC / PSEUDOCODE

**1. Hardware Board Bring-Up**

- Identify the microcontroller, programmer, power source and user LED.
- Verify the power supply using a digital multimeter.
- Identify the GPIO port and pin connected to the LED.
- Establish communication between the host computer and target MCU.

**2. Bare-Metal LED Blinking**

- Initialize the LED GPIO pin.
- Configure the pin as an output using direct register access.
- Generate a software delay.
- Turn the LED ON.
- Wait for the specified delay.
- Turn the LED OFF.
- Wait again.
- Repeat continuously to achieve approximately 1 Hz blinking.

**3. Custom Delay Library**

- Develop a reusable delay function.
- Implement the required delay using software loops.
- Call the function whenever a delay is required in the LED blinking program.

## REQUIRED DELIVERABLES

1. Hardware Bring-Up Sheet with the identified board parameters.
2. Bare-Metal LED Blinking C Program.
3. Custom Delay Library Function.
4. Board Schematic and 8051 Pin Diagram.
5. Verification of LED blinking operation.

## INFERENCE

The experiment demonstrates the fundamentals of bare-metal embedded C programming using the AT89S52 microcontroller. It provides practical experience in hardware board bring-up, identifying GPIO pins, verifying power rails and establishing communication between the host computer and target microcontroller.

It also demonstrates direct GPIO register access for controlling an LED, implementing software-based delays and developing reusable custom library functions without depending on Arduino APIs, HAL libraries or RTOS services.

## CIRCUIT DIAGRAM
