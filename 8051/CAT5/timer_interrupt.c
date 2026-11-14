#include <reg52.h>

sbit LED = P1^7;                 /* change pin to match your board */

unsigned int ms_count = 0;

void Timer0_ISR(void) interrupt 1
{
    /* reload for next 1 ms */
    TR0 = 0;
    TH0 = 0xFC;
    TL0 = 0x66;
    TR0 = 1;

    ms_count++;
    if (ms_count >= 1000)        /* 1000 x 1 ms = 1 s */
    {
        ms_count = 0;
        LED = ~LED;              /* toggle LED */
    }
}

void main(void)
{
    LED = 0;

    TMOD = (TMOD & 0xF0) | 0x01; /* Timer0, Mode 1 (16-bit) */
    TH0  = 0xFC;
    TL0  = 0x66;

    ET0 = 1;                     /* enable Timer0 interrupt */
    EA  = 1;                     /* global interrupt enable */
    TR0 = 1;                     /* start Timer0            */

    while (1)
    {
        /* CPU is free. Timing is done 100% by hardware timer. */
    }
}