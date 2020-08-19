#include <reg52.h>
#include <paulobetaX5.c>
#define uchar unsigned char
uchar debug=0;// use for debugging keys [0=off/1=on]
//11 debug
//12 equals
//13 = minus
//14 = multiplication
//15 = division
//16 = addition

int a,b,c; // integers for calculation
int conv_int; //converted integer
char conv_char; //converted char

uchar i,ixx;
uchar answer;
uchar selector=0; //1-3
uchar value1=0;// value used to calculate
uchar value2=0;// value used to calculate
sbit add=P3^4; // button to add
sbit subtract=P3^5; //button to subtract
sbit multiply=P3^6; //button to multiply
sbit divide=P3^7; // button to divide

int isplit[2]; //split answer in int
uchar jsplit[2]; //array to keep split answer for diplaying on separate segments
uchar jj;// variable for forloop wen splitting

uchar effector; //varible keeping action requested to do on values

// declairing the functions
void debugx();
void ledsignal();
void showresult();
void calculate();
void geteffector();
void getinput();
void display();
int ConvertToInt(char charx);
char ConvertToChar(int intx);
void showsymbol(uchar effector);


void main(){
while(1){
	if(debug==1){
		xkey=0;
		debugx();
	}
	else if(debug==0){
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
			xsegment(1);
			xdisplay(jsplit[0]);
			xsegment(2);
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
if(selector!=1){
	xsegment(1);
	xdisplay(value1);
	//showsymbol(effector);
	xsegment(6);
	xdisplay(value2);
}
else if(selector==1){
	showsymbol(effector);
}
}
void showsymbol(uchar effector){
	switch(effector){
		case 0:case 1://'+'
			xdisplay(20);
			xsegment(3);
			//xdisplay(20);
			P0=0xff;
			P2=0xff;
			xdisplay(21);
			xsegment(4);
			//xdisplay(21);
			break;
		default:
			break;
	}
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
			//SELECTOR0
			if(selector==0){//geting value 1
				if(xkey>9){
					if(xkey>=12){selector=1;return;}
					xkey=0;
				}
				value1=xkey;
			}
			//SELECTOR1
			if(selector==1){//geting effector
				if(xkey<=10){selector=2;return;}
				switch(xkey){
					case 11://debug
						if(debug==1){debug=0;}
						else if(debug==0){debug=1;}
						break;
					case 13://add
						effector=1;
						//selector++;
						return;
					case 14://subtract
						effector=2;
						//selector++;
						return;
					case 15://multiply
						effector=3;
						//selector++;
						return;
					case 16://divide
						effector=4;
						//selector++;
						return;
					default:
						effector=0;
						selector=0;
						return;
				}
			}
			
			//SELECTOR2
			if(selector==2){//getting value 2
				if(xkey>9){
					if(xkey==12){selector=3;return;}
					xkey=0;
				}
				value2=xkey;
			}
	}
}
}

void calculate(){
a = ConvertToInt(value1);
b = ConvertToInt(value2);	
	switch(effector){
		case 1://addittion
			c=a+b;
			break;
		case 2: //subtraction
			c=a-b;
			break;
		case 3: //multiplication
			c=a*b;
			break;
		case 4://division
			c=a/b;
			break;
		default:
				c=0;
	}
/*
if(effector==0){c=a+b;}
if(effector==1){c=a-b;}
if(effector==2){c=a*b;}
if(effector==3){c=a/b;}
*/

isplit[0]= c/10;
isplit[1]= c%10;

//jsplit[0] = 7;
//jsplit[1] = 7;
	
//jsplit[0] = ConvertToChar(6);
//jsplit[1] = ConvertToChar(6);
	
jsplit[0] = ConvertToChar(isplit[0]);
jsplit[1] = ConvertToChar(isplit[1]);
selector = 4; //show result
}

void showresult(){
	xkey=0;
	while(selector==4){
		xgetkey();
		if(xkey>=1){
		selector=0;
		value1=0;
		value2=0;
		answer=0;
		effector=0;
		xresetkey();
		}
		xsegment(3);
		xdisplay(jsplit[0]);
		xsegment(4);
		xdisplay(jsplit[1]);
	}	
}

int ConvertToInt(char charx){
	switch(charx){
		case 0:
			conv_int=0;
			break;
		case 1:
			conv_int=1;
			break;
		case 2:
			conv_int=2;
			break;
		case 3:
			conv_int=3;
			break;
		case 4:
			conv_int=4;
			break;
		case 5:
			conv_int=5;
			break;
		case 6:
			conv_int=6;
			break;
		case 7:
			conv_int=7;
			break;
		case 8:
			conv_int=8;
			break;
		case 9:
			conv_int=9;
			break;
		default:
			conv_int=0;	
	}
return conv_int;
}

char ConvertToChar(int intx){
	switch(intx){
		case 0:
			conv_char=0;
			break;
		case 1:
			conv_char=1;
			break;
		case 2:
			conv_char=2;
			break;
		case 3:
			conv_char=3;
			break;
		case 4:
			conv_char=4;
			break;
		case 5:
			conv_char=5;
			break;
		case 6:
			conv_char=6;
			break;
		case 7:
			conv_char=7;
			break;
		case 8:
			conv_char=8;
			break;
		case 9:
			conv_char=9;
			break;
		default:
			conv_char=0;	
	}
return conv_char;
}
