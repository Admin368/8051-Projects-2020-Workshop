#include<reg52.h>

sbit dc_motor = P1^0; 
sbit relay = P1^7; 
sbit relay_switch = P3^5; 
sbit motor_switch = P3^4;

void delay(char x);// delay function
	
void main()
{
	dc_motor=1;
	relay = 0;
	 while(1)
	 {
			if(motor_switch==0)
			{
				delay(20);
				if(motor_switch==0)
				{
					while(motor_switch==0);
					dc_motor = ~dc_motor;
				}
			}
			
			if(relay_switch==0)
			{
				delay(20);
				if(relay_switch==0)
				{
					while(relay_switch==0);
					relay = ~relay;
				}
			}
			
	 }
}


void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}