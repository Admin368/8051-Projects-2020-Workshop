#include <reg52.h>
#include <juliano[io].h> //my code for input&output
#define uchar unsigned char
//CALCULATING KEYS
//13 = add
//14 = minus
//15 = multiply
//16 = divide

/*
STATES
this calculator uses states
state0=inputing value1
state1= selececting acttion ("+"or "-" or "/" or "*"")
state2=inputing value 2
state3=calculating
state4=displaying answer
*/
int a,b,c; // integers for calculation
int conv_int; //converted integer
char conv_char; //converted char

// GENERAL VARIABLES
uchar i,ixx; //variable for forloops
uchar answer; //variable to keep final answer
uchar state=0; //states 0 - state 4
uchar value1=0;// value used to calculate
uchar value2=0;// value used to calculate

//BUTTONS
sbit add=P3^4; // button to add
sbit subtract=P3^5; //button to subtract
sbit multiply=P3^6; //button to multiply
sbit divide=P3^7; // button to divide

// VARIBLES USED FOR SPLITING THE ANSWER TO SHOW ON DIFFERENT SEGMENTS
int isplit[2]; //split answer in int
uchar jsplit[2]; //array to keep split answer for diplaying on separate segments
uchar jj;// variable for forloop wen splitting


//EFFECTOR IS ACTION TO DO ON VALUES
// 1="+",2="-",3"*",4="/"
uchar effector; //varible keeping action requested to do on values

//DECLARING FUNCTIONS
void ledsignal();// shows current states and effector on the leds
//led 1-4 shows states and led 5-8 shows effector
void showresult(); // shows final result
void calculate(); // calcuates the answer
void xgetkey(); // resets keys and checks key press
void display(); //shows numbers on 7segment

/*chose to convert because doing math with characters
was giving undesired results,so i convert to int before calculating
and convert the answer back to char for displaying */
int ConvertToInt(char charx); //converts Characters to integers
char ConvertToChar(int intx); //converst Integers to Character



void main(){ // main function
	while(1){
		xgetkey(); //checks key press
		display(); //displays on 7seg
		ledsignal(); //shows states and effector on leds
		if(state==3){calculate();} //calculates if in state 3
		if(state==4){showresult();} //shows answer if in state 4
	}
}

void ledsignal(){
if(state==1){xled(1);}
if(state==2){xled(2);}
if(state==3){xled(3);}
if(state==4){xled(4);}
if(effector==1){xled(5);}
if(effector==2){xled(6);}
if(effector==3){xled(7);}
if(effector==4){xled(8);}
}

void display(){
	xsegment(1);
	xdisplay(value1);
	xsegment(6);
	xdisplay(value2);
}

void xgetkey(){
  uchar colvalue,rowvalue;
	P3 = 0xf0;//columnCheck gives P3 //11110000
	if(P3 != 0xf0){
		xdelay(10);//verifying button press
		while(P3!=0xf0){/*stays in function as long as you are 
		pressing to avoid changing both value 1 and 2 at the same time*/
			P3 = 0xf0; //collumn check P3= 1111000
			if(P3 != 0xf0){//columnCheck //11110000
			colvalue=~0xf0|P3; //flips the 0to1 and vise vesa
			P3 = 0x0f;//rowCheck //00001111
			rowvalue = ~0x0f|P3;    // checking row
			xprekey = colvalue&rowvalue; /*gives row and column as hex 
			if eg key is from row1 and column one xprekey = 10001000
			which is 0xee in hex.*/
        }
			display();
			ledsignal();
			xtranslatekey(xprekey); //changes the hex to decimal
			if(state==0){
				if(xkey>9){xkey=0;}//stops input to up to 9
				value1=xkey;}//gives the key u pressed to value1
			if(state==1){//geting effector
				switch(xkey){
					case 13://add
						effector=1;
						break;
					case 14://subtract
						effector=2;
						break;
					case 15://multiply
						effector=3;
						break;
					case 16://divide
						effector=4;
						break;
					default:
						effector=0;
						state=0;
						return;
				}
			}
			if(state==2){// select for value 2
				if(xkey>9){xkey=0;} //limit input to 9
				value2=xkey; //gives key you pressed to value2
			}//getting value 2
		}
		//if(state==3){break;}
		state++;// increase state
		if(state>4){
		state=0;
		value1=0;
		value2=0;
		answer=0;
		effector=0;
		}
		xresetkey();
		
	}   
}

void calculate(){
/*convert to in coz calculating characters produced 
undesired incorrect results 
1.convert char to int
2.calculate
3.split
4.convert back to char
*/

//1.CONVERT CHAR TO INT
a = ConvertToInt(value1); //a = converted int of value1
b = ConvertToInt(value2); //b = converted int of value2

//2.CALCULATE
switch(effector){ //is action you selected to happen to values
	case 1://addittion
		c=a+b;
		break;
	case 2: //subtraction
		c=a-b;
		break;
	case 3: //multiplication
		c=a*b;
		break;
	case 4://division
		c=a/b;
		break;
	default:
		c=0;
}

//3.SPLIT
//c is answer in interger data type
isplit[0]= c/10; // splits first part of answer into array isplit[0]
isplit[1]= c%10;// splits second part of answer into array isplit[1]

//4.CONVERT BACK TO CHAR
// isplit is integer array
// jplit is same values but in character array
// converting and spliting the answer back to characters for display
//becasue my display function was designed to only take characters
jsplit[0] = ConvertToChar(isplit[0]); //puts converted answer to character array jsplit[0]
jsplit[1] = ConvertToChar(isplit[1]); //puts converted answer to character array jsplit[0]

state = 4; //changes state to show result
}

void showresult(){
	while(state==4){
		xgetkey(); //checks if u press any key,so that it can stop showing result
		ledsignal();
		xsegment(3); //selects segment 3
		xdisplay(jsplit[0]);//shows 1st split part of answer in above selected segment
		xsegment(4); //selects segement 4
		xdisplay(jsplit[1]);//shows 2nd split part of answer in above selected segment
	}	
}


int ConvertToInt(char charx){ //converts char to int
	switch(charx){
		case 0:
			conv_int=0;
			break;
		case 1:
			conv_int=1;
			break;
		case 2:
			conv_int=2;
			break;
		case 3:
			conv_int=3;
			break;
		case 4:
			conv_int=4;
			break;
		case 5:
			conv_int=5;
			break;
		case 6:
			conv_int=6;
			break;
		case 7:
			conv_int=7;
			break;
		case 8:
			conv_int=8;
			break;
		case 9:
			conv_int=9;
			break;
		default:
			conv_int=0;	
	}
return conv_int;
}

char ConvertToChar(int intx){ //converts int to char
	switch(intx){
		case 0:
			conv_char=0;
			break;
		case 1:
			conv_char=1;
			break;
		case 2:
			conv_char=2;
			break;
		case 3:
			conv_char=3;
			break;
		case 4:
			conv_char=4;
			break;
		case 5:
			conv_char=5;
			break;
		case 6:
			conv_char=6;
			break;
		case 7:
			conv_char=7;
			break;
		case 8:
			conv_char=8;
			break;
		case 9:
			conv_char=9;
			break;
		default:
			conv_char=0;	
	}
return conv_char;
}
