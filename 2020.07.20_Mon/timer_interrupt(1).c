
#include<reg52.h>

sbit buzzer = P0^7;
sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;

char count =0;
char seconds = 0;
char minutes = 0;

char code segData[] =	   // 0 to 9 codes for segment display
{0x3f,0x06,0x5b,
0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f}; 

char code segment[] =	   // selection choice for one of the 6 display segments
{0xfe,0xfd,0xfb,
0xf7,0xef,0xdf};

void seg_disp(char seconds,char minutes); // display to the 7 segment
void init_timer(); // timer initialization
void delay(char x);// delay function

void main()
{
	init_timer();
	while(1)
	{
		//
		seg_disp(seconds, minutes);
	}
}



void init_timer() // timer initialization
{
	//TMOD
		TMOD = 0x01; // timer 0 in timer mode 1
	//initial value to the timer
		TH0 = (65536-46082)/256;
		TL0 = (65536-46082)%256;	
	//TCON
		TR0 = 1;
	
	// setup interrupt
	EA = 1;
	ET0 = 1;
	
	
}	

void seg_disp(char seconds, char minutes) // display to the 7 segment
{
			char tens, ones;
			char mtens, mones;
			char t = 2; 
	
			tens = seconds/10;
			ones = seconds%10;
	
			mtens = minutes/10;
			mones = minutes%10;
	
			//seconds
			P0 = segment[5];
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = segData[ones]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			P0 = segment[4];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[tens]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			// minutes
			P0 = segment[3];
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = segData[mones]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			P0 = segment[2];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[mtens]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
}
void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}

void timer_0_interrupt() interrupt 1
{
			// reload timer
			TH0 = (65536-46082)/256;
			TL0 = (65536-46082)%256;
			//count time
			count++;
			if(count>=20)
			{
				buzzer = 1;
				delay(10);
				buzzer = 0;
				count = 0;
				
				seconds++;
				if(seconds>4)
				{
						minutes++;
						seconds = 0;
				}
			}
}