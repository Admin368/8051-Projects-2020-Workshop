#include<reg52.h>

sbit key1 = P3^4;

void delay(char x); // delay function
void main()
{

	while(1)
	{
		if(key1==0)
		{
			P1=0;
		}
	}
}

void delay(char x) // delay function
{
	char y;
	while(x--)
		for(y=0; y<120; y++);
}