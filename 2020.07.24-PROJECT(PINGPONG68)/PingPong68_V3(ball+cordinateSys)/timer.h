#include<reg52.h>

sbit buzzer = P0^7; 
char count = 0;

void timer0_init(); // timer 0 initialization

void setup_interr(); // sets up timer 0 interrupt

void delay(char x);// delay function 
	
void main()
{
	buzzer = 0;
	timer0_init();
	setup_interr();
	while(1)
	{}	
}

void timer0_init()
{
	//Set the TMOD register
	TMOD = 0x01; // timer 0 in timer mode 1
	//initialize the timer
	TH0 = (65536-46082)/256;
	TL0 = (65536-46082)%256;
	//start the timer
	TR0 = 1; // start the timer
}

void setup_interr() // sets up timer 0 interrupt
{
	EA = 1; //allow all CPU interrupts
	ET0 = 1; // enable timer 0 interrrupt
}
void timer_0_ISR() interrupt 1 // interrupt service routine
{
	// reload timer 0
	TH0 = (65536-46082)/256;
	TL0 = (65536-46082)%256;
	
	count++; // increament count
	if(count==20)
	{
		//timer 0 has counted upto 1 second
		count = 0;
		buzzer = 1;
		delay(10);
		buzzer = 0;	
		
	}
}
