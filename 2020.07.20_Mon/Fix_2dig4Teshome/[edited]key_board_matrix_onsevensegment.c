/*Display the value corresponding to the key pressed on the keyboard matrix onto the seven 
segment display*/
#include<reg52.h>
sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;
char show2=0; //0 for no and 1 for yes
char  dig1,pos1,dig2,pos2;
char reference;	
void seg_display(char hex,char position);
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
						show2=0;
						seg_display(0x06,0xfe);
						break;
					case 0xde:
						show2=0;
						seg_display(0x5b,0xfd);
						break;
					case 0xbe:
						show2=0;
						seg_display(0x4f,0xfb);
						break;
					case 0x7e:
						show2=0;
						seg_display(0x66,0xf7);
						break;
					case 0xed:
						show2=0;
						seg_display(0x6d,0xef);
						break;
					case 0xdd:
						show2=0;
						seg_display(0x7c,0xdf);
						break;
					case 0xbd:
						show2=0;
						seg_display(0x07,0xfe);
						break;
					case 0x7d:
						show2=0;
						seg_display(0xff,0xfd);
						break;
					case 0xeb:
						show2=0;
						seg_display(0x67,0xfb);
						break;
					case 0xdb://10
						show2=1;
						dig1=0x06;
						pos1=0xf7;
						dig2=0x3f;
						pos2=0xef;
						break;
		      case 0xbb://11
						show2=1;
						dig1=0x06;
						pos1=0xef;
						dig2=0x06;
						pos2=0xdf;
						break;
					case 0x7b://12
						show2=1;
						dig1=0x06;
						pos1=0xfe;
						dig2=0x5b;
						pos2=0xfd;
						break;
					case 0xe7://13
						show2=1;
						dig1=0x06;
						pos1=0xfb;
						dig2=0x4f;
						pos2=0xf7;
						break;
					case 0xd7://14
						show2=1;
						dig1=0x06;
						pos1=0xf7;
						dig2=0x66;
						pos2=0xef;
						break;
					case 0xb7://15
						show2=1;
						dig1=0x06;
						pos1=0xef;
						dig2=0x6d;
						pos2=0xdf;
						break;
					case 0x77://16
						show2=1;
						dig1=0x06;
						pos1=0xfe;
						dig2=0x7c;
						pos2=0xfd;
						break;
					default:
						break;
				}
				
			}
		}	
		if(P3==reference){
			if(show2==1){
				seg_display(dig1,pos1);
				delay(2);
				seg_display(dig2,pos2);
				delay(2);
			}
		}
	}
}
void seg_display(char hex,char position)
{
	P0 = position;
	selectionLatch = 1;
	selectionLatch = 0;
	P0 = hex; 
	dataLatch = 1;
	dataLatch = 0;
}
void delay(char x) // delay function
{
	char y;
	while(x--)
		for(y=0; y<120; y++);
}