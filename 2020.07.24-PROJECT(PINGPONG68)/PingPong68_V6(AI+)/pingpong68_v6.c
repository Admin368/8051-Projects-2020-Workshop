#include <reg52.h>
//#include <string.h>
//#include <math.h>
#include <paulobetaX5.h>
#include <paulo8x8_v1.h>
//#include <gametimerX1.h>
#define uchar unsigned char
//MOVEMENT
char move_method=2;
char rand_char;
char rand_int;
//AI
char AI_MODE=1;
char cal_pos=0; // calculated possition
//keys
sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;

//gamespeed
uchar autospeed;//whether or not to increase speed automatically
uchar highspeed;//higest speed you can go to
uchar Xclock = 0;
char Xclock_old;
uchar XgameSpeed=15;
char Xclock_divider;
char Xclock_Value1,Xclock_Value2;

//implement score
uchar error=0; // if encounter error=1, if not =0;
uchar xx; // for forloops
//flags
uchar forward=1;
uchar flag = 1;
uchar xflag=1;

uchar row2draw;// row to draw on
uchar col2draw;// column to draw on

uchar increment=8;//value pushing ball
uchar ball_location=12;// ranges btween [B9 - B49 
uchar old_ball_location;
uchar bottomracket_location=3; // 6 locations [B1-B6]
uchar topracket_location=59; // 6 locations [B57-B62]

void Xclock_setup();
void Xclock_reset();
void Xclock_init();
void psplit(uchar splitinput); // split input into 3 for display on 7seg
void updateassets();//updates ball+rackets
void update_ball(); //auto moves ball +/- 1row
void bounce_ball(); //bounces ball if hit any surface
void update_bottomracket(); // gets input to move bottom racket
void update_topracket(); //get input to move top racket
void draw(uchar box); // function used to move elements between [B1-B64]
void clear_array();
void error_crash();
void error_checker();//avoid bricking my game
void change_incrememt(uchar change);
void getinput();//checks input from keyboard

char random_num(){
	rand_int=rand()%3;
	return rand_char;
}
void AI_Move(){
	if(ball_location>8&&ball_location<57){
		cal_pos=ball_location%8;
		if(cal_pos==0){cal_pos=8;}
		cal_pos=cal_pos-2;
		switch(move_method){
			case 1://1ST_MOVE_METHOD
				topracket_location=57+cal_pos;
				if(topracket_location>64){topracket_location=64;}
				else if(topracket_location<55){topracket_location=55;}
				break;
			case 2://2ND_MOVE_METHOD
				cal_pos=cal_pos+2;
				if(cal_pos<(topracket_location-56)){topracket_location--;}
				else if(cal_pos>(topracket_location-56)){topracket_location++;}
				if(topracket_location>64){topracket_location=64;}
				else if(topracket_location<55){topracket_location=55;}
				break;
			//default:
		}
	}
}
void AI_Calculate(){
	old_ball_location=ball_location;
	//BOUNCING ON RIGHT_WALL
	if(ball_location==16||ball_location==24||ball_location==32||ball_location==40||ball_location==48||ball_location==56){
		if(forward==1){increment=7;ball_location=ball_location+increment;return;}
		else if(forward==0){increment=-9;ball_location=ball_location+increment;return;}
	}
	//BOUNCING ON LEFT_WALL
	else if(ball_location==9||ball_location==17||ball_location==25||ball_location==33||ball_location==41||ball_location==49){
		if(forward==1){increment=9;ball_location=ball_location+increment;return;}
		else if(forward==0){increment=-7;ball_location=ball_location+increment;return;}
	}
	ball_location=ball_location+increment;
	//BOUNCING ON BOTTOM_RACKET
	if(ball_location==(bottomracket_location)){increment=-9;return;}
	else if(ball_location==(bottomracket_location+1)){increment=-8;return;}
	else if(ball_location==(bottomracket_location+2)){increment=-7;return;}
	//BOUNCING ON TOP_RACKET
	else if(ball_location==(topracket_location)){increment=7;return;}
	else if(ball_location==(topracket_location+1)){increment=8;return;}
	else if(ball_location==(topracket_location+2)){increment=9;return;}

		//BOUNCING ON RIGHT_WALL
	if(ball_location==16||ball_location==24||ball_location==32||ball_location==40||ball_location==48||ball_location==56){
		if(forward==1){increment=7;ball_location=ball_location+increment;return;}
		else if(forward==0){increment=-9;ball_location=ball_location+increment;return;}
	}
	//BOUNCING ON LEFT_WALL
	else if(ball_location==9||ball_location==17||ball_location==25||ball_location==33||ball_location==41||ball_location==49){
		if(forward==1){increment=9;ball_location=ball_location+increment;return;}
		else if(forward==0){increment=-7;ball_location=ball_location+increment;return;}
	}
	ball_location=ball_location+increment;
	//BOUNCING ON BOTTOM_RACKET
	if(ball_location==(bottomracket_location)){increment=-9;return;}
	else if(ball_location==(bottomracket_location+1)){increment=-8;return;}
	else if(ball_location==(bottomracket_location+2)){increment=-7;return;}
	//BOUNCING ON TOP_RACKET
	else if(ball_location==(topracket_location)){increment=7;return;}
	else if(ball_location==(topracket_location+1)){increment=8;return;}
	else if(ball_location==(topracket_location+2)){increment=9;return;}
}

