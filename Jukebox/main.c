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

/*
#define LCD_DATA_D DDRA
#define LCD_DATA_P PORTA     //LCD데이터 포트 정의
#define	LCD_CTRL_D DDRA
#define LCD_CTRL_P PORTA   //LCD 제어 포트 정의
#define LCD_EN 0x04         //LCD 제어(PINA0~2)를 효과적으로 하기위한 정의
#define LCD_RW 0x02
#define LCD_RS 0x01
#define LCD_DB 0xf0

#define FUNCSET 0x28
#define ENTMODE 0X06
#define	ALLCLR	0X01
#define	DISPON	0x0c

#define KEY_DIR		DDRC	
#define KEY_PORT	PORTC	
#define KEY_PIN		PINC

volatile unsigned long long delay = 0;
volatile unsigned int bpm = 60;

void timer_init(void);
void delay_ms(int val);

void LCD_init(void);
void LCD_data(unsigned char byte);
void LCD_command(unsigned char byte);
void LCD_busy(void);
void LCD_string(char *str);
void LCD_pos(unsigned char col, unsigned char row);

unsigned char keyboard();
unsigned char key_scan();

void korobeiniki(void);

void ctc1_init(void);
void tone(double hz, int s_time);
void tone_oct(char oct[], double meter); //총 요소 3개 첫번째 : 옥타브  두번째 : 음  세번째 : 온음(w)/반음(h)
*/

extern volatile unsigned int bpm;

void korobeiniki();

int main(void)
{
	sei();
	timer_init();
	ctc1_init();
	DDRA = 0xff;
	DDRB = 0xff;
	//EIMSK = 0xff;
	//EICRA = 0xff;
	SFIOR = 0x00;
	//KEY_DIR = 0x0f;
	//KEY_PORT = 0xff;
		
	DDRC = 0xff;
	PORTC = 0x0f;
	LCD_init();
	LCD_pos(0, 0);
	LCD_string("jukebox1");
	LCD_pos(0, 1);
	korobeiniki();
	while (1)
	{
		/*
		bpm = 60;
		tone_oct("4Cw", 1);
		tone_oct("4Dw", 1);
		tone_oct("4Ew", 1);
		tone_oct("4Fw", 1);
		tone_oct("4Gw", 1);
		tone_oct("5Aw", 1);
		tone_oct("5Bw", 1);
		tone_oct("5Cw", 1);
		*/
		
	}
}

/*
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

void LCD_data(unsigned char byte)
{
	LCD_busy();
	LCD_CTRL_P |= LCD_RS;		//RS = 1
	LCD_CTRL_P &= ~LCD_RW;		//RW = 0

	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0xf0 & byte);      //데이터 상위 4비트 쓰기
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;		//LCD 사용허가
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD 사용안함
	
	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0Xf0 & (byte << 4));		//데이터 하위 4비트 쓰기
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;    //LCD 사용허가
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD 사용안함
}

void LCD_command(unsigned char byte)			   //PG0-EN , PG1-RW, PG2-RS , PG4-TOSC1핀(사용안함)
{							       //LCD_CTRL = LCD제어부 포트(4핀인데 실질적인 사용3핀)
	LCD_busy();
	LCD_CTRL_P &= (~LCD_RS)&(~LCD_RW); // RS=0, RW=0 으로 정의함.
	
	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0xf0 & byte);      //명령어 상위 4비트 쓰기
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;		//LCD 사용허가
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD 사용안함
	
	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0Xf0 & (byte << 4));		//명령어 하위 4비트 쓰기
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;    //LCD 사용허가
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD 사용안함
}

void LCD_busy(void){
	delay_ms(2);
}

void LCD_string(char *str)    //↑문자열을 한문자씩 출력함수로 전달
{
	while(*str != '\0' )
	{
		LCD_data(*str);
		str++;
	}
}

void LCD_pos(unsigned char col, unsigned char row)  //LCD 포지션 설정
{
	LCD_command(0x80 | (col+(row*0x40)));  // row=행 / col=열 ,DDRAM주소설정
}


void LCD_init(void)   //LCD 초기화
{
	LCD_CTRL_D |= LCD_RS|LCD_RW|LCD_EN;
	LCD_DATA_D |= LCD_DB;
	LCD_CTRL_P &= (~LCD_RS)&(~LCD_RW)&(~LCD_EN);
	
	delay_ms(15);
	LCD_command(0x20);
	delay_ms(5);
	LCD_command(0x20);
	delay_ms(1);
	LCD_command(0x20);
	LCD_command(FUNCSET);   //데이터 4비트 사용, 5X7도트 , LCD2열로 사용(6)
	LCD_command(DISPON);   //Display ON/OFF
	LCD_command(ALLCLR);
	LCD_command(ENTMODE);   //주소 +1 , 커서를 우측으로 이동 (3)
}

unsigned char keyboard(){
	int i;
	unsigned char row = 0xFE;
	unsigned char key_buf;

	KEY_PORT = 0xff;
	for(i = 0; i < 4; i++){
		KEY_PORT = row;
		delay_ms(1000);
		key_buf = KEY_PIN;
		switch (KEY_PIN)
		{
			case 0xD7: key_buf = 0x00; break;
			case 0xEE: key_buf = 0x01; break;
			case 0xDE: key_buf = 0x02; break;
			case 0xBE: key_buf = 0x03; break;
			case 0xED: key_buf = 0x04; break;
			case 0xDD: key_buf = 0x05; break;
			case 0xBD: key_buf = 0x06; break;
			case 0xEB: key_buf = 0x07; break;
			case 0xDB: key_buf = 0x08; break;
			case 0xBB: key_buf = 0x09; break;
			case 0x7E: key_buf = 0x0A; break;
			case 0x7D: key_buf = 0x0B; break;
			case 0x7B: key_buf = 0x0C; break;
			case 0x77: key_buf = 0x0D; break;
			case 0xE7: key_buf = 0x0E; break;
			case 0xB7: key_buf = 0x0F; break;
			default: key_buf = 0xff; break;
		}
		if (key_buf != 0xff)
		{
			return key_buf;
		}
		row = (row << 1) | 0x01;
	}
	return key_buf;
}

unsigned char key_scan(){
	unsigned char key_value;
	key_value = keyboard();
	if(key_value == 0xff){
		while((key_value =keyboard()) == 0xff);
	}
	return key_value;
}

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
*/

void korobeiniki(void){
	bpm = 300;
	/*
	tone_oct("5Ew", 2);
	tone_oct("5Bw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Dw", 2);
	tone_oct("5Cw", 1);
	tone_oct("5Bw", 1);
	tone_oct("5Aw", 3);
	tone_oct("5Cw", 1);
	tone_oct("5Ew", 2);
	tone_oct("5Dw", 1);
	tone_oct("5Cw", 1);
	tone_oct("5Bw", 3);
	tone_oct("5Cw", 1);
	tone_oct("5Dw", 2);
	tone_oct("5Ew", 2);
	tone_oct("5Cw", 2);
	tone_oct("5Aw", 2);
	tone_oct("5Aw", 4);
	*/
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