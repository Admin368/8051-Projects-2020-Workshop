#include <reg52.h>
#include <paulobetaX5.c>
#define uchar unsigned char
uchar i,ixx;
uchar selector=0; //1-3
uchar counter=0;
uchar delayx=0;
uchar megaclock=0; //1megaclock = 100clocks 
uchar clock=0;  // 1clock = 100milliclocks
uchar milliclock=0;//1milliclock = 100microclock
uchar microclock=0;//microclcok >=100,++;
uchar flag;
uchar value1=0;
uchar value2=0;
void xclock();
void getinput();
void display();
void main(){
	while(1){
			xclock();
			xgetkey();
			display();
			
			//if(flag==clock%2){flag++;}
			//if(flag>=4){flag=1;}
		}
}


void getinput(){
	xresetkey();
	xgetfullkey();//give us variable xkey of what user is pressing
		
}
void display(){
	xsegment(1);
	xdisplay(value1);
	xsegment(6);
	xdisplay(value2);
}

void displayold(){
		xsegment(6);
		xdisplay(microclock);
		xdelay(delayx);
		xsegment(5);
		xdisplay(milliclock);
		xdelay(delayx);
		xsegment(4);
		xdisplay(clock);
		xdelay(delayx);
		xsegment(3);
		xdisplay(megaclock);
		xdelay(delayx);
		xsegment(2);
		xdisplay(value1);
		xsegment(1);
		xdisplay(value2);
}
void xclock(){
	microclock++;
	if(microclock>=10){
		microclock=0;
		milliclock++;
	}
	if(milliclock>=10){
		milliclock=0;
		clock++;
	}
	if(clock>=10){
		clock=0;
		milliclock=0;
		microclock=0;
		megaclock++;
	}
	if(megaclock>=10){megaclock=0;}
	
}

void xgetkey(){
    uchar colvalue,rowvalue;
	P3 = 0xf0;//columnCheck //11110000
	if(P3 != 0xf0){
		xdelay(10);//verifying button press
		while(P3!=0xf0){
			P3 = 0xf0;
			if(P3 != 0xf0){//columnCheck //11110000
			colvalue=~0xf0|P3; //flips the 0to1 and vise vesa
			P3 = 0x0f;//rowCheck //00001111
			rowvalue = ~0x0f|P3;    // checking row
			xprekey = colvalue&rowvalue;	
        }
			display();
			xtranslatekey(xprekey);
			if(selector==1){value1=xkey;}
			if(selector==2){value2=xkey;}
		}
		selector++;
		if(selector>=3){selector=0;}
	}   
}

