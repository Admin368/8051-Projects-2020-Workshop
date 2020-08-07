/*written by Nakibinge Simon£¨slemonla13@gmail.com£©, last updated 2020/4/3*/
/*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/


#include<reg52.h>
#include "infraredRemConApi.c"
#include "LEDstyles.c"

#define uchar unsigned char


uchar pressedBtn;


void buttonRes(); // response to the pressed button
void controls();  // controls for LEDs

void main()
{
	initInfraredRemCon();
	while(1)
	{
		buttonRes();
	}
}

void buttonRes()
{
		pressedBtn = irCodeDecoder();
	
		switch(pressedBtn)
		{

			case 0:  turnOff;       break;
			case 7:  speedUp;       break;   case 8:  speedDown;   		   break; 
			case 9:  defaultStyle();break;   case 10: randomMode(); 		 break; 
			case 11:                break;    case 12: lightAll;         break; 
			case 13: centerOut();   break;		case 14: accumulateLEDs(); break; 
			case 15: lightAll;      break; 		case 16: accumulateLEDs(); break; 
			case 17: ledChaser();  	break;		case 18: ledChaser();      break;   
			case 19: danger();     	break; 		case 20: ;      				   break;                 
			default: break;       
		}	
}


void controls()
{
	
		if(irCodeDecoder()==7)
		{
			speedUp;
		}
		if(irCodeDecoder()==8)
		{
			speedDown;
		}
		
}

