/*============================================================
工程：字符型液晶通用六线驱动
作者：朱海峰		
日期：2007.02.28
E_mail:ntzhf100@163.com

液晶指令说明：
0x08==============>关闭显示
0x0c==============>开显示
0x01==============>清除LCD的显示内容
0x06==============>移动光标
0x0c==============>显示开，光标关
0x28==============>16*2显示，5*7点阵，4位数据
0x1c==============>字符右移一格
0x18==============>字符左移一格
0x10==============>光标右移一格
0x14==============>光标左移一格
显示地址：
===============================================================
=0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 ................ 0x27=
=0x40 0x41 0x42 0x43 0x44 0x45 0x46 0x47 ................ 0x67=
===============================================================
每行可以显示40个字符，可以看到的只有16个字符，可以通过指令使字符
整体移动来显示所有字符。
LCD_write_byte函数功能：当cmd＝0时，向LCD写入数据，否则向LCD写
                   入命令
四线控制的方式：先送字节的高四位，在送低四位。
值得注意的是当使用的I/O口为高四位时数据先给另一个变量，变量再将
数据高四位送到I/O口，接着是将变量左移四位，再送到I/O口上去。
当使用的I/O口为低四位时数据先给另一个变量，变量右移四位后送到I/O
口上去，接着将数据给变量直接送入I/O口。
使用时注意一下。
============================================================*/
#ifndef __Lcd_1602_6wires_h__
#define __Lcd_1602_6wires_h__

//定义MCU与LCD的接口
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
                     函数声明
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

