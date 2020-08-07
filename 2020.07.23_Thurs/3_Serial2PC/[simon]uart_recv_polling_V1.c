#include<reg52.h>
#include<string.h>
#include "lcd_interface.c"

#define uchar unsigned char
	
char myMSG[] = {"The world is a beautiful place\n"}; 

void uart_init();
char uart_RX(); // receive data

void main()
{
	char i = 0;
	uart_init();
	lcd_init();
	while(1)
	{
		
			write_data(uart_RX());
		
		
	}
}


void uart_init()
{
	// initialize timer 1 in mode 2(8 bit auto reload)
	TMOD = 0x20;
	TH1 = 0xfd;
	SCON = 0x50;
	TR1 = 1;
	RI =  0;
}
char uart_RX( )
{
	char _data;
	while(RI == 0);
	_data = SBUF;
	RI=0;
	return _data;

}
