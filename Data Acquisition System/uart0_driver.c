#include<lpc21xx.h>
#include"header.h"

void uart0_init(unsigned int baud)
{
	int a[]={15,60,30,0,15};
	unsigned int pclk=a[VPBDIV]*1000000;
	unsigned int result=0;
	result=pclk/(16*baud);
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLL= result& 0xff;
	U0DLM=(result>>8)& 0xff;
	U0LCR=0x03;
}

void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

unsigned char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_string(signed char *p)
{
	while(*p!=0)
	{
		U0THR=*p;
		while(THRE==0);
		p++;
	}
}

void uart0_rx_string(signed char *p,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		p[i]=uart0_rx();
		if(p[i]=='\r')
			break;
	}
	p[i]='\0';
}

void uart0_integer(int num)
{
	int a[100],i;
	if(num==0)
	uart0_tx('0');
	if(num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	i=0;
	while(num)
	{
		a[i]=num%10;
		num=num/10;
		i++;
	}
	for(--i;i>=0;i--)
	uart0_tx(a[i]+48);
}

void uart0_float(float num)
{
	int a[100],i;
	i=num;
	uart0_integer(i);
	uart0_tx('.');
	i=(num-i)*10;
	uart0_tx(a[i]+48);
}