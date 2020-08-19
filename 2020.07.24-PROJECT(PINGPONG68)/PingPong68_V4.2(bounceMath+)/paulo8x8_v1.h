#include <reg52.h>
#include <string.h>
#include <math.h>
#define uchar unsigned char
//sbit light2=P1^6;
//sbit light3=P1^7;
sbit fcol = P2^6;

sbit row0=P0^0;
sbit row1=P0^1;
sbit row2=P0^2;
sbit row3=P0^3;
sbit row4=P0^4;
sbit row5=P0^5;
sbit row6=P0^6;
sbit row7=P0^7;

uchar value;
uchar ixx;
uchar xdc;
uchar bin;
uchar row,col;
uchar tempbin;
//code uchar bin_row[8];
uchar bin_col[9];
xdata uchar map[8][8]={
{1,1,1,1,1,1,1,1},
{0,0,0,0,0,1,0,0},
{0,0,0,0,0,1,1,0},
{1,1,1,1,1,1,1,1},
{0,0,0,0,0,1,1,0},
{0,0,0,0,0,1,0,0},
{0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1},
};
void resetclock();
void cleararray();
void get_bin(){
	bin = 0;
	//light2=0;
	for(col=0;col<8;col++){
    bin = 0;
		for(row=7;row>=0;row--){
			tempbin = map[row][col]*pow(2,row);
			bin = tempbin+bin;
		}
		bin_col[col] = bin;
	}
//light2=1;
}

void get_col(uchar xcol){
		for(row=7;row>=0;row--){
			bin_col[7-row] = map[row][xcol];
		}
}

void xrow(uchar rr){
	if(rr==0){P0=0x00;}
	if(rr==1){P0=0x80;}
	if(rr==2){P0=0x40;}
	if(rr==3){P0=0x20;}
	if(rr==4){P0=0x10;}
	if(rr==5){P0=0x08;}
	if(rr==6){P0=0x04;}
	if(rr==7){P0=0x02;}
	if(rr==8){P0=0x01;}
}

void xcol(uchar xcc){
/*
1111 1110 0xfe //led1
1111 1101 0xfd //led2
1111 1011 0xfb //led3
1111 0111 0xf7 //led4
1110 1111 0xef //led5
1101 1111 0xdf //led6
1011 1111 0xbf //led7
0111 1111 0x7f //led8
*/	
// if P0 =1
//col 1=off 0=on
if(xcc==8){P2=0xff;}//col0
if(xcc==0){P2=0xfe;}//col1
if(xcc==1){P2=0xfd;}//col2
if(xcc==2){P2=0xfb;}//col3
if(xcc==3){P2=0xf7;}//col4
if(xcc==4){P2=0xef;}//col5
if(xcc==5){P2=0xdf;}//col6
if(xcc==6){P2=0xbf;}//col7
if(xcc==7){P2=0x7f;}//col8
}
/*
void display(){//display row by row
	//light3=0;
	for(col=0;col<=8;col++){
		//P0 = 0xff; // row 1=on , 0=off
		//P0 = bin_col[5];
		//value = bin_col[col];
		//P0 = value;
		//P0 = 255;
		P0=0xff;
		xcol(5);
		xdelay(1);
	}
//light3=1;
}
*/
void disp_col(){
	//uchar xdel;
	for(col=0;col<8;col++){
		//light3=0;
		//get_col();
		for(row=0;row<8;row++){
			bin_col[row] = map[row][col];
			}
		P0=0x00;
		xcol(col);
		if(bin_col[0]==1){row0=1;}
		if(bin_col[1]==1){row1=1;}
		if(bin_col[2]==1){row2=1;}
		if(bin_col[3]==1){row3=1;}
		if(bin_col[4]==1){row4=1;}
		if(bin_col[5]==1){row5=1;}
		if(bin_col[6]==1){row6=1;}
		if(bin_col[7]==1){row7=1;}
		//xdelay();
		//light3=1;
		//xdelay(1);		
	}
}
/*
void display2(){
	for(col=0;col<=8;col++){
		uchar xxr;
		//bin_col[col] = 555;
		//while(xdelay(500)){
			for(xxr=1;xxr<=3;xxr++){
				while(xdelay(500)){
				uchar disp1,disp2,disp3;
				disp1=bin_col[col]/100;
				xsegment(1);
				xdisplay(disp1);
				disp2=(bin_col[col]%100) /10;
				xsegment(2);
				xdisplay(disp2);
				disp3=(bin_col[col]%100)%10;
				xsegment(3);
				xdisplay(disp3);
				P0 = bin_col[col];
				xcol(5);
				//xdelay(100);
				}
		}
	}
}
*/
