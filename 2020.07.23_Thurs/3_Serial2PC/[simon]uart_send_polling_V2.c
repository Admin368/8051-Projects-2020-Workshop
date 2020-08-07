#include<reg52.h>
#include<string.h>

#define uchar unsigned char
	
char myMSG[] = {"The world is a beautiful place\n"}; 

void delay(uchar x);
void uart_init();
void uart_TX(char _data);

void main()
{
	char i = 0;
	uart_init();
	
	while(1)
	{
		for(i=0; i<strlen(myMSG);i++)
		{
			uart_TX(myMSG[i]);
			delay(10);
		}
		
	}
}

void delay(uchar x)
{
	uchar y;
	while(x--)
		for(y = 0; y<120; y++);
}
void uart_init()
{
	// initialize timer 1 in mode 2(8 bit auto reload)
	TMOD = 0x20;
	TH1 = 0xfd;
	SCON = 0x50;
	TR1 = 1;
	TI =  0;
}
void uart_TX(char _data)
{
	SBUF = _data;
	while(TI == 0);
	TI = 0;
}
