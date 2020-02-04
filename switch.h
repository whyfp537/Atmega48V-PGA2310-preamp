/*
 * switch.h
 *
 * Created: 2012/6/15 0:29:29
 *  Author: Administrator
 */ 


#ifndef __SWITCH_H__
#define __SWITCH_H__

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "voltage_index.h"

#define SWITCH_AC_DDR  DDRD
#define SWITCH_AC_PORT PORTD
#define SWITCH_AC_PIN  PIND
#define SWITCH_AC_BIT  3

#define SWITCH_BC_DDR  DDRD
#define SWITCH_BC_PORT PORTD
#define SWITCH_BC_PIN  PIND
#define SWITCH_BC_BIT  1


#define Channel_select_DDR DDRC
#define Channel_select_PORT PORTC
#define Channel_A_select Channel_select_PORT&=(~(1<<PC4))  //  C:PC5  B:PC3  A:PC4
#define Channel_B_select Channel_select_PORT&=(~(1<<PC3))
#define Channel_C_select Channel_select_PORT&=(~(1<<PC5))
#define Channel_clear Channel_select_PORT|=((1<<PC3)|(1<<PC4)|(1<<PC5))


/*
#define SWITCH_EN_DDR  DDRD
#define SWITCH_EN_PORT PORTD
#define SWITCH_EN_PIN  PIND
#define SWITCH_EN_BIT  4

#define VID_OUT_DDR DDRB
#define VID_OUT_PORT PORTB

#define Buttom_EN_DDR DDRD
#define Buttom_EN_PORT PORTD
#define Buttom_EN_PIN PIND
#define Buttom_EN_BIT 3
*/
#define AC_status() SWITCH_AC_PIN&(1<<SWITCH_AC_BIT)
#define BC_status() SWITCH_BC_PIN&(1<<SWITCH_BC_BIT)
//#define EN_status() SWITCH_EN_PIN&(1<<SWITCH_EN_BIT)
//#define Buttom_set() Buttom_EN_PIN&(1<<Buttom_EN_BIT)

void SWITCH_PORT_INI(void)
{
	SWITCH_AC_DDR &= ~(1<<SWITCH_AC_BIT);
	SWITCH_BC_DDR &= ~(1<<SWITCH_BC_BIT);
//	SWITCH_EN_DDR &= ~(1<<SWITCH_EN_BIT);
//	Buttom_EN_DDR &= ~(1<<Buttom_EN_BIT);
//	VID_OUT_DDR=0xFF;

/*****atmega48***************************************/
	EICRA |= (1<<ISC10);	//INT1 下降沿触发中断
	EIFR |= (1<<INTF1);		//clear INTF1 flag
	EIMSK |= (1 << INT1);	//外部中断请求1中断使能
/**************************************************/


/***************ATmega8*************************/



/************************************************/	
	
}


void Channel_init(void)
{
	Channel_select_PORT|=0x38;//PC3,4,5 output high
	Channel_select_DDR|=(1<<PC3)|(1<<PC4)|(1<<PC5);//PC3--5 output
	
}



//external interrupt 1 process
SIGNAL(INT1_vect)
{
	//external interupt on INT1
	
    cli();         //关闭总中断
//	if(AC_status()) //猽牟祇, ┮A狠﹚琌筿キ, ぃノ耞
		if(!(BC_status()))
		{	
			if(volume_data>1)
				volume_data--;
			else
				volume_data=1;
		}
		 
		else
		{	
			if(volume_data<255)
				volume_data++;
			else 
				volume_data=255;
		}		

	
	sei();

}



#endif /* SWITCH_H_ */