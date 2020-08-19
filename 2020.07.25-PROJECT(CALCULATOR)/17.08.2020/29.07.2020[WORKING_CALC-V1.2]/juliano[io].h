#include <reg52.h>
#define uchar unsigned char
sbit xsegdef = P2^7;//segment latch
sbit xdigdef = P2^6;//data latch
uchar xsegdelay = 1;//amount delayed after open&close seg latch
uchar xdigdelay = 1;//amount delayed after open&close seg latch
uchar xkey; //value that keeps key pressed in decimal
uchar xprekey;//value of key pressed in hex
void xdelay(uchar xx);//small delay loop    
void xled(uchar ld); //light leds
void xsegment(uchar xseg); //selects segments for display
void xdisplay(uchar xdisp); //sends data to display on segment
uchar xtranslatekey(uchar key); //converts pressed key hex to decimal
void xresetkey(); //resets values of key pressed

void xdelay(uchar xx){//delay function
    uchar xz,zx;
    for (xz=0;xz<xx;xz++){
        for (zx=0;zx<120;zx++){}
    }
}
void xled(uchar ld){// turns on led
        if (ld == 1){P1 = 0xfe;} //led1 = 0xfe;
        if (ld == 2){P1 = 0xfd;} //led2 = 0xfd;
        if (ld == 3){P1 = 0xfb;} //led3 = 0xfb;
        if (ld == 4){P1 = 0xf7;} //led4 = 0xf7;
        if (ld == 5){P1 = 0xef;} //led5 = 0xef;
        if (ld == 6){P1 = 0xdf;} //led6 = 0xdf;
        if (ld == 7){P1 = 0xbf;} //led7 = 0xbf;
        if (ld == 8){P1 = 0x7f;} //led8 = 0x7f;
        if (ld == 0){P1 = 0xff;} //ledalloff = 0xff;
        if (ld == 00){P1 = 0xff;} //ledalloff = 0xff;
        if (ld == 11){P1 = 0x00;} //ledallon = 0x00;
        if (ld == 21){P1 = 0x0f;} //halfon1 = 0x0f;
        if (ld == 22){P1 = 0x0f;} //halfon2 = 0x0f;
}
void xsegment(uchar xseg){//selects segment to dispay on
    switch(xseg)
		{
			case 0:
				P0 = 0xff; //segnone = 0xff;
				break;
			case 1:
				P0 = 0xfe; //seg1 = 0xfe;
				break;
			case 2:
				P0 = 0xfd; //seg2 = 0xfd;
				break;
			case 3:
				P0 = 0xfb; //seg3 = 0xfb;
				break;
			case 4:
				P0 = 0xf7; //seg4 = 0xf7;
				break;
			case 5:
				P0 = 0xef; //seg5 = 0xef;
				break;
			case 6:
				P0 = 0xdf; //seg6 = 0xdf;
				break;
      case 11:
        P0 = 0x00; // segall = 0x00;
			default:
				xsegdef = 0;
				return;
      }
		xdelay(xsegdelay);
    xsegdef = 1; //opens segmet latch
    xsegdef = 0; //closes segment latch
}

void xdisplay(uchar xdisp){//displays digit on 7segment
		char x2disp = xdisp;
    switch(x2disp)
        {  
            case 0:
                P0 = 0x3f; //dig0 = 0x3f;
                break;
            case 1:
                P0 = 0x06; //dig1 = 0x06;
                break;
            case 2:
                P0 = 0x5b; //dig2 = 0x5b;
                break; 
            case 3:
                P0 = 0x4f; //dig3 = 0x4f;
                break;
            case 4:
                P0 = 0x66; //dig4 = 0x66;
                break;
            case 5: 
                P0 = 0x6d; //dig5 = 0x6d;
                break;
            case 6:
                P0 = 0x7d; //dig6 = 0x7d;
                break;
            case 7:
                P0 = 0x07; //dig7 = 0x07;
                break;
            case 8:
                P0 = 0x7f; //dig8 = 0x7f;
                break;
            case 9:
                P0 = 0x6f; //dig9 = 0x6f;
                break;
			case 'n': //displays nothing 
				P0 = 0x08;
				break;
			default:
                return;
        }
    xdigdef = 1; //open data latch
    xdigdef = 0; //close data latch
    xdelay(xdigdelay); //delay to avoid
}

uchar xtranslatekey(uchar xprekey){ //turns hex value to key pressed in decimal
	switch(xprekey){
		  case 0xee:									
			  xkey = 1;
				break;
			case 0xde:									
				xkey = 2;
				break;								
			case 0xbe:									
				xkey = 3;
				break;								
			case 0x7e:									
				xkey = 4;	
				break;
			case 0xed:									
				xkey = 5;	
				break;
			case 0xdd:									
				xkey = 6;	
				break;								
			case 0xbd:									
				xkey = 7;	
				break;								
			case 0x7d:									
				xkey = 8;	
				break;									
			case 0xeb:									
				xkey = 9;
				break;
			case 0xdb:									
				xkey = 0;	
				break;								
			case 0xbb:
				xkey = 11;									
				break;								
			case 0x7b:
				xkey = 12;
				break;
			case 0xe7:
				xkey = 13; //addition
				break;
			case 0xd7:
				xkey = 14;//subtraction			
			  break;								
			case 0xb7:									
				xkey= 15;//multiplication
				break;								
			case 0x77:									
				xkey= 16;//division
				break;								
			default:
				//xkey = 0;
				 break;
		}
return xkey;
}
void xresetkey(){
	P3 = 0xf0;
	xprekey = 0;
	xkey = 0;

}

