# CONTINUOUS LAB EVALUATION – 5

**DATE:** 10-08-2026

## NAME OF EXPERIMENT

Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation and Stepper Motor Control

## HARDWARE SETUP / PLATFORM

- 8051 Toolchain Setup
- AT89S52 Development Board
- 11.0592 MHz Crystal Oscillator
- LEDs and GPIO Output Pins
- Digital Multimeter
- Oscilloscope
- Board Schematics and 8051 Pin Diagram
- Stepper Motor (Optional)

## TASK NO

Design and implement a timer-driven embedded control system using the AT89S52 microcontroller, in which a hardware timer periodically generates interrupts.

Use the timer interrupt as the system time base to control LED brightness, generate variable-frequency pulse signals and control the stepping sequence of a stepper motor.

The implementation must be non-blocking and must not use software delay loops for timing.

## TASK 1: HARDWARE TIMER AND INTERRUPT-BASED LED CONTROL

Configure Timer 0 to generate a precise periodic interrupt.

**Activities to be performed:**

1. Configure Timer 0 in 16-bit mode.
2. Generate a periodic timer interrupt.
3. Use the timer interrupt to create a software time base.
4. Toggle an LED every one second.
5. Verify the generated timing using an oscilloscope.

### TIMER CALCULATION

For a classic 12-clock 8051 with an 11.0592 MHz crystal:

**Machine Cycle Time:**

T_machine = 12 / 11.0592 MHz

T_machine ≈ 1.085 µs

For a 1 ms timer interrupt:

N = 1 ms / 1.085 µs ≈ 922

Timer Preload = 65536 − 922 = 64614

Timer Preload = 0xFC66

Therefore:

```c
TH0 = 0xFC;
TL0 = 0x66;
```

### TIMER-BASED CONTROL FLOW

Crystal (11.0592 MHz) → Machine Cycle → Timer Counter → Overflow → Interrupt → Software Time Base → 1-Second LED Control

**Key Principle:** Hardware generates the timing, and software responds to the timing event.

## TASK 2: LED FADING USING SOFTWARE PWM AND VARIABLE-FREQUENCY SQUARE-WAVE GENERATION

### PART A: LED FADING USING SOFTWARE PWM

Using the timer interrupt developed in Task 1, generate a software PWM signal.

**Activities to be performed:**

1. Generate a PWM signal using timer interrupts.
2. Gradually increase the duty cycle from 0% to 100%.
3. Gradually decrease the duty cycle from 100% to 0%.
4. Repeat the sequence to produce a visible LED fading effect.
5. Maintain a suggested PWM frequency of approximately 500 Hz to 1 kHz.

### DUTY CYCLE AND LED BRIGHTNESS

| Duty Cycle | LED Brightness |
|---|---|
| 0% | OFF |
| 25% | Dim |
| 50% | Medium |
| 75% | Bright |
| 100% | Fully ON |

The LED should appear continuously illuminated rather than visibly flickering.

### PART B: VARIABLE-FREQUENCY SQUARE-WAVE GENERATION

Configure a GPIO pin as a signal output and use timer interrupts to generate square-wave signals of different frequencies.

| Mode | Output Frequency |
|---|---|
| Mode 1 | 100 Hz |
| Mode 2 | 500 Hz |
| Mode 3 | 1 kHz |
| Mode 4 | 2 kHz |
| Mode 5 | 5 kHz |

Measure the output frequency and duty cycle using an oscilloscope.

### DIFFERENT SIGNAL TYPES

**1. Square Wave**

Generate a periodic signal alternating between HIGH and LOW states.

Example: `101010101010`

**2. Variable Duty-Cycle Wave**

Generate a waveform with adjustable HIGH and LOW durations.

Example: `1111000011110000`

**3. Pulse Train**

Generate narrow pulses separated by longer LOW intervals.

Example: `100000001000000010000000`

**4. Burst Signal**

Generate groups of pulses separated by inactive intervals.

Example: `1010101010 0000000000 1010101010`

## TASK 3: STEPPER MOTOR SPEED AND DIRECTION CONTROL (OPTIONAL)

Use timer interrupts to control the stepping sequence of a stepper motor.

**Activities to be performed:**

1. Generate the stepping sequence using timer interrupts.
2. Advance to the next step based on the timer interval.
3. Control the motor speed by changing the interval between steps.
4. Control the motor direction by changing the stepping sequence.

### STEPPER MOTOR SEQUENCE

| Step | Output Pattern |
|---|---|
| 1 | 1000 |
| 2 | 0100 |
| 3 | 0010 |
| 4 | 0001 |

### STEPPER MOTOR SPEED CONTROL

| Speed | Timer Interval |
|---|---|
| Slow | 100 ms/step |
| Medium | 50 ms/step |
| Fast | 10 ms/step |

The timer interval determines the motor speed.

## TOPICS / CONSTRAINTS

- 8051 Toolchain Setup
- AT89S52 Development Board
- Bare-Metal Embedded C Programming
- Direct Register-Level Programming
- Hardware Timer Configuration
- Timer Interrupt Handling
- Software Time Base
- LED Fading Using PWM
- Variable-Frequency Square-Wave Generation
- Stepper Motor Control (Optional)

**Implementation Constraints:**

- Strictly use bare-metal embedded C programming.
- Do not use Arduino APIs.
- Do not use HAL libraries.
- Do not use RTOS services.
- Do not use software delay loops for timing.
- Use hardware timer interrupts for timing operations.
- Ensure non-blocking implementation.

## CORE LOGIC / PSEUDOCODE

1. Initialize the required GPIO pins.
2. Configure Timer 0 using direct register access.
3. Enable the Timer 0 interrupt.
4. Generate periodic interrupts using the hardware timer.
5. Maintain a software time base using the timer interrupt.
6. Toggle the LED every one second.
7. Generate software PWM by varying the duty cycle from 0% to 100% and back to 0%.
8. Generate square-wave signals at the specified frequencies.
9. Generate square waves, variable duty-cycle waves, pulse trains and burst signals.
10. For the optional stepper motor task, generate the stepping sequence and control the motor speed using timer intervals.
11. Continue execution without blocking software delay loops.

## INFERENCE

The experiment demonstrates hardware timer and interrupt-based timing using the AT89S52 microcontroller.

It provides an understanding of timer configuration, interrupt handling, software time-base generation, LED brightness control using PWM and variable-frequency signal generation.

The experiment also demonstrates how hardware timers can support non-blocking embedded applications without relying on software delay loops.

The optional stepper motor task extends timer-based control to motor speed and stepping sequence management.

## CIRCUIT DIAGRAM


<img width="1491" height="1055" alt="AT89S52 LED Control on P1 7" src="https://github.com/user-attachments/assets/d8e1301d-a64e-4604-b123-990ac0d16eb4" />
