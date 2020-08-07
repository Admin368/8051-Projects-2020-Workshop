#include<reg52.h>
#include<intrins.h>


sbit Scl = P2^1;
sbit Sda = P2^0;
sbit selectionLatch = P2^7;
sbit dataLatch = P2^6;
sbit buzzer = P3^0;

//unsigned char upperThres = 160; 
unsigned char lowerThres = 50; 

unsigned char code segData[] =	   // 0 to 9 codes for segment display
{0x3f,0x06,0x5b,
0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f}; 

unsigned  char code segment[] =	   // selection choice for one of the 6 display segments
{0xfe,0xfd,0xfb,
0xf7,0xef,0xdf};


void iic_start();     // start condition for data transmision on the IIC protocol           
void iic_send(unsigned char _data); // sending serial data using the IIC protocol
unsigned char iic_read();		// reading serial data using the IIC protocol
void iic_ack(); 		// acknowledge bit after sending a data byte
void iic_noAck(); 	// no acknowledge after receiving the last byte	
void iic_stop();    // stop condition after data transmision on the IIC protocol   
void myDAC(unsigned char _byte); // digital to analog conversion
unsigned char ADC(unsigned char channel); // analog to digital conversion

void delay(char x);// delay function
void seg_disp(char seconds, char minutes); // display to the 7 segment

void warning_alarm(); // make the buzzer produce a warning alarm
	
void main()
{
	unsigned char num = 0;
	unsigned char flag = 0;
	unsigned char count = 0;
	unsigned char channel = 0;
	bit alarmFlag = 0;
	
	buzzer = 0; // turn off buzzer
	num = ADC(channel);
	
	
	
	while(1)
	{
		if(alarmFlag)
		{
		//	warning_alarm(); // warning alarm
		}
		count ++;
		if(count>=100)
		{
				num = ADC(channel); 
			/*
				if(num>=upperThres)
				{
					// turn on the LEDs
					P1 = 0;
				}
			*/
				if(num<=lowerThres)
				{
					// turn on the alarm flag
					alarmFlag = 1;
				}
		}
			
		seg_disp(num,0);
	}
}
void iic_start()
{
	
	Scl = 1;
	_nop_();
	Sda = 1;
	_nop_();
	Sda = 0;
	
}
void iic_send(unsigned char _data)
{
	char oneByte = 8;
	char temp = 0x80; // 1000 0000
	//1000 0000
	//0XXX XXXX
	//1XXX XXXX
	
	while(oneByte)
	{
		Scl = 0;   // added new line 1
		if((temp&_data)==0)
		//if(temp&_data==0) // changed this line 
		{
			Sda = 0;
		}
		else
		{
			Sda = 1;
		}
		Scl = 0;
		_nop_();
		Scl = 1;
		_nop_();  // added new line 2
		Scl = 0;  // added new line 3
		
		_data = _data<<1;
		oneByte--;
	}
	
}

unsigned char iic_read()
{
		 unsigned char check = 0x80;
		 unsigned char read = 0;
		 unsigned char bitCount=8;

	   Sda=1;
	   while(bitCount)
	   {
		  Scl=0;
          _nop_();
		  Scl=1;
		  _nop_();
		  if(Sda==1)
			{
				read = read|check;
			}
			check = check>>1;
			bitCount--;
		}
		return(read);
}

void iic_ack()
{
	Sda = 0;
	Scl = 0;
	_nop_();
	Scl = 1;
	_nop_();
	Scl = 0;
	
}
void iic_noAck()
{
	Scl = 0;
	Sda = 1;
	_nop_();
	Scl = 1;
	_nop_();
	Scl = 0;
	
}
void iic_stop()
{
	Scl = 1;
	_nop_();
	Sda = 0;
	_nop_();
	Sda = 1;
	
}

void myDAC(unsigned char _byte)
{
	iic_start();
	iic_send(0x90); // write to D/A convertor
	iic_ack();
	iic_send(0x40); //enable analog out
	iic_ack();
	iic_send(_byte); // send data
	iic_ack();
	iic_stop();
}	
	


void delay(unsigned char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}


void seg_disp(unsigned char seconds, unsigned char minutes) // display to the 7 segment
{
			char tens, ones;
			char mtens, mones;
			char t = 1; 
	
			tens = seconds/50;
			ones = (seconds%50)/10;
	
			mtens = minutes/10;
			mones = minutes%10;
	
			//seconds
			P0 = segment[5];
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = segData[ones]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			P0 = segment[4];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[tens]|0x80; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			// minutes
			/*
			P0 = segment[3];
			selectionLatch = 1;
			selectionLatch = 0;
			
			P0 = segData[mones]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			P0 = segment[2];
			selectionLatch = 1;
			selectionLatch = 0;
	
			P0 = segData[mtens]; 
			dataLatch = 1;
			dataLatch = 0;
			delay(t);
			*/
}

unsigned char ADC(unsigned char channel)
{
	char readData;
	iic_start();
	iic_send(0x90); // write to D/A convertor
	iic_ack();
	iic_send(0x40|channel); //enable analog out and read from channel
	iic_ack();
	
	iic_start();
	iic_send(0x91); // send read address
	iic_ack();
	readData = iic_read();
	iic_noAck();
	iic_stop();
	return readData;
}	

void warning_alarm() // make the buzzer produce a warning alarm
{
		char t = 30;
	
		buzzer = 1;
		delay(t*3);
		buzzer = 0;
		delay(t);
}
	