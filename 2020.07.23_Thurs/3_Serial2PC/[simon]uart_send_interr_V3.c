#include<reg52.h>
#include<string.h>

#define uchar unsigned char
	
char code myMSG[] = 
{
"#include<reg52.h>"
"#include<string.h>"
""
"#define uchar unsigned char"
"	"
"char myMSG[] = {\"The world is a beautiful place\n\"}; "
""
"void delay(uchar x);"
"void uart_init();"
""
""
"bit txFlag = 1;"
""
"void main()"
"{"
"	char i = 0;"
"	uart_init();"
"	"
"	while(1)"
"	{"
"		"
"		"
"			if(txFlag)"
"			{"
"				txFlag = 0;"
"				SBUF = myMSG[i];"
"				i++;"
"				if(i==strlen(myMSG))"
"				{"
"					i  = 0;"
"				}"
"				delay(10);"
"			}"
"	"
"	"	
"	"	
"	}"
"}"
""
"void delay(uchar x)"
"{"
"	uchar y;"
"	while(x--)"
"		for(y = 0; y<120; y++);"
"}"
"void uart_init()"
"{"
"	// initialize timer 1 in mode 2(8 bit auto reload)"
"	TMOD = 0x20;"
"	TH1 = 0xfd;"
"	SCON = 0x50;"
"	TR1 = 1;"
"	TI =  0;"
"	//using inteerrupt"
"	EA = 1; // allow all interrupts"
"	ES = 1; // enable serial interrupt"
"	"
"}"
""
""
"void serial_ISR() interrupt 4"
"{"
"	TI = 0;"
"	txFlag = 1;"
"	"
"}"
}; 

void delay(uchar x);
void uart_init();


bit txFlag = 1;

void main()
{
	unsigned int i = 0;
	uart_init();
	
	while(1)
	{
		
		
			if(txFlag)
			{
				txFlag = 0;
				SBUF = myMSG[i];
				i++;
				if(i==strlen(myMSG))
				{
					i  = 0;
				}
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
	//using inteerrupt
	EA = 1; // allow all interrupts
	ES = 1; // enable serial interrupt
	
}


void serial_ISR() interrupt 4
{
	TI = 0;
	txFlag = 1;
	
}
