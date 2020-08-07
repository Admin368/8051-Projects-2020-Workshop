#include<reg52.h>

sbit dc_motor = P1^0; 
sbit motor_switch = P3^4;

char dutyCyle = 50;
char period = 10;

void delay(char x);// delay function
	
void main()
{
	
	 while(1)
	 {
			dc_motor=1;
		 	delay(period*(dutyCyle/100));
			dc_motor=0;
		  delay(period*((100-dutyCyle)/100));
		 
			if(motor_switch==0)
			{
				delay(20);
				if(motor_switch==0)
				{
					while(motor_switch==0);
					dc_motor = ~dc_motor;
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