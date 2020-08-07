#include<reg52.h>

sbit rs = P2^3; // register select
sbit rw = P2^4; // read/write
sbit en = P2^5; // read/write enable

void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
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

void lcd_init() // lcd initialization
{
		// prepare the screen ->16*2 cells, 5*7 matrix for each cell
		write_com(0x38);
		// clear the screen
		write_com(1);
	  // prepare cursor and data pointer
		write_com(6);
	  // cursor setup
	  write_com(0x0c);
		//start on first line
	  write_com(0x80);
		
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

