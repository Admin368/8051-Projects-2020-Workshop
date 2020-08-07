#include <reg52.h>
//#include <string.h>
//#include <math.h>
#include <paulobetaX5.h>
#include <paulo8x8_v1.h>
#define uchar unsigned char

uchar error=0; // if encounter error=1, if not =0;
sbit light0=P1^7;
sbit light1=P1^6;
sbit light2=P1^5;
sbit light3=P1^4;
sbit light4=P1^3;
sbit light5=P1^2;
sbit light6=P1^1;
sbit light7=P1^0;

uchar xx; // for forloops
uchar cycle;		//game cycle		, 1cycle		= 10clock
uchar clock;     	//game clock 		, 1clock 		= 100milli_clock;
uchar milliclock=0;	//game milliclock 	, 1milliclock 	= 100micro_clock;
uchar microclock=0;	//game microclock	,

//splitter
xdata uchar xsplit[4];

//flags
uchar flag = 1;
uchar xflag=1;
uchar xflag0=1;
uchar xflag1=1;
uchar xflag2=1;
uchar xflag3=1;
// used to know change
uchar oldcycle;
uchar oldclock;
uchar oldmilliclock;
uchar oldmicroclock;

//timer
uchar timer;
uchar oldtimer;
uchar usetimer;

uchar row2draw;// row to draw on
uchar col2draw;// column to draw on

uchar increment=8;//value pushing ball
uchar ball_location=12;// ranges btween [B9 - B49 
uchar old_ball_location;
uchar bottomracket_location; // 6 locations [B1-B6]
uchar topracket_location; // 6 locations [B57-B62]

void debuglights();
void psplit(uchar splitinput); // split input into 3 for display on 7seg
//void showtimer();// shows timer on 7seg
void Xclock(); //increment the clock
void resetXclock();//resets clock
void resetXtimer(); //resets timer
void startXtimer(); //resets and starts timer
void RunXtimer(); //increments timer if usetimer=1;
void stopXtimer(); //stops and resets timer

uchar timerchanged(); 			//check if 1 clock counted 1once
uchar timercounted(uchar ctime);//
void update_ball();//auto moves ball +/- 1row
void move_ball(); //gets input to move ball
void move_bottomracket(); // gets input to move bottom racket
void move_topracket(); //get input to move top racket
void draw(uchar box); // function used to move elements between [B1-B64]
void clear_array();
void error_crash();
void error_checker();//avoid bricking my game
void change_incrememt();


void main(){
	uchar triger = 1;
	xx=0;
	resetXclock();
	while(1){
		Xclock();
		if(triger==1){
			startXtimer();
			timer=1;
			triger=0;
		}
		//showtimer();
		clear_array();
		//move_bottomracket();
		//move_ball();
		update_ball();
		//move_topracket();
		disp_col();
		error_checker();
	}
	error_crash();
}
void update_ball(){
	old_ball_location=ball_location;
	//ball_location=ball_location+increment;
	//xx++;
	//if(xx>=56){xx=0;}
	//if(timer%10==0){ball_location=ball_location+increment;}
	if(milliclock%2==0){ball_location=ball_location+increment;}
	if(ball_location<9){
		ball_location=old_ball_location;
		increment=-(increment);
		ball_location=ball_location+increment;
		}
	if(ball_location>56){
		ball_location=old_ball_location;
		increment= -(increment);
		ball_location=ball_location+increment;
		}
	draw(ball_location);
	//draw(xx);
}
void change_incrememt(uchar change){
	increment=change;
	if(increment<=0){increment=1;}
	if(increment>8){increment=8;}
}

void error_checker(){
	if(increment<=0&&increment>8){error=2;return;}//Error2 increment out of bound
	if(ball_location<9&&ball_location>56){error=3;return;}//Error3 ball out of bound
}

