#include "timer.h"

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