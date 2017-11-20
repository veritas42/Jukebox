/*
 * butten.c
 *
 * Created: 2017-11-20 오후 4:59:01
 *  Author: veritas
 */ 
#include <avr/interrupt.h>
#include "butten.h"

volatile unsigned char state = 0;
volatile unsigned char select = 0;
volatile unsigned char mode = 0;

void butten_init(void){
	sei();
	EIMSK |= (1 << INT0); 
	EICRA = (EICRA | (1 << ISC01) | (1 << ISC11) | (1 << ISC21) | (1 << ISC31)) & ~((1 << ISC00) | (1 << ISC10) | (1 << ISC20) | (1 << ISC30));
}

ISR(INT0_vect){
	state = 1 - state;
}

ISR(INT1_vect){
	select = select >= 0 ? select - 1 : select;
}

ISR(INT2_vect){
	select = select < MAXSELECT ? select + 1 : select;
}

ISR(INT3_vect){
	mode = (mode + 1) % MODENUM;
}

unsigned char state(void){
	return state;	
}

unsigned char select(void){
	return select;
}

unsigned char mode(void){
	return mode;
}