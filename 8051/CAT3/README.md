# CONTINUOUS LAB EVALUATION – 3

**COURSE:** Fundamentals of Internet of Things + Lab  
**PLATFORM:** 8051 Microcontroller  
**MICROCONTROLLER:** 8051 (REG51-compatible)

## NAME OF EXPERIMENT

Multiple LED Pattern Generation and Push-Button-Based Mode Selection Using 8051

## AIM

To develop an Embedded C program for the 8051 microcontroller that controls four LEDs connected to Port 1 and switches between four LED patterns using a push button.

## HARDWARE SETUP / PLATFORM

- 8051 microcontroller development board
- Four LEDs
- Current-limiting resistors
- Push button or keypad switch
- Regulated power supply
- Keil µVision IDE
- 8051 programming environment

## TASK NO

**CAT3 – Four LED Patterns with Push-Button Mode Selection**

Implement four LED operating modes:

1. Running LED pattern
2. Four-bit binary counter
3. Alternating LED pattern
4. Simultaneous flashing of all LEDs

Use a push button to cycle through the four modes.

## PIN CONFIGURATION

| Component | 8051 Pin | Function |
|---|---|---|
| LED 1 | P1.0 | First LED output |
| LED 2 | P1.1 | Second LED output |
| LED 3 | P1.2 | Third LED output |
| LED 4 | P1.3 | Fourth LED output |
| Switch row | P2.7 | Driven LOW |
| Switch column | P2.3 | Active-LOW switch input |

The program drives P2.7 LOW and writes HIGH to P2.3 so that P2.3 can be read as an input. A button press is detected when P2.3 becomes LOW.

The physical LED illumination depends on whether the board uses active-HIGH or active-LOW LED connections.

## WORKING PRINCIPLE

The four LEDs are connected to the lower four bits of Port 1.

A variable named `mode` determines which LED pattern is executed. Initially, `mode = 0`.

The `switch(mode)` statement selects one of four functions.

### MODE 0 – RUNNING LED PATTERN

Function: `runningled()`

The program generates the following sequence at P1.3–P1.0:

| Step | Binary output |
|---|---|
| 1 | 0001 |
| 2 | 0010 |
| 3 | 0100 |
| 4 | 1000 |

Only one output bit is HIGH at a time, producing a running or chasing LED pattern for active-HIGH LEDs.

### MODE 1 – FOUR-BIT BINARY COUNTER

Function: `binarycounter()`

The lower four bits of Port 1 represent a binary count from 0 to 15.

The sequence begins at `0000` and continues through `0001`, `0010`, `0011`, and so on until `1111`.

The following statement updates only the lower four bits:

`P1 = (P1 & 0xF0) | (count & 0x0F);`

The upper four bits are preserved.

### MODE 2 – ALTERNATING LED PATTERN

Function: `alternatingpattern()`

The output alternates between:

- `0101`
- `1010`

For active-HIGH LEDs, this causes alternate pairs of LEDs to illuminate.

### MODE 3 – FLASHING ALL LEDs

Function: `flash()`

The output alternates between:

- `1111` – All four outputs HIGH
- `0000` – All four outputs LOW

This produces simultaneous flashing of all four LEDs.

## PUSH-BUTTON MODE SELECTION

The program checks the switch through `swicol`, which is mapped to P2.3.

When the input becomes LOW, the current LED pattern can terminate early.

After a pattern returns, the main loop checks the switch again. If the switch is still LOW, the mode is incremented.

The mode sequence is:

`0 → 1 → 2 → 3 → 0`

The program waits until the button is released before continuing.

## DELAY AND BUTTON MONITORING

The function `delay_and_check()` uses two nested loops, each iterating up to 300 times.

During these loops, the function repeatedly checks the button input.

- Returns `1` when the button is detected as pressed.
- Returns `0` when the delay completes without detecting a press.

Each LED pattern uses the return value to decide whether to stop early.

This allows button monitoring during the software delay rather than only between complete LED patterns.

**Note:** The program contains a debounce-related check, but it does not implement a guaranteed stable-time debounce interval. Reliable debounce behavior depends on the physical switch and timing.

## ALGORITHM

1. Start the program.
2. Configure P1.0–P1.3 for LED output control.
3. Drive P2.7 LOW and set P2.3 HIGH for switch input operation.
4. Clear the lower four bits of Port 1.
5. Initialize the operating mode to 0.
6. Enter an infinite loop.
7. Execute the LED pattern corresponding to the current mode.
8. Monitor the switch during software delays.
9. If the switch remains pressed when checked in the main loop, increment the mode.
10. Reset the mode to 0 after mode 3.
11. Wait for switch release.
12. Continue executing the selected pattern.

## SOURCE CODE

The experiment is implemented in Embedded C using `reg51.h`.

The main functions are:

- `delay_and_check()` – Software delay with button monitoring
- `runningled()` – Sequential LED pattern
- `binarycounter()` – Four-bit binary counter
- `alternatingpattern()` – Alternating LED outputs
- `flash()` – Simultaneous LED flashing
- `main()` – GPIO initialization, mode selection, and switch handling

The complete implementation is provided in the accompanying source file.

## EXPECTED OUTPUT

When the program starts, the running LED pattern is selected.

A recognized push-button press changes the mode to the next LED pattern.

The four modes cycle in the following order:

Running LEDs → Binary Counter → Alternating LEDs → Flashing LEDs → Running LEDs

The LED output pattern changes according to the selected mode.

## RESULT

The Embedded C program implements four different LED output patterns using the 8051 microcontroller.

It also provides push-button-based mode selection and monitors the switch during the software delay loops.

## INFERENCE

This experiment demonstrates GPIO output control, individual bit manipulation, Port 1 masking, conditional execution, and user-input-based mode selection on the 8051 microcontroller.

The implementation shows how a single push button can control multiple operating modes and how switch monitoring can be incorporated into software delays to improve responsiveness.

## CIRCUIT DIAGRAM

![Circuit Diagram](circuit.png)
