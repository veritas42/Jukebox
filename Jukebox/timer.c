
#include <avr/common.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect){
	TCNT0 = 0x83;
	delay = delay ? delay - 1 : delay;
}

void timer_init(void){
	TIMSK |= (1 << TOIE0);
	TCCR0 = 0x05;
	TCNT0 = 0x83;
}

void delay_ms(int val){
	delay = val;
	while(delay!=0);
}