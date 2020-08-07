#include <reg52.h>
//#include <string.h>
//#include <paulo8x8_v1.h>
//#include <paulobetaX5.c>
//#define uchar unsigned char
	
int clock;// game clock // range [1-100]
int sub_clock; //game sub_clock [100 subclocks form 1 clock]
void calculate_xy(int z); // calculates x,y cordinates to be used to change values in display matrix
void main(){
	while(1){
		for(clock=0;clock<=100;clock++){
			for(sub_clock=0;sub_clock<=100;sub_clock++){
				//get_bin();
				//display();
				}
		}
	}	
}

void calculate_xy(int z){}