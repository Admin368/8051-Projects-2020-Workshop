#include <reg52.h>
#include "../../headers/paulobetaX5.c"
// GND TO VCC
// MOTOR TO VCC+ AND DC-
sbit dc_motor = P0;
void main(){
	dc_motor =0;
	xsegment(1);
	xdisplay(0);
	while(1){
			xkey=0;
			xgetfullkey();
			if(xkey==1){
				xdisplay(1);
				//dc_motor=1;
			}
			if(xkey==2){
				xdisplay(2);
				//dc_motor=1;
			}
	}
}