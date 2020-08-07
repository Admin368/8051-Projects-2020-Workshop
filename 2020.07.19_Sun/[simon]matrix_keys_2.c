#include<reg52.h>

sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;
char reference;	
void seg_display(char hex);
void delay(char x); // delay function
void main()
{
	char keyCol;
	char keyRow;
	reference = 0xf0;
	P3 = reference;
	while(1)
	{
		P3 = reference;
		if(P3!=reference) // key has been pressed
		{
				//debounce key
				delay(50);
			if(P3!=reference) //indeed key has been pressed
			{
				
				keyCol = P3;
				P3 = ~reference;
				keyRow = P3;
				
				switch(keyCol|keyRow)
				{
					case 0xee:
						seg_display(0x06);
						break;
					case 0xd7:
						seg_display(0x5e);
						break;
					default:
						break;
				}
				
			}
		}
			
			
			
	
	}
}
void seg_display(char hex)
{
	P0 = 0;
	selectionLatch = 1;
	selectionLatch = 0;
	
	P0 = hex; //1--> 0x06,
	dataLatch = 1;
	dataLatch = 0;

}
void delay(char x) // delay function
{
	char y;
	while(x--)
		for(y=0; y<120; y++);
}