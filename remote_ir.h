/*
 * remote_ir.h
 *
 * Created: 2012/6/15 0:26:13
 *  Author: Administrator
 */ 


/*

��00000000��11111110��01110000��10001111��  +

10000000��01111111  -

10110000��01001111  play

00000000��11111111   ��

10010000��01101111  �M

11010000��00101111   off

 

 

Start   low 9.04ms, high 4.48ms, (low 600us, high 520us,)

Repeat  Low 9.08ms  ,high 2.2ms, Low 560us  high

 

(low 600us, high 520us,)(0)

Low 600us, high 1.64ms (1)



*/


#ifndef __REMOTE_IR_H__
#define __REMOTE_IR_H__

/*
 * reference_ir.c
 *
 * Created: 2012/1/31 ���� 02:30:45
 *  Author: Cherry_Yuan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define uchar unsigned char
#define uint unsigned int
//#pragma interrupt_handler Int0:2
#define pd2 (PIND&0x04)

uchar r=0,ir_data=0,tab[4]={0};


void delay_n_100us(uint n)
{
	TCNT0 = 0x6a; //set count
    TCCR0A = 0x00;
    TCCR0B = 0x02; //start timer  
	while(n)
	{
		if(TCNT0==0xFF)
		{
			TCNT0=0x6A;
			n--;
		}
    }
    TCCR0B = 0x00; //stop
}


void IR_init(void)
{
	 DDRD &= ~(1<<PD2);
	 
/*****atmega48***************************************/
	EICRA |= (1<<ISC00);	//INT0 �½��ش����ж�
	EIFR |= (1<<INTF0);		//clear INTF0 flag
	EIMSK |= (1 << INT0);	//�ⲿ�ж�����0�ж�ʹ��
/**************************************************/
}



SIGNAL(INT0_vect)
{
    uchar i,j,n=0;
    SREG=0x00;         //�ر����ж�
	tab[4]=0;
	if(pd2)
	{
		r=1;
		sei();        //�����ж�
		return;
	}
	while(!pd2);   //�ȴ�9ms�͵�ƽ��
	while(pd2);    //�ȴ�4.5ms�ߵ�ƽ��
	for(i=0;i<4;i++)
		for(j=0;j<8;j++)
		{
			while(!pd2);   //�ȴ�0.56ms�͵�ƽ��
			while(pd2)
			{
				delay_n_100us(1);
				n++;        //ÿ��100us�Ĵ���n�Լ�1
			}
			tab[i]=tab[i]>>1;
			if(n>6) tab[i]|=0x80;
			n=0;
		}
	delay_n_100us(1000);
	if(tab[2]==~tab[3]) {ir_data=tab[2];}
	else tab[4]=0;
	r=1;
	
	sei();        //�����ж�
	return;
}





#endif /* REMOTE_IR_H_ */