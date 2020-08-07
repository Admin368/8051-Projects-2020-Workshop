#include <reg52.h>
#include "..\..\headers\paulobetaX6.c"
void outside_inward();
void center_outward();
void left_accumulation();
void right_accumulation();
void main(){
    while(1){
        xuplevels(~1);
        //outside_inward();
    }
}
void outside_inward(){
    char x=1;
    char y=8;
    while(x<5){
        x++;
        y--;
        xsecondsstatus=1; //resets xseconds status
        while(xsecondsstatus==1){
            xseconds(1);
            while(1){
            xled(x);
            xled(y);
            }
        }
    }
}
void center_outward(){}
void left_accumulation(){}
void right_accumulation(){}

/*
x-y
1-8
2-7
3-6
4-5
*/