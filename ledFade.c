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
