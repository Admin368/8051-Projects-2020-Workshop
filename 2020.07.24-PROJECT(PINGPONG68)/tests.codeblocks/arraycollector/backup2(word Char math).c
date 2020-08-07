#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define uchar unsigned char
int xdc;
int bin;
int row,col;
int tempbin;
int bin_row[8];
int map[8][8]={
{1,1,1,1,1,1,1,1},
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
	    printf("ROW[%d] binary array:",row);
        for(xdc=0;xdc<8;xdc++){printf("%d,",map[row][xdc]);}
	    printf("\n");
	    //system("timeout /t 1 >nul");
        bin = 0;
	    printf("bin = [");
        //system("timeout /t 1 >nul");
		for(col=0;col<8;col++){
            printf("[%d]*2^%d +",map[row][col],col);
            //system("timeout /t 1 >null");
			tempbin = map[row][col]*pow(2,7-col);
			bin = tempbin+bin;
		}
		printf("]\n");
		bin_row[row] = bin;
		printf("bin_row[%d] = bin(%d);\n",row,bin);
        printf("Array:");
        for(xdc=0;xdc<8;xdc++){printf("%d,",map[row][xdc]);}
        printf("-->DEC:%d",bin);
        system("pause");
	}
//system("cls");
for(xdc=0;xdc<8;xdc++){printf("%d\n",bin_row[xdc]);}
system("timeout /t 1 >null");
}

int main()
{
    while(1){
        get_bin();
        int ii;
        printf("PRINTING ARRAY\n");
        for(ii=0;ii<8;ii++){
         printf("%d[%c] ",ii,bin_row[ii]);
        }
        printf("Hello world!\n");
        system("timeout /t 4>nul 2>nul");
        system("cls");
        system("timeout /t 4>nul 2>nul");
    }
    return 0;
}
