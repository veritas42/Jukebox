/*
 * CFile1.c
 *
 * Created: 2017-11-20 오후 1:48:36
 *  Author: veritas
 */ 

#include <avr/common.h>
#include <avr/interrupt.h>
#include <math.h>
#include "sound.h"

volatile unsigned int bpm = 60;

extern void delay_ms(int);

void ctc1_init(void){
	//set ctc mode
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);
	
	//set prescaler
	TCCR1B &= ~(1 << CS10);
	TCCR1B |= (1 << CS11);
	TCCR1B &= ~(1 << CS12);
}

void tone(double hz, int s_time){
	ICR1 = (unsigned int)((2000000 / hz + 0.5)/2);			//set cycle
	TCCR1A &= ~(1 << COM1B1);
	TCCR1A |= (1 << COM1B0);
	delay_ms(s_time);
	TCCR1A &= ~(1 << COM1B1);
	TCCR1A &= ~(1 << COM1B0);
}

void tone_oct(char oct[], double meter){
	int s_time = (int)(meter * 60000 / bpm);
	if(oct[1] == 'H'){
		delay_ms(s_time);
	}
	else if(oct[1] == 'A'){
		if(oct[2] == 'w'){
			tone((55 * pow(2 , (oct[0] - 0x30) - 1)), s_time);
		}
		else if(oct[2] == 'h'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)1/12)), s_time);
		}
	}
	else if (oct[1] == 'B'){
		tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)2/12)), s_time);
	}
	else if (oct[1] == 'C'){
		if(oct[2] == 'w'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)3/12)), s_time);
		}
		else if(oct[2] == 'h'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)4/12)), s_time);
		}
	}
	else if (oct[1] == 'D'){
		if(oct[2] == 'w'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)5/12)), s_time);
		}
		else if(oct[2] == 'h'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)6/12)), s_time);
		}
	}
	else if (oct[1] == 'E'){
		tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)7/12)), s_time);
	}
	else if (oct[1] == 'F'){
		if(oct[2] == 'w'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)8/12)), s_time);
		}
		else if(oct[2] == 'h'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)9/12)), s_time);
		}
	}
	else if (oct[1] == 'G'){
		if(oct[2] == 'w'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)10/12)), s_time);
		}
		else if(oct[2] == 'h'){
			tone((55 * pow(2 , ((oct[0] - 0x30) - 1) + (double)11/12)), s_time);
		}
	}
}