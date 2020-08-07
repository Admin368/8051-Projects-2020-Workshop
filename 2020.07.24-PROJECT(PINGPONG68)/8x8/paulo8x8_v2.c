#include <reg52.h>
#include <string.h>
#include <math.h>
#define uchar unsigned char


char bin;
char tempbin;
char bin_row[8];
char row,col,ixx;
pdata char hex[8][4];// the binaries in map as 8 hex values
pdata char map[8][8]={
{0,0,0,0,0,1,0,0},
{0,0,0,0,1,1,1,0},
{0,0,0,0,0,1,0,0},
{0,0,0,0,0,1,0,0},
{0,0,0,0,0,1,0,0},
{0,0,0,0,0,1,0,0},
{0,0,1,1,1,1,0,0},
{0,0,0,0,0,0,0,0},
};

void get_bin(){
	bin = 0;
	for(row=0;row<8;row++){
		for(col=0;col<8;col++){
			tempbin = map[row][col]*pow(2,7-col);
			bin = tempbin+bin;
		}
		bin_row[row] = bin;
	}	
}
void giga(char rr){
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

void display(){//display row by row
	for(row=0;row<8;row++){
		//P0 = bin_row[row];
		//P0 = 0xfe; 
		giga(row);
		//P0 = 0xff;
		P2 = 0xff;
		//xdelay(100);
	}
}



void main(){}