#ifndef _LCD_

#define _LCD_

#define LCD_DATA_D DDRA
#define LCD_DATA_P PORTA     //LCD������ ��Ʈ ����
#define	LCD_CTRL_D DDRA
#define LCD_CTRL_P PORTA   //LCD ���� ��Ʈ ����
#define LCD_EN 0x04         //LCD ����(PINA0~2)�� ȿ�������� �ϱ����� ����
#define LCD_RW 0x02
#define LCD_RS 0x01
#define LCD_DB 0xf0

#define FUNCSET 0x28
#define ENTMODE 0X06
#define	ALLCLR	0X01
#define	DISPON	0x0c

void LCD_init(void);
void LCD_data(unsigned char byte);
void LCD_command(unsigned char byte);
void LCD_busy(void);
void LCD_string(char *str);
void LCD_pos(unsigned char col, unsigned char row);

#endif