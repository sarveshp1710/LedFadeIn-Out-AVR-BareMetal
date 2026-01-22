<h1> Hi GitMates, </h1> 
here I am sharing my LED Fade in / Fade out AVR bare matal program. This is my first proper bare-metal program understanding how timers/counters works in register level without burdening CPU.
I also learnt to use Interrup Service Routine in this AVR MCU (Atmega328p). I learnt how actual Engineers handles MCU by digging Datasheets / User manuals of the MCUs. I am not going to stop with this, stay tunedd!!!

```
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int8_t i=1;
ISR(TIMER2_OVF_vect){ //interrupt service routine with vector of timer2 overflow
    if(OCR1A==0 && i==-1) //varying output compare register to vary duty cycle of fastpwm.
        i=1;
    else if(OCR1A==255 && i==1)
        i=-1;
    OCR1A+=i;
}

int main(){
    //timer 1 for generating pwm.
    DDRB |= (1<<PB1); //setting pb1 ie., d9 pin as output becoz it is the oc1A pin. for output, set it as output
    TCCR1A = (1<<COM1A1) | (1<<WGM10); //setting, clear output on compare output matched (means it sets to non-inverting mode and also it connects oca1 pin for pwm output) and wgm10 is set to 1 to set fastpwm 8 bit mode
    TCCR1B = (1<<WGM12) | (1<<CS12); //wgm12 is next reg for fastpwm 8 bit mode, cs12 is set to set prescaler as 256
    OCR1A=0; //initializing output compare register as 0, it keeps led dim, pwm thin.

    //timer 2 for varying output compare register
    TCCR2A = 0; //dont need any bit in this to set
    TCCR2B =(1<<CS21) | (1<<CS22); // setting prescaler to 256
    TIMSK2 = (1<<TOIE2); //enabling timer overflow interrupt
    sei(); //SREG |= (1<<I); // enabling global interrupt(all interrupt)
    for(;;){
        // no process in the loop
    }
    return 0;
}
```
---
The above code is ```ledFade.c``` file.

I also listed the registers which I used in this program.
<i>
TCCR1A
    COM1A1 = set
    COM1A0 = clear
    (non inverting mode, Fast PWM, 8-bit)
    WGM10 = set

TCCR1B
    WGM12 = set
    CS10 = set
    CS11 = set
    (f_clk/64)
    OCR1A = compare value(0-255)

DDRB
    PB1(OC1A) = set (OUTPUT)

Timer/Counter2 --> for OCR1A update
Normal mode
TCCR2A
    WGM21 = clear
    WGM20 = clear

TCCR2B
    WGM22 = clear
    CS21 = set
    CS22 = set (254 prescaler)

TIMSK2
    TOIE2 = set (interrupt enable)
SREG
    I = set (global interrupt enable)
</i>

Thank you see soon with another banger project !!!!!
