#include <reg52.h>
#include "../../headers/paulobetaX5.c"
// GND TO VCC
// MOTOR TO VCC+ AND DC-
void main(){
	P1 =0;
	xsegment(1);
	xdisplay(0);
	while(1){
			xkey=0;
			xgetfullkey();
			if(xkey==1){
				xdisplay(1);
				P1=1;
			}
			if(xkey==2){
				xdisplay(2);
				P1=0;
			}
			if(xkey==0){
				xdisplay(0);
				P1=0;
			}
	}
}