CONTINUOUS LAB EVALUATION – 5
DATE: 10-08-2026
COURSE: 25CS2741 – Fundamentals of Internet of Things + Lab
NAME OF EXPERIMENT
Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control
HARDWARE SETUP / PLATFORM
- 8051 toolchain setup
- AT89S52 development board
- Board schematics and 8051 pin diagram
- Digital multimeter for hardware debugging
- Oscilloscope for timing and signal verification
TASK NO
Design a timer-driven embedded control system using the 8051 in which a hardware timer periodically generates interrupts. Use the timer interrupt as the system time base to control LED brightness, generate variable-frequency pulse signals, and control the stepping sequence of a stepper motor.

Constraints: Bare-metal embedded C and register-level control only. No Arduino APIs, HAL libraries, RTOS services, or software delay loops for timing. The implementation must be non-blocking.
TASK 1: HARDWARE TIMER AND INTERRUPT-BASED LED CONTROL
Configure Timer 0 to generate a precise periodic interrupt. Use the interrupt to establish a software time base and toggle an LED every 1 second. Verify the timing using an oscilloscope.

Timing flow: 11.0592 MHz crystal → machine cycle → timer counter → overflow → interrupt → software time base → 1-second LED control.

For a classic 12-clock 8051:
- Machine-cycle duration = 12 / 11.0592 MHz ≈ 1.085 μs
- Timer counts for approximately 1 ms = 1 ms / 1.085 μs ≈ 922
- 16-bit Timer 0 preload = 65536 − 922 = 64614 = 0xFC66
- TH0 = 0xFC, TL0 = 0x66
These are the example values in the evaluation sheet; precise timing must be verified experimentally.
TASK 2: SOFTWARE PWM AND VARIABLE-FREQUENCY SIGNAL GENERATION
A. LED fading using software PWM

Use the timer interrupt from Task 1 to generate software PWM. Increase the duty cycle gradually from 0% to 100%, then decrease it back to 0%, producing a visible fading effect.
- Suggested PWM frequency: 500 Hz–1 kHz
- LED should appear continuously illuminated without visible flicker.
Duty cycle	LED brightness
0%	OFF
25%	Dim
50%	Medium
75%	Bright
100%	Fully ON


B. Variable-frequency square-wave generation

Configure a GPIO pin as a signal output and generate square waves using timer interrupts. Measure output frequency and duty cycle using an oscilloscope.
Mode	Frequency
1	100 Hz
2	500 Hz
3	1 kHz
4	2 kHz
5	5 kHz


C. Different signal types
- Square wave: 101010101010
- Variable duty-cycle wave: 1111000011110000
- Pulse train: short HIGH pulses separated by longer LOW intervals
- Burst signal: a group of pulses followed by an inactive interval
TASK 3: STEPPER MOTOR SPEED AND DIRECTION CONTROL (OPTIONAL)
Use timer interrupts to generate the next step in a four-output sequence:

1000 → 0100 → 0010 → 0001

The timer interval determines the stepping speed:
Speed	Interval
Slow	100 ms/step
Medium	50 ms/step
Fast	10 ms/step


Reverse the stepping order to reverse the motor direction.
CORE LOGIC / PSEUDOCODE
1. Configure the required GPIO outputs and Timer 0 using direct register access.
2. Enable the timer interrupt and establish a software time base.
3. On timer events, update the LED output to achieve a one-second toggle interval.
4. Use timer-driven updates to vary the PWM duty cycle for LED fading.
5. Generate the selected square-wave frequency and other requested signal patterns using timer-driven output transitions.
6. If implementing the optional motor task, advance or reverse the step sequence according to the selected step interval.
7. Keep the main program non-blocking; do not use software delay loops for timing.
INFERENCE
This evaluation demonstrates timer-driven control on the AT89S52 using register-level embedded C. Hardware timer interrupts provide a software time base for LED toggling, PWM-based fading, and pulse generation without blocking delay loops. The optional stepper motor task applies timer-driven events to speed and direction control.
CIRCUIT DIAGRAM
<img width="1491" height="1055" alt="AT89S52 LED Control on P1 7" src="https://github.com/user-attachments/assets/d8e1301d-a64e-4604-b123-990ac0d16eb4" />
