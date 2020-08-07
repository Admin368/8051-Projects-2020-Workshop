#include<reg52.h>

sbit rs = P2^3; // register select
sbit rw = P2^4; // read/write
sbit en = P2^5; // read/write enable

void lcd_init(); // lcd initialization
void write_com(char com); //write command
void write_data(char _data); // write data

void delay(char x);// delay function
void main()
{
	lcd_init();
	write_data('a');
	while(1)
	{}
}

void lcd_init() // lcd initialization
{
		// prepare the screen -16*2 5*7 matrix
		write_com(0x38);
		// turn on display
		write_com(0x08);
	  // prepare cursor and data pointer
		write_com(6);
	  // push curso to frist line
	  write_com(0x80);
		// clear the screen
		write_com(1);
}
void write_com(char com) //write command
{
	rs = 0; rw =0; P0 = com;
	en = 0;
	delay(10);
	en = 1;
	delay(10);
	en = 0;
}
void write_data(char _data) // write data
{
	rs = 1;  rw = 0; P0 = _data;
	en = 0;
	delay(10);
	en = 1;
	delay(10);
	en = 0;
	
}

void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}