void Xclock_setup(){
//GameSpeed1=1Sec,
//high=faster
XgameSpeed=13;
autospeed=1;
highspeed=20;
Xclock_divider=256;
Xclock_Value1=65536;
Xclock_Value2=46082;
}

void getinput(){

	//while(key1==0||key2==0||key3==0||key4==0){
		if(key1==0){//bottom racket push_left
			bottomracket_location--;
			if(bottomracket_location<=0){bottomracket_location=0;}
			else if(bottomracket_location>=8){bottomracket_location=8;}
			//break;
		}
		else if(key2==0){//bottom racket push_right
			bottomracket_location++;
			if(bottomracket_location<=0){bottomracket_location=0;}
			else if(bottomracket_location>=8){bottomracket_location=8;}
			//break;
		}	
		else if(key3==0){//top racket push_left
			if(AI_MODE==0){	
				topracket_location--;
				if(topracket_location<=55){topracket_location=55;}
				else if(topracket_location>=64){topracket_location=64;}
			}
		}
		else if(key4==0){//top racket push_right
			if(AI_MODE==0){	
				topracket_location++;
				if(topracket_location<=55){topracket_location=55;}
				else if(topracket_location>=64){topracket_location=64;}
			}
		}
		//while(1){
		while(key1==0||key2==0||key3==0||key4==0){
			clear_array();
			updateassets();
			disp_col();
		}
	//}
}

void check_score(){
// CHECKING IF WIN OR LOST
	if(ball_location<=8){error=10;error_crash();}//lost
	else if(ball_location>=64){error=20;error_crash();}//won
}

void main(){
	Xclock_init();// initiates SysClock+interupt [GameClock]
	while(error==0){
		getinput();
		clear_array();
		updateassets();
		//draw(ball_location);
		disp_col();
		error_checker();
	}
	error_crash();
}

void update_bottomracket(){
	uchar limit=3;
	switch(bottomracket_location){
		case -1://racket out of  bound on left
			draw(1);
			break;
		case 0://racket out of  bound on left
			draw(1);draw(2);
			break;
		case 7://racket out of  bound on right
			draw(7);draw(8);
			break;
		case 8://racket out of  bound on right
			draw(8);
			break;
		default:
			for(xx=0;xx<3;xx++){
				draw((bottomracket_location)+xx);
			}
	}
}

void update_topracket(){
	switch(topracket_location){
		case 55:
			draw(57);
			break;
		case 56:
			draw(57);draw(58);
			break;
		case 63:
			draw(63);draw(64);
			break;
		case 64:
			draw(64);
			break;
		default:
			for(xx=0;xx<3;xx++){
				draw((topracket_location)+xx);
			}
	}
} 

void updateassets(){//updates ball and all rackats on screen
	update_bottomracket(); //print bottomracket
	draw(ball_location);//prints ball in array
	update_topracket();//print top racket
}

void update_ball(){
	// SAVING PREV BOUNCE LOCATION
	old_ball_location=ball_location;
	// BOUNCING BALL
	bounce_ball();
	
	// TOP RACKET
	// MOVING BALL +/- 1 ROW
	//ball_location=ball_location+increment;
	
	// BOTTOM RACKET
	if(ball_location==(bottomracket_location)||ball_location==(bottomracket_location+1)||ball_location==(bottomracket_location+2)){
		ball_location=old_ball_location;
		increment=-(increment);//REVERSE BALL DIRECTION
		forward=1;//FLAG FOR BALL DIRECTION GOING FORWARD
		ball_location=ball_location+increment;
		//AI_Calculate();
		//check_score();
		return;
		//break;
	}
	// TOP RACKET
	else if(ball_location==(topracket_location)||ball_location==(topracket_location+1)||ball_location==(topracket_location+2)){
		ball_location=old_ball_location;
		increment= -(increment);//REVERSE BALL DIRECTION
		forward=0;//FLAG FOR BALL DIRECTION GOING BACKWARDS
		ball_location=ball_location+increment;
		//check_score();
		return;
		//break;
	}
	//ball_location=ball_location+increment;
	//check_score();
}

