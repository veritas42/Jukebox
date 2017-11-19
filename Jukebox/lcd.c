#include "timer.h"

void LCD_data(unsigned char byte)
{
	LCD_busy();
	LCD_CTRL_P |= LCD_RS;		//RS = 1
	LCD_CTRL_P &= ~LCD_RW;		//RW = 0

	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0xf0 & byte);      //������ ���� 4��Ʈ ����
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;		//LCD ����㰡
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD ������
	
	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0Xf0 & (byte << 4));		//������ ���� 4��Ʈ ����
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;    //LCD ����㰡
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD ������
}

void LCD_command(unsigned char byte)			   //PG0-EN , PG1-RW, PG2-RS , PG4-TOSC1��(������)
{							       //LCD_CTRL = LCD����� ��Ʈ(4���ε� �������� ���3��)
	LCD_busy();
	LCD_CTRL_P &= (~LCD_RS)&(~LCD_RW); // RS=0, RW=0 ���� ������.
	
	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0xf0 & byte);      //��ɾ� ���� 4��Ʈ ����
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;		//LCD ����㰡
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD ������
	
	LCD_DATA_P = (LCD_DATA_P & 0X0f) | (0Xf0 & (byte << 4));		//��ɾ� ���� 4��Ʈ ����
	//delay_ms(1);
	LCD_CTRL_P |= LCD_EN;    //LCD ����㰡
	//delay_ms(1);
	LCD_CTRL_P &= ~LCD_EN;    //LCD ������
}

void LCD_busy(void){
	delay_ms(2);
}

void LCD_string(char *str)    //�蹮�ڿ��� �ѹ��ھ� ����Լ��� ����
{
	while(*str != '\0' )
	{
		LCD_data(*str);
		str++;
	}
}

void LCD_pos(unsigned char col, unsigned char row)  //LCD ������ ����
{
	LCD_command(0x80 | (col+(row*0x40)));  // row=�� / col=�� ,DDRAM�ּҼ���
}


void LCD_init(void)   //LCD �ʱ�ȭ
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
	LCD_command(FUNCSET);   //������ 4��Ʈ ���, 5X7��Ʈ , LCD2���� ���(6)
	LCD_command(DISPON);   //Display ON/OFF
	LCD_command(ALLCLR);
	LCD_command(ENTMODE);   //�ּ� +1 , Ŀ���� �������� �̵� (3)
}