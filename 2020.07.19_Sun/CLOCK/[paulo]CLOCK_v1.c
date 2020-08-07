#include <reg52.h>
#include <string.h>
#include "..\..\headers\paulobetaX5.c"
sbit rs = P2^3;// REGISTER SELECT
sbit rw = P2^4;//	READ/WRITE
sbit en = P2^5;// READ/WRITE ENABLE
char data1[]={"DATE 2020/07/18"};
char data2[]={"TIME 00:00"};
char pdelay=10;
char x=0;
void lcd_init();//INITIALIZES LCD
void write_com(char com); //WRITE COMMANDS
void write_data(char _data); // WRITE COMMANDS
void main(){
	char i;
	lcd_init();
	xdelay(20);
	while(1){
	//DISPLAY ON LINE 1
	write_com(0x80+17);
	xdelay(10);
	for(i=0;i<=14;i++){
		write_data(data1[i]);
		xdelay(10);
	}
	//DISPLAY ON LINE 2
	write_com(0xc0+17);
	xdelay(10);
		for(i=0;i<=9;i++){
			write_data(data2[i]);
			xdelay(10);
	}
/*
	data2[9]=x+1;
	write_com(0xc0+17);
	xdelay(10);
	for(i=0;i<=9;i++){
		write_data(data2[i]);
		}
		xseconds(1);
*/	
	while(1){}
	}
/*	
	//SHIFTING DATA
	for(i=0;i<12+16-11;i++){
		write_com(0x18);//COM18 SHIFT DATA FROM LEFT TO WRITE
		xdelay(100);
	}	
*/
}
void lcd_init(){
//PREPARE THE SCREEN -16*2 5*7 MATRIX
	write_com(0x38);
//turn on display
	write_com(0x08);
//CLEAR SCREEN
	//write_com(hex of 1);
	write_com(1);
//PREPARE COURSOR  AND DATA POINTER
	//INCREMENT CURSOR AFTER ENTER BY SENTING 0X06
	write_com(0x06);
	write_com(6);
	//write_com(0x80);
	//CURSOR SETUP
	write_com(0x0c);
}

void write_com(char com){
//>TO WRITE DCOMMAND | RS=LOW,RW=LOW ,(SEND DATA),(CREATE PURSE)
//>(SEND DATA) WITH P0;
// delay by 150 nanoseconds "tpw"	
	rw=0 ; rs=0; P0 = com;
	en = 0;
	xdelay(pdelay);
	en = 1;
	xdelay(pdelay);
	en=0;
}
void write_data(char _data){
//>TO WRITE DATA (rs=1,rw=0, datat to P0; then send pulse
	rs=1; rw=0; P0= _data;
	//PULSE
	en = 0;
	xdelay(pdelay);
	en = 1;
	xdelay(pdelay);
	en=0;
}
	

	