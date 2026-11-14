# CONTINUOUS LAB EVALUATION – 2

**COURSE:** Fundamentals of Internet of Things + Lab  
**PLATFORM:** 8051 Microcontroller  
**MICROCONTROLLER:** 8051 (REG51-compatible)

## NAME OF EXPERIMENT

LED Blinking Using GPIO and Software Delay in 8051 Microcontroller

## AIM

To write and execute an Embedded C program to blink an LED continuously using Port 1, Pin 0 (P1.0) of the 8051 microcontroller with a software-generated delay.

## HARDWARE SETUP / PLATFORM

- 8051 microcontroller development board
- LED
- Current-limiting resistor
- Regulated power supply
- Keil µVision IDE
- 8051 programming/debugging environment

## TASK NO

**CAT2 – LED Blinking Using Software Delay**

Configure P1.0 as a digital output and repeatedly switch its logic state between HIGH and LOW with a software delay between transitions.

## PIN CONFIGURATION

| Component | 8051 Pin | Function |
|---|---|---|
| LED | P1.0 | Digital output |
| Power supply | VCC | Microcontroller power |
| Ground | GND | Common reference |

**Note:** The LED's physical ON/OFF state depends on whether it is wired as active-high or active-low.

## WORKING PRINCIPLE

The 8051 microcontroller controls the LED through GPIO pin P1.0.

The program defines `ledpin` using the `sbit` keyword to access the individual port bit.

A `delay()` function introduces a time interval using two nested `for` loops.

Inside the infinite `while(1)` loop:

1. P1.0 is set to logic HIGH.
2. The software delay is executed.
3. P1.0 is set to logic LOW.
4. The software delay is executed again.
5. The sequence repeats continuously.

This produces a periodic digital signal at P1.0, causing the LED to blink.

## ALGORITHM

1. Start the program.
2. Declare P1.0 as the LED control pin.
3. Define the software delay function.
4. Enter an infinite loop.
5. Set P1.0 to HIGH.
6. Call the delay function.
7. Set P1.0 to LOW.
8. Call the delay function.
9. Repeat steps 5–8 continuously.

## SOURCE CODE

```c
#include <stdio.h>
#include <reg51.h>

sbit ledpin = P1^0;

void delay()
{
    int i, j;

    for(i = 0; i < 500; i++)
    {
        for(j = 0; j < 500; j++)
        {
        }
    }
}

void main()
{
    while(1)
    {
        ledpin = 1;
        delay();

        ledpin = 0;
        delay();
    }
}
```

## EXPECTED OUTPUT

The LED connected to P1.0 blinks continuously with a delay between successive logic transitions.

The blinking speed depends on the microcontroller clock frequency, compiler optimization, and software delay execution time.

## RESULT

The Embedded C program implements continuous GPIO toggling at P1.0 using a software delay routine.

## INFERENCE

This experiment demonstrates basic digital output control using the 8051 microcontroller. It illustrates how the `sbit` keyword provides access to individual GPIO pins and how nested software loops can introduce delays between output transitions.

Software delays are simple to implement but are blocking and are not suitable for applications requiring precise timing or simultaneous tasks.

## CIRCUIT DIAGRAM

<img width="1752" height="897" alt="a9452275-22c1-4eab-873b-5ba74e7aec2b" src="https://github.com/user-attachments/assets/bf0b4d2b-1c53-4159-8964-d3fd61e49126" />
