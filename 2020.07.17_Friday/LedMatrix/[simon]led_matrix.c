#include <reg52.h>
#include <intrins.h>


char t = 2;
char dig2[2][5]={
{0xc3,0xdf,0xc3,0xfb,0xc3},//P2 
{0x01,0x06,0x08,0x30,0x40} //P0 
};
void delay(char x); // delay function
void main()
{
	char i,j;
	char check=0;
	while(1)
	{
		/*
		P0 = 0xff;
		P2 = 0xfe;
		delay(t);
		P2 = 0;
		P0 = 0x80;
		delay(t);
		*/
		//display two
		for(i =0; i<5; i++)
		{
			P2 = dig2[0][i];
			P0 = dig2[1][i];
			delay(t);
		}
		check ++;
		if(check%10==0)
		{
			for(i =0; i<5; i++)
			{
				dig2[1][i] = _cror_(dig2[1][i],1);
			}
		}
	
	
	}
}

void delay(char x)
{
	char y;
	while(x--)
		for(y = 0; y<120; y++);

}