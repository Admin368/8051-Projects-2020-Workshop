#include <reg52.h>
#include <paulobetaX5.c>
#define uchar unsigned char
uchar i,ixx;
uchar answer;
uchar selector=0; //1-3
uchar value1=0;
uchar value2=0;
sbit add=P3^4;
sbit subtract=P3^5;
sbit multiply=P3^6;
sbit divide=P3^7;
uchar jsplit[2];
uchar jj;
uchar effector;
void debugx();
void ledsignal();
void showresult();
void calculate();
void geteffector();
void getinput();
void display();
void main(){
	uchar debug=0;
	if(debug==1){
		xkey=0;
		while(1){
			debugx();
		}
	}
	if(debug==0){
		while(1){
				xgetkey();
				display();
				ledsignal();
				if(selector==3){calculate();}
				if(selector==4){showresult();}
			}
	}
}

void debugx(){
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
			xtranslatekey(xprekey);
			jsplit[0]= xkey/10;
			jsplit[1]= xkey%10;
			xsegment(3);
			xdisplay(jsplit[0]);
			xsegment(4);
			xdisplay(jsplit[1]);
		}
	}
			xtranslatekey(xprekey);
			jsplit[0]= xkey/10;
			jsplit[1]= xkey%10;
			xsegment(3);
			xdisplay(jsplit[0]);
			xsegment(4);
			xdisplay(jsplit[1]);
}

void ledsignal(){
if(selector==1){xled(1);}
if(selector==2){xled(2);}
if(selector==3){xled(3);}
if(selector==4){xled(4);}
if(effector==1){xled(5);}
if(effector==2){xled(6);}
if(effector==3){xled(7);}
if(effector==4){xled(8);}
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
			if(selector==0){value1=xkey;}//geting value 1
			if(selector==1){//geting effector
				switch(xkey){
					case 13://add
						effector=1;
						break;
					case 14://subtract
						effector=2;
						break;
					case 15://multiply
						effector=3;
						break;
					case 16://divide
						effector=4;
						break;
					default:
						effector=0;
						selector=0;
						return;
				}
			}
			if(selector==2){
				if(xkey>9){xkey=9;}
				value2=xkey;
			}//getting value 2
		}
		//if(selector==3){break;}
		selector++;
		if(selector>4){
		selector=0;
		value1=0;
		value2=0;
		answer=0;
		effector=0;
		}
		xresetkey();
		
	}   
}

void calculate(){
if(effector==0){answer=value1+value2;}
if(effector==1){answer=value1-value2;}
if(effector==2){answer=value1*value2;}
if(effector==3){answer=value1/value2;}
jsplit[0]= answer/10;
jsplit[1]= answer%10;
selector = 4; //show result
}

void showresult(){
	while(selector==4){
		xgetkey();
		xsegment(3);
		xdisplay(jsplit[0]);
		xsegment(4);
		xdisplay(jsplit[1]);
	}	
}