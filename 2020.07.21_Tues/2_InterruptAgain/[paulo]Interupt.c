#include <reg52.h>
//#include "../../headers/paulobetaX6.c"
char count =0;
sbit buzzer = P0^7;
void timer0_init();
void timer0_pull();
void delay(char x);
void main(){
	buzzer = 0;
	timer0_init();
	while(1){
			timer0_pull();
		}
}

void timer0_init(){ //if we repeat this process 20 times its 1 sec
	//SET THE TMODE REGISTER
	TMOD = 0x01;
	//INIT THE TIMER
	TH0 = (65536-46082)/256;
	TL0 = (65536-46082)%256;
	//START TIMER
	TR0=1;
	//WEN EVER IT OVERFLOWS IT INCREMENTS COUNT
}

void timer0_pull(){
	while(TF0==0);
	TF0 = 0; //reset overflow flag
	count++;// increment count
	if(count==20){
				count=0;//timer 0 has counted up to 1 sec
				buzzer=1;
				delay(5);
				buzzer=0;
				//after this we need to reload timer0init with same value
	}
}

void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}

void setup_interrupt(){//SETUP TIMER 0 INTERRUPT
	EA = 1; //ALLOW ALL CPU INTERUPTS
	ET0 = 1; //ENABLE TIMER 0 INTERRUPT
	//MAKE SURE ITS ENABLED BEFORE INFITNE LOOP
	//set EA AS 1 
	//TIMER 0 ET0 TIMER 1
	//TIMER 1 E
}

//after interrupt is done it goes back to what ever it was doing
void timer0_interrupt() interrupt 1{// interrupt service routine
				count=0;//timer 0 has counted up to 1 sec
				P1=0x00;
				buzzer=1;
				delay(5);
				P1=0xff;
				buzzer=0;
}