/*********************************************************

*********************************************************/

unsigned char volume_data=10,channel_data=0;
unsigned int Gain_value;
unsigned char marking;

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
//#include "switch.h"
#include "switch.h"
#include "lcd_1602_6wires.h"
#include "pga2310.h"
#include "remote_ir.h"

#define nop		   asm("nop")

void ChipInit(void);		//芯片初始化
void volume_disp(void);
void DisplayCode(unsigned int IrData);
void channel_select(void);

unsigned char disp_update=0,pre_volume=0;
const uint8_t HexNumber[]={'0','1','2','3','4','5','6','7',
                           '8','9','A','B','C','D','E','F'};
						   
unsigned char temp_number[8];

/*****************************************************/

/*****************************************************/
int main(void)
{
	cli();						//全局中断禁止
//	ChipInit();
	SWITCH_PORT_INI();
	Channel_init();
	Pga2310_port_Init();
	IR_init();
	LCD_init();
	LCD_write_string(1,1,"Input: Chanel ");
	LCD_write_string(1,2,"Volume:     dB");
	sei();
	//SET_1(PORTB,1);//no mute
	uMUTE;
	Channel_A_select;
	while(1)
	{
		IR_update();
		volume_disp();
		channel_select();
		
	}


}



void volume_disp()
{
	if(pre_volume==volume_data) nop;
	
	else
	{
		unsigned char temp=0;
		if(volume_data>=192)
		{
			Gain_value=(unsigned int)(volume_data-192)*5;
			marking=0; //positive
		}
		else
		{
			Gain_value=(unsigned int)(192-volume_data)*5;
			marking=1; //negative
		}
		
		
		if(marking==1)
			LCD_write_string(8,2,"-");
		else 
			LCD_write_string(8,2," ");

		temp=Gain_value/100;
		LCD_write_byte(0,HexNumber[temp]);
		Gain_value=Gain_value%100;
		temp=Gain_value/10;
		LCD_write_byte(0,HexNumber[temp]);
		temp=Gain_value%10;
		LCD_write_string(11,2,".");
		LCD_write_byte(0,HexNumber[temp]);
		//DisplayCode(Gain_value);
		
		PGA2310_Write(volume_data);	
		
		pre_volume=volume_data;	
	}
		
	
		
		
}


/****************************************************
*函数功能：void DisplayCode(void)
*功能描述：在1602液晶上显示14位的红外码
*入口参数：无
*出口参数：无
*其    他：
*****************************************************/
/*void DisplayCode(unsigned int IrData)
{
 	 uint8_t i;
	 unsigned int pro_data;
	 pro_data = IrData;
	 for (i=4; i>=1; i--)
	 {
	  	 temp_number[i-1] = (uint8_t)pro_data;
		 temp_number[i-1] &= 0x0f;
		 pro_data >>=4;
	 }
	 LCD_set_xy(8,2);
	 for (i=0; i<4; i++)
	 {
		 LCD_write_byte(0,HexNumber[temp_number[i]]);
	 }
}*/
/****************************************************/

void IR_update(void)
{
	switch(ir_data)
	{
		case 0x70:// key "+"
			if(volume_data<255)
				volume_data++;
			else 
				volume_data=255;
			break;
		case 0x80: //key "-"
			if(volume_data>1)
				volume_data--;
			else
				volume_data=1;
			break;
		case 0x90:
			if(channel_data==2)channel_data=0;
			else 
				channel_data++;
			break;
		case 0x00:
			if(channel_data==0)channel_data=2;
			else
				channel_data--;
			break;
		default: break;
		
		
	}
	
	ir_data=0xff;


}


void channel_select(void)
{
	switch(channel_data)
	{
		case 0://select A
			Channel_clear;
			Delay_nms(10);
			Channel_A_select;
			break;
		case 1://select B
			Channel_clear;
			Delay_nms(10);
			Channel_B_select;
			break;
		case 3://select C
			Channel_clear;
			Delay_nms(10);
			Channel_C_select;
			break;

	}
}