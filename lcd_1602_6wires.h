/*============================================================
���̣��ַ���Һ��ͨ����������
���ߣ��캣��		
���ڣ�2007.02.28
E_mail:ntzhf100@163.com

Һ��ָ��˵����
0x08==============>�ر���ʾ
0x0c==============>����ʾ
0x01==============>���LCD����ʾ����
0x06==============>�ƶ����
0x0c==============>��ʾ��������
0x28==============>16*2��ʾ��5*7����4λ����
0x1c==============>�ַ�����һ��
0x18==============>�ַ�����һ��
0x10==============>�������һ��
0x14==============>�������һ��
��ʾ��ַ��
===============================================================
=0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 ................ 0x27=
=0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 ................ 0x67=
===============================================================
ÿ�п�����ʾ40���ַ������Կ�����ֻ��16���ַ�������ͨ��ָ��ʹ�ַ�
�����ƶ�����ʾ�����ַ���
LCD_write_byte�������ܣ���cmd��0ʱ����LCDд�����ݣ�������LCDд
                   ������
���߿��Ƶķ�ʽ�������ֽڵĸ���λ�����͵���λ��
ֵ��ע����ǵ�ʹ�õ�I/O��Ϊ����λʱ�����ȸ���һ�������������ٽ�
���ݸ���λ�͵�I/O�ڣ������ǽ�����������λ�����͵�I/O����ȥ��
��ʹ�õ�I/O��Ϊ����λʱ�����ȸ���һ������������������λ���͵�I/O
����ȥ�����Ž����ݸ�����ֱ������I/O�ڡ�
ʹ��ʱע��һ�¡�
============================================================*/
#ifndef __Lcd_1602_6wires_h__
#define __Lcd_1602_6wires_h__

//����MCU��LCD�Ľӿ�
#define LCD_DATA_PORT	  	PORTD
#define LCD_DATA_DDR	  	DDRD
#define LCD_CONTROL_PORT  	PORTC
#define LCD_CONTROL_DDR   	DDRC
#define LCD_DATA          	0xF0
#define RS				  	(1<<PC0)
#define EN				  	(1<<PC1)
#define SET_RS()		  	LCD_CONTROL_PORT |= RS
#define CLR_RS()		  	LCD_CONTROL_PORT &= ~RS
#define SET_EN()		  	LCD_CONTROL_PORT |= EN
#define CLR_EN()		  	LCD_CONTROL_PORT &= ~EN

/*
#define BK_LIGHT		  	(1<<PB1)
#define BK_PORT			  	PORTB
#define BK_DDR			  	DDRB
#define BK_LIGHT_ON()		BK_DDR |= BK_LIGHT;BK_PORT |= BK_LIGHT
#define BK_LIGHT_OFF()		BK_DDR |= BK_LIGHT;BK_PORT |= ~BK_LIGHT
*/
/*-----------------------------------------------------
                     ��������
-------------------------------------------------------*/
void LCD_init         		(void);
void LCD_write_byte         (unsigned char cmd,unsigned char data);
void LCD_Write_half_byte	(unsigned char half_byte);
void LCD_set_xy             (unsigned char x, unsigned char y);
void LCD_write_string       (unsigned char X,unsigned char Y,unsigned char *s);
void Move					(unsigned char step,unsigned char dirction,unsigned int time);
void Flash_lcd				(unsigned int delay_t,unsigned char times);
void Delay_nms				(unsigned int ms);
//==================================================
#endif

