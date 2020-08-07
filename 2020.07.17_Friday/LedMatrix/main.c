#include <reg52.h>
#include "..\..\headers\paulobetaX5.c"

void main(){
	char x=00; // led1
	while(1){
	P1=0;
	xseconds(1);
	x = x >> 1;
	P1= x;
	xseconds(1);
	//_cror_
	}
}