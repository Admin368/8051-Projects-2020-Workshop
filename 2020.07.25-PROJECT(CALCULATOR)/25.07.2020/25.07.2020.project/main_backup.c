#include<reg52.h>
// #include <paulobetaX5.c>
#define uchar unsigned char

sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;
// display the segment
sbit mySeg1 = P0^0;
sbit mySeg2 = P0^1;
sbit mySeg3 = P0^2;
sbit mySeg4 = P0^3;
sbit mySeg5 = P0^4;
sbit mySeg6 = P0^5;

char reference;	
char mySeg;
char time= 1;
void seg_display(char hex);
void seg_display2(char hex2);
void send_num();
void calcutator(unsigned char);
void delay(char x); // delay function
void main()
{
	
	char keyCol;
	char keyRow;
	mySeg= mySeg1;
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
					//1st keyb 
					case 0xee:
						seg_display(0x06);
						break;
				
					
					//2sd keyb	
					case 0xde:
						seg_display(0x5b);
						break;
					
					//3th keyb
					case 0xbe:
						seg_display(0x4f);
						break;
					
					//4th keyb
					case 0x7e:
						seg_display(0x66);
						break;
					//5th  keyb
						case 0xed:
						seg_display(0x6d);
						break;						
					//6th keyb 
					case 0xdd:
						seg_display(0x7d);
						break;
			  	//7th keyb
					case 0xbd:
						seg_display(0x07);
						break;
					//8th keyb
					case 0x7d:
						seg_display(0x7f);
						break;
					//9th keyb
					case 0xeb:
						seg_display(0x6f);
						break;
					//10th keyb
					case 0x3f:
						seg_display(0x06);
						break;
					//11th keyb
					case 0xbb:
						seg_display(0x06);
						break;
					//12th keyb
					case 0x7b:
						seg_display(0x06);
						break;
					//13th keyb
					case 0xe7:
						seg_display(0x06);
						break;
					//14th keyb
					case 0xd7:
						seg_display(0x06);
						break;
					//15th keyb
					case 0xb7:
						seg_display(0x06);
						break;
					//16th keyb
					case 0x77:
						seg_display(0x06);
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
	/*P0 = 0;
	selectionLatch = 1;
	selectionLatch = 0;
	
	P0 = hex; //1--> 0x06,
	dataLatch = 1;
	dataLatch = 0;
	*/

while(1){
		P0 = 0xff;
	mySeg1 = 0;
	selectionLatch = 1;
	selectionLatch = 0;
delay(time);
	
	  P0 = hex; 
	dataLatch = 1;
	dataLatch = 0;
	
delay(time);
	
	  	P0 = 0xff;
		mySeg2 = 0;
		selectionLatch = 1;
		selectionLatch = 0;
		
		P0 = hex; 
		dataLatch = 1;
		dataLatch = 0;
	
		delay(time);
	
		P0 = 0xff;
		mySeg3 = 0;
		selectionLatch = 1;
		selectionLatch = 0;
		
		P0 = 0x5b; 
		dataLatch = 1;
		dataLatch = 0;
	
	
		delay(time);
	
			P0 = 0xff;
			mySeg4 = 0;
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = 0x4f; 
			dataLatch = 1;
			dataLatch = 0;
			
			delay(time);
	
			P0 = 0xf7;
			mySeg4 = 0;
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = hex; 
			dataLatch = 1;
			dataLatch = 0;
	}
						
}
	
 void send_num()
 {
	 int i;
	 int num[6];
	 int selector=0;
	 int num_click=0;
	 if(num<6)
		 {
		 
	 num[selector]=num_click;selector++;
 }
	 for(i=0;i<selector;i++){
		 
		 
	 }
 }
	
 
	/*mySeg2 = 0;
	selectionLatch = 1;
	selectionLatch = 0;
	
	mySeg2 = hex; //1--> 0x06,
	dataLatch = 1;
	dataLatch = 0;
*/	
	



void delay(char x) // delay function
{
	char y;
	while(x--)
		for(y=0; y<120; y++);
}