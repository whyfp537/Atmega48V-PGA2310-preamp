/*****************************************************
*File name:lcd_1602_6wires.c
*Author:Andy Zhu
*Date:2008.7.25
*Version:V1.01
*****************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_1602_6wires.h"

//==================================================
void LCD_init(void)
{
	/*****************液晶使用的I/O口初始化*******************/	 
	LCD_DATA_PORT = 0X00;
	LCD_DATA_DDR |= LCD_DATA;
	LCD_CONTROL_DDR |= RS|EN;
//	BK_LIGHT_ON();	//开液晶背光
	/*********************液晶初始化**************************/	
	_delay_ms(50);                 
    LCD_write_byte(1,0x28); 		//4bit test    显示模式设置(不检测忙信号) 
    _delay_ms(1);  
    LCD_write_byte(1,0x08);         // 显示关闭 
    _delay_ms(1); 
    LCD_write_byte(1,0x01);         // 显示清屏 
    _delay_ms(1); 
    LCD_write_byte(1,0x06);         // 显示光标移动设置 
    _delay_ms(1); 
    LCD_write_byte(1,0x0C);         // 显示开及光标设置 
    _delay_ms(10);
}
/*--------------------------------------------------
LCD_write_byte    : 英文字符显示函数
输入参数：*s      ：英文字符串指针；
          X、Y    : 显示字符串的位置，X:1-16，Y:1-2 		
---------------------------------------------------*/
void LCD_write_byte(unsigned char cmd,unsigned char data)
{       
	unsigned char data_temp;
	if (cmd==1)
	{
	   CLR_RS();
	}
	if (cmd==0)
	{
	   SET_RS();
	}
	data_temp=data;
	//data_temp=data_temp>>4;
    LCD_Write_half_byte(data_temp);
	data_temp=data<<4;
    LCD_Write_half_byte(data_temp);
	_delay_ms(1);	 
}
/*----------------写高4bit到LCD------------------------*/
void LCD_Write_half_byte(unsigned char half_byte)
{  
	LCD_DATA_PORT&=0x0f;	  //
   	LCD_DATA_PORT=half_byte;//send high 4bit
	SET_EN();
	_delay_loop_1(1);
	CLR_EN(); 
	_delay_loop_1(1);
}

/*----------------------------------------------------
LCD_set_xy        : 设置LCD显示的起始位置
输入参数：x、y    : 显示字符串的位置，X:1-16，Y:1-2		
-----------------------------------------------------*/
void LCD_set_xy( unsigned char x, unsigned char y )
{
	unsigned char address;
    if (y==1) 
	{
	   address=0x80-1+x;
	}
    else 
    {
	   address=0xc0-1+x;
	}
    LCD_write_byte(1,address);
}
/*---------------------------------------------------
LCD_write_string  : 英文字符串显示函数
输入参数：*s      ：英文字符串指针；
          X、Y    : 显示字符串的位置		
---------------------------------------------------*/
void LCD_write_string(unsigned char X,unsigned char Y,unsigned char *s)
{
	LCD_set_xy( X, Y );   
    while (*s) 
    {
		LCD_write_byte(0,*s);
		s++;
     }
}
//=======================================================
void Move(unsigned char step,unsigned char dirction,unsigned int time)
{
 	unsigned char i;
	for(i=0;i<step-1;i++)
	{
		LCD_write_byte(1,dirction);      //字符移动方向                                    
        Delay_nms(time);                //控制移动时间
	}
}
//=========================================================
void Flash_lcd(unsigned int delay_t, unsigned char times)
{
	unsigned char j;
	for(j=0;j<times;j++)
	{
		LCD_write_byte(1,0x08);
		Delay_nms(delay_t);
		LCD_write_byte(1,0x0c);
		Delay_nms(delay_t);
	}
}

//========================================================
void Delay_nms( unsigned int ms) 
{ 
	for (; ms>0; ms--)
	{
		_delay_ms(1);
	}
} 
//========================================================


