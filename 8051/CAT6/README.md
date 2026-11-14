# CONTINUOUS LAB EVALUATION – 6

**COURSE:** Fundamentals of Internet of Things + Lab  
**PLATFORM:** 8051 Microcontroller  
**MICROCONTROLLER:** 8051/8052-compatible microcontroller (`reg52.h`)

## NAME OF EXPERIMENT

UART Serial Communication Using Polling, Interrupts, and Circular Buffer in 8051 Microcontroller

## AIM

To implement UART serial communication using the 8051 microcontroller by:

1. Transmitting a predefined string repeatedly using polling.
2. Receiving and echoing serial characters using UART interrupts and a circular receive buffer.

## HARDWARE SETUP / PLATFORM

- 8051/8052-compatible microcontroller development board
- 11.0592 MHz crystal oscillator
- USB-to-UART adapter or compatible serial interface
- Computer with serial terminal software
- Regulated power supply
- Keil µVision IDE
- Embedded C programming environment

## TASK NO

**CAT6 – UART SERIAL COMMUNICATION**

### TASK A – INTERRUPT-DRIVEN UART ECHO WITH CIRCULAR BUFFER

The first program implements UART reception using serial interrupts and a circular buffer.

### TASK B – UART STRING TRANSMISSION USING POLLING

The second program transmits the string `Hello from 8051` repeatedly using polling-based UART transmission.

These are independent programs and should be compiled and executed separately.

## PIN CONFIGURATION

| Component | 8051 Pin | Function |
|---|---|---|
| UART RXD | P3.0 | Serial receive input |
| UART TXD | P3.1 | Serial transmit output |
| Timer1 | Internal peripheral | UART baud-rate generation |
| VCC | Power | Microcontroller supply |
| GND | Ground | Common reference |

For connection to a USB-to-UART adapter:

- 8051 TXD connects to adapter RXD.
- 8051 RXD connects to adapter TXD.
- Both devices share a common ground.

Use compatible logic-voltage levels. A direct TTL-level UART connection is not the same as an RS-232 voltage-level connection.

## COMMON UART CONFIGURATION

Both programs use the following UART settings:

| Parameter | Configuration |
|---|---|
| UART mode | Mode 1 |
| Data bits | 8 |
| Stop bits | 1 |
| Parity | None |
| Baud rate | 9600 bps |
| Baud-rate generator | Timer1 |
| Timer1 mode | Mode 2, 8-bit auto-reload |
| TH1 | 0xFD |
| TL1 | 0xFD |
| SMOD | 0 |
| Receive enable | REN = 1 |

### UART Initialization

`SCON = 0x50;`

Configures UART Mode 1 and enables reception.

`PCON &= 0x7F;`

Clears SMOD to disable baud-rate doubling.

`TMOD &= 0x0F;`

Clears the Timer1 configuration bits while preserving the Timer0 configuration.

`TMOD |= 0x20;`

Configures Timer1 in Mode 2.

`TH1 = 0xFD;`

Sets the Timer1 reload value for 9600 baud with an 11.0592 MHz oscillator on a conventional 12-clock 8051.

`TR1 = 1;`

Starts Timer1.

## TASK A – INTERRUPT-DRIVEN UART ECHO

### OBJECTIVE

To receive serial characters through UART interrupts, store them in a circular buffer, and transmit the received characters back to the sender.

### WORKING PRINCIPLE

The program initializes UART communication and enables serial interrupts.

The statement:

`ES = 1;`

Enables the serial interrupt.

The statement:

`EA = 1;`

Enables global interrupts.

The serial interrupt service routine is declared as:

`void uart_isr(void) interrupt 4`

The ISR handles both reception and transmission-complete events.

### CIRCULAR RECEIVE BUFFER

The program declares:

`#define RX_SIZE 16`

`#define RX_MASK (RX_SIZE - 1)`

The receive buffer is:

`static unsigned char rx_buf[RX_SIZE];`

Two indices track the buffer:

- `rx_head` – Position where the next received character is stored.
- `rx_tail` – Position from which the next character is read.

The next buffer index is calculated using:

`next = (rx_head + 1) & RX_MASK;`

This provides circular indexing because the buffer size is a power of two.

The implementation reserves one slot to distinguish a full buffer from an empty buffer. Therefore, the maximum usable capacity is 15 bytes.

If the buffer is full, the newly received character is read from `SBUF` and discarded.

### UART RECEIVE INTERRUPT

