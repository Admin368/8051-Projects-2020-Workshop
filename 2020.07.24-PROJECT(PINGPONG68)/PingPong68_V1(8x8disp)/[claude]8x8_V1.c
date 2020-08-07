#include <reg52.h>
sbit selectionLatch=P2^7;
sbit dataLatch=P2^6;
sbit led1=P1^0;

code void delay(char x);
code char calc_p0 (char n,char r);
code void display();

code char t=0;
code char check=0;

sbit col0 = P2^0;
sbit col1 = P2^1;
sbit col2 = P2^2;
sbit col3 = P2^3;
sbit col4 = P2^4;
sbit col5 = P2^5;
sbit col6 = P2^6;
sbit col7 = P2^7;
sbit row0 = P0^0;
sbit row1 = P0^1;
sbit row2 = P0^2;
sbit row3 = P0^3;
sbit row4 = P0^4;
sbit row5 = P0^5;
sbit row6 = P0^6;
sbit row7 = P0^7;

 char mat[8][8]={
	{0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,1,1,1,0,0,0},
	{0,0,0,1,0,0,0,0},
};



void main()
{
	while(1)
	{
		display();
		delay(t);
	}
}

void delay(char x)
{
	char y;
	while(x--)
		for(y = 0; y<120; y++);

}

void display()
{
char i;
for(i =0; i<8; i++)
		{
			row7 = calc_p0(i,0);
			row6 = calc_p0(i,1);
			row5 = calc_p0(i,2);
			row4 = calc_p0(i,3);
			row3 = calc_p0(i,4);
			row2 = calc_p0(i,5);
			row1 = calc_p0(i,6);
			row0 = calc_p0(i,7);
			col0 = !mat[i][0];
			col1 = !mat[i][1];
			col2 = !mat[i][2];
			col3 = !mat[i][3];
			col4 = !mat[i][4];
			col5 = !mat[i][5];
			col6 = !mat[i][6];
			col7 = !mat[i][7];
		}
}

char calc_p0 (char n,char r)//n is current mat row, r is loop i
{
char j,sum=0;
for (j=0;j<8;j++)
{
	sum+=mat[n][j];
}
 if ((n ==r) && sum>0)
 {
     return 1;
 }
 else
 {
     return 0;
 }

}

