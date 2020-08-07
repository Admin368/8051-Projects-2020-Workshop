#include<reg52.h>

sbit dc_motor = P1^0; 
sbit motor_switch = P3^4;
sbit speedUp = P3^6;
sbit speedDown = P3^7;

char dutyCyle = 50;
char period = 10;

void delay(char x);// delay function
	
void main()
{
	
	 while(1)
	 {
			P1 = 0;
			dc_motor=1;
		 	delay(period*(dutyCyle/100));
			dc_motor=0;
			P1 = 0xff;
		  delay(period*((100-dutyCyle)/100));
		 
			if(motor_switch==0)
			{
				delay(20);
				if(motor_switch==0)
				{
					while(motor_switch==0);
					//dc_motor = ~dc_motor;
					P1 = ~P1;
				}
			}
			
			// speed up the motor
			if(speedUp==0)
			{
				delay(20);
				if(speedUp==0)
				{
					dc_motor=1;
					while(speedUp==0);
					
					dutyCyle = dutyCyle<90?(dutyCyle + 10):100;
					
				}
			}
			
			// speed down the motor
			if(speedDown==0)
			{
				delay(20);
				if(speedDown==0)
				{
					//dc_motor=1;
					while(speedUp==0);
					
					if(dutyCyle>10)
					{
						dutyCyle = dutyCyle-10;
					}
					
					
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