#include <reg52.h>
#include "..\_OwnMadeStcHeaderFiles\paulobetax3.c"
#define uchar unsigned char
	
void main(){
	uchar bX;
	while(1){
		for(bX=1;bX<7;bX++){
			xled(bX);
			xdigit(bX);
			xsegment(bX);
			xseconds(1);
		}
	}
}