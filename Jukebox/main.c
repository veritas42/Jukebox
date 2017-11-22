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

void play();
void SOS();
void korobeiniki();
void rasputin();

int main(void)
{
	sei();
	timer_init();
	ctc1_init();
	LCD_init();
	butten_init();
	LCD_pos(0, 0);
	LCD_string("jukebox");
	LCD_pos(0, 1);
	tone(440, 1000);
	DDRE = 0xff;
	while (1)
	{
		play();
	}
}

void play(){
	
	switch(select){
		case 1:
		LCD_pos(0, 1);
		LCD_string("korobeiniki");
		if(state){
			korobeiniki();
			state = 0;
		}
		break;
		case 0:
		LCD_pos(0, 1);
		LCD_string("rasputin");
		if(state){
			rasputin();
			state = 0;
		}
		break;
		case 2:
		LCD_pos(0, 1);
		LCD_string("aaa");
		break;
	
	}
		
}

void SOS(){
	bpm = 240;
	tone_oct("4Aw", 1);
	tone_oct("4Aw", 1);
	tone_oct("4Aw", 1);
	tone_oct("4Aw", 3);
	tone_oct("4Aw", 3);
	tone_oct("4Aw", 3);
	tone_oct("4Aw", 1);
	tone_oct("4Aw", 1);
	tone_oct("4Aw", 1);
	tone_oct("4Hw", 5);
}

void korobeiniki(void){
	bpm = 300;
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

void rasputin(void){
	bpm = 160;
	tone_oct("5Bw", 1);
	tone_oct("5Bw", 1);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 1);
	tone_oct("4Gh", 0.5);
	tone_oct("4Gh", 0.5);
	tone_oct("4Gh", 0.5);
	tone_oct("4Gh", 0.5);
	tone_oct("4Fh", 0.5);
	tone_oct("4Ew", 0.5);
	tone_oct("4Dh", 1);
	
	tone_oct("4Hw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("4Gh", 1);
	tone_oct("4Gh", 1);
	tone_oct("4Fh", 0.5);
	tone_oct("4Fh", 0.5);
	tone_oct("4Ew", 0.5);
	tone_oct("4Fh", 2.5);
	
	tone_oct("5Bw", 1);
	tone_oct("5Bw", 1);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 1);
	tone_oct("4Gh", 0.5);
	tone_oct("4Gh", 0.5);
	tone_oct("4Gh", 0.5);
	tone_oct("4Gh", 0.5);
	tone_oct("4Fh", 0.5);
	tone_oct("4Ew", 0.5);
	tone_oct("4Dh", 1);
	
	tone_oct("4Hw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("5Aw", 0.5);
	tone_oct("4Gh", 1);
	tone_oct("4Gh", 1);
	tone_oct("4Fh", 0.5);
	tone_oct("4Fh", 0.5);
	tone_oct("4Ew", 0.5);
	tone_oct("4Fh", 2.5);
	delay_ms(1000);
}