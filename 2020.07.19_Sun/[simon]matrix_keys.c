#include<reg52.h>

char reference;	
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
						P1 = 0xfc;
						break;
					case 0xd7:
						P1 = 0x3f;
						break;
					default:
						break;
				}
				
			}
		}
			
			
			
	
	}
}

void delay(char x) // delay function
{
	char y;
	while(x--)
		for(y=0; y<120; y++);
}