When a character is received:

1. The RI flag becomes set.
2. The serial interrupt service routine executes.
3. The RI flag is cleared.
4. The next buffer position is calculated.
5. If space is available, the received character is stored.
6. The buffer head index is updated.

### UART TRANSMISSION

The `uart_tx()` function waits until the previous transmission is complete.

It then clears `tx_done` and writes the next character to `SBUF`.

When transmission completes, the TI flag triggers serial interrupt handling.

The ISR clears TI and sets:

`tx_done = 1;`

This indicates that another character can be transmitted.

### UART ECHO OPERATION

After initialization, the program transmits:

`UART Echo Ready`

The main loop checks whether received data is available.

If a character is present, the program reads it from the circular buffer and transmits it back.

If the received character is carriage return (`'\r'`), the program transmits carriage return followed by line feed (`'\n'`).

Otherwise, the received character is echoed unchanged.

### TASK A ALGORITHM

1. Initialize UART Mode 1.
2. Configure Timer1 Mode 2 for baud-rate generation.
3. Enable serial and global interrupts.
4. Initialize the circular receive buffer.
5. Transmit the startup message.
6. Wait for incoming serial data.
7. On reception, execute the UART ISR.
8. Store the received character in the circular buffer if space is available.
9. Check for buffered data in the main loop.
10. Retrieve the received character.
11. Echo the character through UART.
12. Convert carriage return into carriage return and line feed.
13. Repeat continuously.

### TASK A EXPECTED OUTPUT

Serial terminal:

```text
UART Echo Ready
Hello
123
8051
```

The user types the characters after the startup message. The program echoes the received characters.

### TASK A RESULT

The program implements interrupt-driven UART reception with a circular receive buffer and serial echo functionality.

## TASK B – UART STRING TRANSMISSION USING POLLING

### OBJECTIVE

To configure the 8051 UART and repeatedly transmit a predefined text string using polling-based serial communication.

### WORKING PRINCIPLE

The program initializes UART Mode 1 and configures Timer1 in Mode 2.

The `uart_tx()` function sends one character by writing it to the serial buffer register:

`SBUF = c;`

The program then waits for the transmit interrupt flag:

`while (TI == 0);`

When transmission completes, TI becomes set.

The program clears TI in software:

`TI = 0;`

The `uart_puts()` function transmits each character of a null-terminated string by repeatedly calling `uart_tx()`.

### MAIN PROGRAM

After UART initialization, the main program repeatedly transmits:

`Hello from 8051\r\n`

The `\r\n` characters provide carriage return and line feed.

Because transmission occurs inside an infinite loop, the message repeats continuously without an additional delay.

### TASK B ALGORITHM

1. Start the program.
2. Configure UART Mode 1.
3. Configure Timer1 Mode 2.
4. Load `TH1 = 0xFD` and `TL1 = 0xFD`.
5. Start Timer1.
6. Enter an infinite loop.
7. Pass the predefined string to `uart_puts()`.
8. Transmit one character through `SBUF`.
9. Wait until TI becomes set.
10. Clear TI.
11. Repeat until all characters are transmitted.
12. Restart the string transmission.

### TASK B EXPECTED OUTPUT

```text
Hello from 8051
Hello from 8051
Hello from 8051
Hello from 8051
...
```

The message repeats continuously on the serial terminal.

### TASK B RESULT

The program implements continuous UART string transmission using polling and Timer1-based baud-rate generation.

## COMPARISON OF TASK A AND TASK B

| Feature | Task A | Task B |
|---|---|---|
| Communication | Receive and echo | Transmit only |
| Reception handling | Interrupt-driven | Not used |
| Transmission handling | Interrupt completion flag | Polling TI flag |
| Circular buffer | Yes | No |
| UART baud rate | 9600 | 9600 |
| Main functionality | Echo received characters | Repeated text output |

## OVERALL RESULT

Both programs demonstrate UART serial communication using the 8051 microcontroller.

Task A implements interrupt-driven reception, buffered data handling, and character echo.

Task B implements polling-based transmission of a predefined string.

## INFERENCE

This experiment demonstrates the operation of the 8051 UART peripheral, Timer1-based baud-rate generation, serial transmit and receive registers, interrupt flags, and circular buffering.

Polling provides a straightforward method for serial transmission but requires the processor to wait for completion.

Interrupt-driven reception allows received data to be collected independently of the main program's execution, while circular buffering helps manage incoming characters.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
