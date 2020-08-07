#include <reg52.h>
#include <string.h>
#include <math.h>
//#define uchar unsigned char

char bin;
char tempbin;
char bin_row[8];
pdata char row,col,ixx;
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
	for(row=0;row<8;col++){
		for(col=0;col<8;col++){
			tempbin = map[row][col]*pow(2,7-col);
			bin = tempbin+bin;
		}
		bin_row[row] = bin;
	}	
}

void display(){//display row by row
	for(row=0;row<8;col++){
		P0 = bin_row[row];
		P2 = 0;
}