void bounce_ball(){

	//BOUNCING ON RIGHT_WALL
	if(ball_location==16||ball_location==24||ball_location==32||ball_location==40||ball_location==48||ball_location==56){
		if(forward==1){increment=7;ball_location=ball_location+increment;return;}
		else if(forward==0){increment=-9;ball_location=ball_location+increment;return;}
	}
	//BOUNCING ON LEFT_WALL
	else if(ball_location==9||ball_location==17||ball_location==25||ball_location==33||ball_location==41||ball_location==49){
		if(forward==1){increment=9;ball_location=ball_location+increment;return;}
		else if(forward==0){increment=-7;ball_location=ball_location+increment;return;}
	}
	ball_location=ball_location+increment;
	/*
	//BOUNCING ON BOTTOM_RACKET
	if(ball_location==(bottomracket_location)){increment=-9;return;}
	else if(ball_location==(bottomracket_location+1)){increment=-8;return;}
	else if(ball_location==(bottomracket_location+2)){increment=-7;return;}
	//BOUNCING ON TOP_RACKET
	else if(ball_location==(topracket_location)){increment=7;return;}
	else if(ball_location==(topracket_location+1)){increment=8;return;}
	else if(ball_location==(topracket_location+2)){increment=9;return;}
	*/
	//BOUNCING ON BOTTOM_RACKET
	if(ball_location==(bottomracket_location)){increment=-9;}
	else if(ball_location==(bottomracket_location+1)){increment=-8;}
	else if(ball_location==(bottomracket_location+2)){increment=-7;}
	//BOUNCING ON TOP_RACKET
	else if(ball_location==(topracket_location)){increment=7;if(xflag==flag){XgameSpeed++;}}
	else if(ball_location==(topracket_location+1)){increment=8;if(xflag==flag){XgameSpeed++;}}
	else if(ball_location==(topracket_location+2)){increment=9;if(xflag==flag){XgameSpeed++;}}
	if(XgameSpeed>=20){XgameSpeed=20;}
	return;
}

void change_incrememt(uchar change){
	increment=change;
	if(increment<=0){increment=1;}
	if(increment>9){increment=9;}
}

void error_checker(){
	if(increment<=0&&increment>8){error=2;return;}//Error2 increment out of bound
	//if(ball_location<9&&ball_location>56){error=3;return;}//Error3 ball out of bound
	//if(ball_location<1){error=10;return;}//lost
	//else if(ball_location>64){error=20;return;}//won

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
	switch(error){
		case 10://lost game
			clear_array();
			for(xx=3;xx<=59;xx+=8){draw(xx);}
			for(xx=4;xx<=8;xx+=1){draw(xx);}
			xled(11);
			while(1){
				disp_col();
			}
			break;	
		case 20://won game
			while(1){
				clear_array();
				for(xx=1;xx<=64;xx++){
					draw(xx);
					disp_col();
					//xdelay(1);
				}
			}
			break;
		default://general Error
			//error
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
	
	
}
void draw(uchar box){
if(box<1){error=4;return;}
if(box>64){error=4;return;}
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



void Xclock_reset(){
	TH0=(Xclock_Value1-Xclock_Value2)/Xclock_divider;
	TL0=(Xclock_Value1-Xclock_Value2)%Xclock_divider;
}

void Xclock_init(){
	Xclock_setup();
	TMOD = 0x01; //TIMER MODE1
	Xclock_reset();//RESETS TIMER
	TR0 = 1; //STARTS TIMER
	//ENABLE INTERUPT
	EA = 1; //CPU INTERUPT ENABLE
	ET0 = 1; //ENABLE TIMER 0
}

void Xclock_interupt() interrupt 1 {
	Xclock_reset(); //RESET CLOCK
	Xclock++; // increament count
	if(Xclock>=254){Xclock=0;}
	//if(Xclock==(1*XgameSpeed)){//20 = 1 sec
	//if(Xclock==20/XgameSpeed){//GameSpeed
	if(Xclock==(21-XgameSpeed)){ //6 is okay speed
	//if( (Xclock%(3))==0){//GameSpeed
	//if(Xclock%(1)==0){
		xflag = ~xflag;
		if(xflag==flag){
			//P1=0xfe;
		}
		else if(xflag!=flag){
			P1=0xff;
		}
		if(AI_MODE==1){AI_Move();}
		//ball_location=bottomracket_location+9;
		update_ball();
		check_score();
		Xclock=0;
		//disp_col();
	}
	//GAME IF STATEMENTS
	//if(Gseconds%30==0){XgameSpeed=XgameSpeed+1;if(XgameSpeed>=20){XgameSpeed=20;}}//every 30 sec increase game speed
	//if(Xclock>=20){Xclock=0;}
	//GET_CONTROLS	
}
