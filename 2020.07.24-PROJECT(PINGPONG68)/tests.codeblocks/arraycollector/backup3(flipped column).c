#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define uchar unsigned char
uchar xdc;
uchar bin;
uchar row,col;
uchar tempbin;
uchar bin_row[8];
uchar bin_col[8];
uchar map[8][8]={
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
	for(col=0;col<8;col++){
	    printf("Col[%d] binary array:",row);
        for(xdc=7;xdc>=0;xdc--){printf("%d,",map[xdc][col]);}
	    printf("\n");
	    //system("timeout /t 1 >nul");
        bin = 0;
	    printf("bin = [");
        //system("timeout /t 1 >nul");
		for(row=7;row>=0;row--){
            printf("[%d]*2^%d +",map[row][col],row);
            //system("timeout /t 1 >null");
			tempbin = map[row][col]*pow(2,row);
			bin = tempbin+bin;
		}
		printf("]\n");
		bin_col[col] = bin;
		printf("bin_col[%d] = bin(%d);\n",col,bin);
        printf("Array:");
        for(xdc=7;xdc>=0;xdc--){printf("%d,",map[xdc][col]);}
        printf("-->DEC:%d \n",bin);
        system("pause");
	}
//system("cls");
for(xdc=0;xdc<8;xdc++){printf("%d\n",bin_col[xdc]);}

}

int main()
{
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
    return 0;
}
