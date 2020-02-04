/*
 * pga2310.h
 *
 * Created: 2012/6/15 上午 09:06:47
 *  Author: Cherry_Yuan
 */ 


#ifndef PGA2310_H_
#define PGA2310_H_


/*
 * SPI.h
 *
 * Created: 2011/11/24 22:59:10
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "switch.h"


#define   SET_1(a,b)  a|=(1<<b) 
#define   CLE_0(a,b)  a&=~(1<<b) 
/*
#define ZCEN_PORT PORTC
#define ZCEN_DDR  DDRC
#define ZCEN  PC3
*/

/*******************************************************************************/
/* PROCEDURE: HW_SPI_Init */
/* */
/* This procedure initializes the hardware SPI on the MCU. */
/* */
/* Input: None */
/* */
/* Returns: Nothing */
/* */
/*******************************************************************************/
void spiInit(void )
{
DDRB |= ((1<<PB2)|(1<<PB5)|(1<<PB3));	 // Set MOSI , SCK , and SS output
//CLE_0(DDRB,6);
//CLE_0(PORTB,1);
	SPCR =  _BV(CPOL)|_BV(CPHA)|_BV(SPE)|_BV(MSTR)|_BV(SPR0)|_BV(SPR1);
	SPSR |= _BV(SPI2X);

}


unsigned char spiByte(unsigned char addr)
{
	SPDR = addr;					//Load byte to Data register
	while(!(SPSR & (1<<SPIF))); 	// Wait for transmission complete 
	return SPDR;
}



//#define SPIFLASH_CONFIG_CS		DDRB  |= (1<<PB2)
#define SPIFLASH_ASSERT_CS		PORTB &= ~(1<<PB2)
#define SPIFLASH_RELEASE_CS		PORTB |= (1<<PB2)

#define MUTE_CONFIG  DDRB |=(1<<PB1)
#define MUTE         PORTB &=~(1<<PB1)
#define uMUTE        PORTB =(1<<PB1)

// functions
void Pga2310_port_Init(void)
{
	// initialize spi
	SPIFLASH_RELEASE_CS;
	spiInit();
	// initialize chip select
	
	//SPIFLASH_CONFIG_CS;
	
	MUTE_CONFIG;
	MUTE;

	
	
}


void PGA2310_Write(unsigned char data)
{
		// enable write
		SPIFLASH_ASSERT_CS;
		spiByte(data); //left
		spiByte(data); //right
		SPIFLASH_RELEASE_CS;
		// clock out dummy byte to waste time
		spiByte(0x00);

}




#endif /* PGA2310_H_ */