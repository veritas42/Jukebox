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

void butten_init(void){
	sei();
	EIMSK |= (1 << INT0) | (1 << INT1); 
	EICRA =0x0a;
	//EICRA = (EICRA | ((1 << ISC01) | (1 << ISC11) | (1 << ISC21))) & ~((1 << ISC00) | (1 << ISC10) | (1 << ISC20));
}

ISR(INT0_vect){
	state = 1;
}

ISR(INT1_vect){
	select += 1;
	select %= MAXSELECT;
}