void clear_array(){
	uchar ar,ac;
	for(ar=0;ar<8;ar++){
		for(ac=0;ac<8;ac++){
			map[ar][ac]=0;
		}
	}
}
void error_crash(){
	clear_array();
	//draw 'e'
	draw(36);draw(35);draw(34);
	draw(28);draw(26);draw(20);
	draw(19);draw(18);draw(10);
	draw(4);draw(3);draw(2);
	//draw 'r'

	draw(32);draw(31);draw(30);
	draw(22);draw(14);draw(6);
	for(xx=56;xx<(56+error);xx++){
		draw(xx);
	}
	while(1){
		disp_col();
	}
}
void draw(uchar box){
if(box<=0){error=1;return;}
if(box>64){error=1;return;}
if(box>0&&box<=8){col2draw=1;}
if(box>8&&box<=16){col2draw=2;}
if(box>16&&box<=24){col2draw=3;}
if(box>24&&box<=32){col2draw=4;}
if(box>32&&box<=40){col2draw=5;}
if(box>40&&box<=48){col2draw=6;}
if(box>48&&box<=56){col2draw=7;}
if(box>56&&box<=64){col2draw=8;}
	row2draw=box-(8*(col2draw-1));
	map[row2draw-1][col2draw-1]=1;
}

/*
void showtimer(){
	psplit(microclock);
	xsegment(6);
	xdisplay(xsplit[2]);
	xsegment(5);
	xdisplay(xsplit[1]);
	xsegment(4);
	xdisplay(xsplit[0]);

	psplit(milliclock);
	xsegment(3);
	xdisplay(xsplit[2]);
	xsegment(2);
	xdisplay(xsplit[1]);
	xsegment(1);
	xdisplay(xsplit[0]);
}
*/
void psplit(uchar splitinput){
	xsplit[0]=splitinput/100;
	xsplit[1]=(splitinput%100)/10;
	xsplit[2]=(splitinput%100)%10;
}
void resetXtimer(){
 timer=0;
 oldtimer=0;
}
void startXtimer(){
	resetXtimer();
 	usetimer=1;
}
void RunXtimer(){
	if(usetimer==1){
		if(oldclock!=clock){
			oldtimer=timer;
			timer++;
			if(timer==254){timer=0;}
		}
	}
}
void stopXtimer(){
	usetimer=0;
	resetXtimer();
}

uchar timerchanged(){
	if(timer!=oldtimer){return 1;}
	else if(timer==oldtimer){return 0;}
}

uchar timercounted(uchar ctime){
	if(ctime-timer==0){return 1;}
	else if(ctime-timer!=0){return 0;}
}

void Xclock(){
microclock++;
if(microclock==100){microclock=0;oldmilliclock=milliclock;milliclock++;}
if(milliclock==100){milliclock=0;oldclock=clock;clock++;}
if(clock==10){clock=0;oldcycle=cycle;cycle++;}
if(cycle==254){cycle=0;}
//if(cycle==254){resetXclock();}
//debuglights();
//RunXtimer();
}

void debuglights(){
if(milliclock!=oldmilliclock){
	xflag3 = ~xflag3;
}
if(xflag3 == flag){light3=1;}
else if(xflag3 == ~flag){light3=0;}

if(microclock!=oldmicroclock){xflag2 = ~xflag2;if(xflag2 == flag){light2=1;}else if(xflag2 == ~flag){light2=0;}}
if(clock!=oldclock){xflag1 = ~xflag1;if(xflag1 == flag){light1=1;}else if(xflag1 == ~flag){light1=0;}}
if(cycle!=oldcycle){xflag0 = ~xflag0;if(xflag0 == flag){light0=1;}else if(xflag0 == ~flag){light0=0;};xbeep();}

}
void resetXclock(){
	microclock=0;
	milliclock=0;
	clock=0;
	cycle=0;
	oldmicroclock=0;
	oldmilliclock=0;
	oldclock=0;
	oldcycle=0;
}