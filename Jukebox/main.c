/*
 * Jukebox.c
 *
 * Created: 2017-11-13 오후 1:51:36
 * Author : veritas
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>
#include <math.h>
#include "lcd.h"
#include "timer.h"
#include "sound.h"
#include "butten.h"

void korobeiniki();

int main(void)
{
	sei();
	timer_init();
	ctc1_init();
	LCD_init();
	butten_init();
	//DDRA = 0xff;
	//DDRB = 0xff;
	//KEY_DIR = 0x0f;
	//KEY_PORT = 0xff;
		
	//DDRC = 0xff;
	//PORTC = 0x0f;
	LCD_init();
	LCD_pos(0, 0);
	LCD_string("jukebox1");
	LCD_pos(0, 1);
	korobeiniki();
	while (1)
	{
		if(mode() == 0){
			
		}
	}
}


void korobeiniki(void){
	bpm = 400;
	tone_oct("5Ew", 1);
	tone_oct("5Fw", 0.5);
	tone_oct("5Ew", 0.5);
	tone_oct("5Bw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Dw", 1);
	tone_oct("5Ew", 0.5);
	tone_oct("5Dw", 0.5);
	tone_oct("5Cw", 1);
	tone_oct("5Bw", 1);
	tone_oct("5Aw", 1);
	tone_oct("4Ew", 1);
	tone_oct("5Aw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Ew", 1);
	tone_oct("5Fw", 0.5);
	tone_oct("5Ew", 0.5);
	tone_oct("5Dw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Bw", 1);
	tone_oct("4Ew", 1);
	tone_oct("4Gh", 1);
	tone_oct("5Bw", 1);
	tone_oct("5Dw", 1);
	tone_oct("4Gh", 1);
	tone_oct("5Ew", 1);
	tone_oct("4Gh", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Aw", 1);
	tone_oct("4Gh", 1);
	tone_oct("5Aw", 1);
	tone_oct("5Aw", 3);
	tone_oct("0Hw", 1);
	
	tone_oct("5Dw", 1);
	tone_oct("5Aw", 1);
	tone_oct("5Dw", 1);
	tone_oct("5Fw", 1);
	tone_oct("6Aw", 1);
	tone_oct("6Bw", 0.5);
	tone_oct("6Aw", 0.5);
	tone_oct("5Gw", 1);
	tone_oct("5Fw", 1);
	tone_oct("5Ew", 1);
	tone_oct("5Aw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Dw", 1);
	tone_oct("5Ew", 1);
	tone_oct("5Aw", 1);
	tone_oct("5Dw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Bw", 1);
	tone_oct("4Ew", 1);
	tone_oct("4Gh", 1);
	tone_oct("5Bw", 1);
	tone_oct("5Dw", 1);
	tone_oct("4Gh", 1);
	tone_oct("5Bh", 1);
	tone_oct("5Dw", 1);
	tone_oct("5Fw", 1);
	tone_oct("5Dw", 1);
	tone_oct("5Gh", 1);
	tone_oct("6Bw", 1);
	tone_oct("6Dw", 1);
	tone_oct("6Fw", 1);
	tone_oct("6Gh", 1);
	tone_oct("7Bw", 1);
	tone_oct("7Ew", 4);
	tone_oct("0Hw", 2);
	tone_oct("7Ew", 0.5);
	tone_oct("7Dw", 0.5);
	tone_oct("7Cw", 0.5);
	tone_oct("7Bw", 0.5);
	tone_oct("7Aw", 1);
	tone_oct("0Hw", 3);
	tone_oct("6Aw", 1);
	tone_oct("0Hw", 3);
	delay_ms(1000);
}