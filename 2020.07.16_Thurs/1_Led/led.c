#include<reg52.h>
#include "..\..\headers\paulobetaX5.c"
void main(){
	int px;
	while(1){
		for(px=0;px<8;px++){
		xled(px);
		xseconds(1);
		xled(0);
		xseconds(1);
		}
	}
}
