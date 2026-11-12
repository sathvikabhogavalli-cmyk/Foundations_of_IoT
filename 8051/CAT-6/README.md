# CONTINUOUS LAB EVALUATION – 6

**DATE:** 17-08-2026

## NAME OF EXPERIMENT

UART Driver and Serial Debugging

## HARDWARE SETUP / PLATFORM

- 8051 Toolchain Setup
- AT89S52 Development Board
- USB-to-TTL Serial Converter
- Host Computer / PC
- PuTTY Serial Terminal
- Digital Multimeter
- Board Schematics and 8051 Pin Diagram

## TASK NO

Develop a basic interrupt-driven UART driver for the AT89S52 microcontroller to transmit and receive characters through a PC terminal using a USB-to-TTL serial interface.

Configure UART for 9600-8-N-1 communication and demonstrate character transmission and reception using PuTTY.

Implement UART transmit and receive functions, followed by an interrupt-driven RX ring buffer.

## TASK A: UART INITIALIZATION AND CHARACTER TRANSMISSION

Configure the 8051 UART with the following parameters:

| Parameter | Configuration |
|---|---|
| UART Mode | 8-bit UART |
| Operation | Asynchronous |
| Baud Rate | 9600 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |

**Activities to be performed:**

1. Identify the UART transmission and reception pins of the AT89S52.
2. Configure the UART operating mode using direct register access.
3. Configure the baud-rate generation mechanism.
4. Initialize UART for 9600-8-N-1 communication.
5. Establish serial communication between the AT89S52 development board and the PC using a USB-to-TTL converter.
6. Transmit the message `Hello from 8051` continuously to the PuTTY terminal.
7. Verify the transmitted characters on the PC terminal.

### COMMUNICATION FLOW

8051 Development Board → TX → USB-to-TTL Converter → PC → PuTTY

### EXPECTED OUTPUT

```text
Hello from 8051
Hello from 8051
Hello from 8051
```

## TASK B: UART ECHO

Develop an interactive UART communication application.

Whenever a character is entered in the PuTTY terminal, the AT89S52 must receive the character and transmit the same character back to the PC.

**Activities to be performed:**

1. Configure UART reception.
2. Receive a character from the PuTTY terminal.
3. Detect the reception of the character using the UART receive indication.
4. Read the received character from the serial data register.
5. Transmit the same character back to the PC.
6. Repeat the process continuously.

### COMMUNICATION FLOW

PC → 8051 → PC

### EXAMPLE

**Input entered in PuTTY:**

```text
ABC123
```

**Expected output:**

```text
ABC123
```

## UART DRIVER DEVELOPMENT STAGES

### STAGE 1: IDENTIFY UART PINS

- Identify the TXD and RXD pins of the AT89S52.
- Understand their alternate peripheral functions for serial communication.

### STAGE 2: UART CONFIGURATION REGISTER

- Identify the register used to select the serial operating mode.
- Understand the bits responsible for selecting the UART mode.
- Configure 8-bit asynchronous communication with variable baud rate.
- Enable UART reception.

### STAGE 3: TRANSMIT REGISTER

- Identify the serial data register used for transmitting characters.
- Understand how data is written for transmission and accessed during reception.

### STAGE 4: TRANSMISSION COMPLETION

- Identify the flag indicating completion of character transmission.
- Monitor the transmission-complete indication.
- Handle the flag before transmitting subsequent characters.

### STAGE 5: BAUD-RATE GENERATION

- Identify the timer peripheral used for UART baud-rate generation.
- Configure the required timer operating mode.
- Generate the timing required for serial communication.

### STAGE 6: CONFIGURE 9600 BAUD

- Identify the crystal frequency of the development board.
- Refer to the 8051 Timer 1 baud-rate equation.
- Determine the timer reload value required for 9600 baud.
- Configure the baud-rate generator accordingly.

### STAGE 7: UART INITIALIZATION

Develop the UART initialization function:

```c
void uart_init(void);
```

Configure the UART for 9600-8-N-1 communication.

### STAGE 8: UART VERIFICATION

Verify the UART configuration by transmitting a known character to the PC terminal.

### STAGE 9: UART CHARACTER RECEPTION

- Detect the arrival of a character from the PC.
- Identify the UART reception flag.
- Read the received character from the serial data register.
- Store the received character in a suitable variable.

### STAGE 10: PuTTY ECHO EXPERIMENT

Develop an application that continuously receives characters from PuTTY and immediately transmits the same characters back.

**Test Input:**

```text
Hello 8051
```

**Expected Output:**

```text
Hello 8051
```

## TOPICS / CONSTRAINTS

- 8051 Toolchain Setup
- AT89S52 Development Board
- Bare-Metal Embedded C Programming
- UART Serial Communication
- UART Configuration Registers
- Baud-Rate Generation
- Timer 1 Configuration
- Character Transmission and Reception
- UART Interrupt Handling
- Interrupt-Driven RX Ring Buffer
- Serial Debugging Using PuTTY

**Implementation Constraints:**

- Strictly use bare-metal embedded C programming.
- Do not use Arduino APIs.
- Do not use HAL libraries.
- Do not use RTOS services.
- Configure UART using direct microcontroller register access.
- Use a USB-to-TTL serial interface for PC communication.
- Maintain 9600-8-N-1 UART communication.

## CORE LOGIC / PSEUDOCODE

**1. UART Initialization**

1. Identify the UART TXD and RXD pins.
2. Configure the UART operating mode.
3. Configure the baud-rate generation timer.
4. Set the required baud rate to 9600.
5. Enable UART reception.
6. Enable the required UART interrupt for interrupt-driven operation.

**2. Character Transmission**

1. Initialize UART communication.
2. Load the character into the serial data register.
3. Wait for or handle the transmission-complete indication.
4. Clear the transmission-complete flag as required.
5. Continue transmitting the message `Hello from 8051`.

**3. Character Reception and Echo**

1. Initialize UART communication.
2. Detect the arrival of a character from the PC.
3. Read the received character.
4. Transmit the same character back to the PC.
5. Repeat continuously.

**4. Interrupt-Driven RX Ring Buffer**

1. Configure UART reception interrupts.
2. When a character is received, handle the UART interrupt.
3. Read the received character from the serial data register.
4. Store the character in the RX ring buffer.
5. Make the buffered character available to the main application for processing.

## INFERENCE

The experiment demonstrates UART serial communication and debugging using the AT89S52 microcontroller.

It provides an understanding of UART initialization, baud-rate configuration, character transmission, character reception and serial communication between an 8051 development board and a PC using a USB-to-TTL converter.

The UART echo application demonstrates bidirectional communication by receiving characters from PuTTY and transmitting the same characters back.

The experiment also introduces interrupt-driven UART reception and RX ring-buffer handling for embedded serial communication applications without using Arduino APIs, HAL libraries or RTOS services.

## CIRCUIT DIAGRAM
<img width="3508" height="2481" alt="circuit" src="https://github.com/user-attachments/assets/dd1e5655-81cc-4ca5-910e-ad2f73f9677d" />

<img width="3508" height="2481" alt="circuit" src="https://github.com/user-attachments/assets/66df96fd-46b7-453d-b0b3-6aff44e77931" />
