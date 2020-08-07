#include <reg52.h>
//#include <string.h>
//#include <math.h>
#include <paulobetaX5.h>
#include <paulo8x8_v1.h>
#define uchar unsigned char

sbit light0=P1^0;
sbit light1=P1^4;
uchar xx;
uchar clock;//game clock ,out of 100;
uchar milliclock;//game milliclock , 1clock = 100milli_clock;
uchar microclock;//game microclock

void main(){
	uchar flag = 1;
	uchar xflag;
	uchar xflag0= flag;
	uchar xflag1= flag;
	uchar xflag2= flag;
	while(1){
		xflag1 = ~xflag1;if(xflag1 == flag){light1=1;}if(xflag1 == ~flag){light1=0;}
		for(clock=0;clock<=10;clock++){
				xflag0 = ~xflag0;if(xflag0 == flag){light0=1;;}if(xflag0 == ~flag){light0=0;}
				for(milliclock=0;milliclock<=100;milliclock++){
					for(microclock=0;microclock<=100;microclock++){
						//get_bin();
						//display();
						disp_col();
					}
				
				}
		}
	}
}