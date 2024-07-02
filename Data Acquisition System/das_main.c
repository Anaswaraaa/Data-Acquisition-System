#include<LPC21XX.H>
#include"header.h"

int main()
{
	int tempr2;
	unsigned int ret;
	unsigned long int adcval1,adcval2,light_perc;
	float vout,pressure,tempr;
	unsigned char hr,min,sec;
	uart0_init(9600);
	i2c_init();
	spi0_init();
	adc_init();
	uart0_tx_string("Data Acquisition System\r\n");
	i2c_byte_write_frame(0xD0,0x0,0x56);
	i2c_byte_write_frame(0xD0,0x1,0x56);
	i2c_byte_write_frame(0xD0,0x2,0x08);

	while(1)
	{
	///pressure
	adcval1=adc_read(2);
	uart0_tx_string("\r\n");
	uart0_tx_string("\Pressure\r\n");
	vout=(adcval1*3.3)/1023;
	pressure=(vout/(0.009*3.3))+(0.095/0.009);
	uart0_float(vout);
	uart0_tx_string("kpa");
	uart0_tx_string("\r\n");


	//temparature
	adcval2=adc_read(1);
	uart0_tx_string("temparature\r\n");
	vout=(adcval2*3.3)/1024;
	tempr=(vout-0.5)/0.01;
	tempr2=tempr;
	uart0_integer(tempr2);
	uart0_tx_string("degree celsius\r\n");
	uart0_tx_string("\r\n");

	//Light Intensity
	ret=mcp3204_adc_read(0);
	light_perc=100-((ret*100)/4095);
	uart0_tx_string("Light Intensity: ");
	uart0_integer(light_perc);
	uart0_tx_string("%");
	uart0_tx_string("\r\n");

	hr=i2c_byte_read_frame(0xD0,0X2);
	min=i2c_byte_read_frame(0xD0,0x1);
	sec=i2c_byte_read_frame(0xD0,0x0);
	uart0_tx_string("Time:");
	uart0_tx((hr/0x10)+48);
	uart0_tx((hr%0x10)+48);
	uart0_tx(':');

	uart0_tx((min/0x10)+48);
	uart0_tx((min%0x10)+48);
	uart0_tx(':');

	uart0_tx((sec/0x10)+48);
	uart0_tx((sec%0x10)+48);
	uart0_tx_string("\r\n");

	delay_ms(2000);

	uart0_tx_string("---------------------------------------");

	}  
}