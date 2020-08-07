/*written by Nakibinge Simon£¨slemonla13@gmail.com£©, last updated 2020/4/3*/
/*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <reg52.h>
#include <intrins.h>

/** controls  ***/
#define turnOff   P1 = 0xff;


#define speedDown  delay = delay<8?delay+1:8


#define speedUp	   delay = delay>0?delay-1:0

/** controls up ***/
	
static uchar delay =  2;
static uchar rDelay = 8; // random styles delay

static void LEDstylesDelay(uchar x);

/****lighting modes */

#define lightAll P1 = 0x00

void defaultStyle()
{
	P1 = 0x55;
	LEDstylesDelay(delay);
	P1 = ~P1; 
	LEDstylesDelay(delay);
}


void ledChaser()
{
	static uchar chaser = 0xfe;
	
	chaser = _crol_(chaser,1);
	P1 = chaser;
	
	LEDstylesDelay(delay);
	
}


void accumulateLEDs()
{
	static uchar accum = 0xff;
	
	P1 = accum;
	LEDstylesDelay(delay);
	accum <<= 1;
	P1 = accum;
	LEDstylesDelay(delay);
	
	if(accum==0) accum = 0xff;
}

void centerOut()
{

	static uchar kernel = 0xe7;
	
	P1 = ~kernel; 
	LEDstylesDelay(delay);
	
	kernel = kernel & _crol_(kernel,1);
	kernel = kernel & _cror_(kernel,1);
	
	if(kernel==0)
	{		
		P1 = ~kernel; LEDstylesDelay(delay);
		lightAll;      LEDstylesDelay(delay);
		kernel = 0xe7;
		
	}
	
}

void outIn()
{
	static uchar kernel = 0xff;
	kernel = kernel & _crol_(kernel,1);
	kernel = kernel & _cror_(kernel,1);
	
}

void danger()
{
  P1 = P1 == 0x00? 0xff:0x00;
	LEDstylesDelay(delay);
}
void randomMode()
{
	lightAll;       
	defaultStyle();  
	ledChaser(); 		 
	accumulateLEDs();
	centerOut();		 
	danger();				 
}

/** lighting modes up**/



/** file only functions **/
static void LEDstylesDelay(uchar x)
{
	uchar i=0,j=255;
	while(x--)
	{
			for(i=0;i<120;i++)
					while(j--);
					j= 255;
	}
}


