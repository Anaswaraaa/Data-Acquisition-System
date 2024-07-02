#include<LPC21XX.H>
#include "header.h"
#define CS0 1<<7

unsigned int mcp3204_adc_read(unsigned char ch_num)
{
	unsigned char byte_H=0,byte_L=0,channel=0;
	unsigned int result=0;
	channel=ch_num<<6;
	IOCLR0=CS0;
	
	spi0(0x06);
	byte_H=spi0(channel);
	byte_L=spi0(0x0);
	IOSET0=CS0;
	byte_H&=0x0f;
	result=(byte_H<<8)|byte_L;
	return result;
}