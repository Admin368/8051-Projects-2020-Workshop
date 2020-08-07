#include<reg52.h>
#include<intrins.h>
sbit Scl = P2^1;
sbit Sda = P2^0;

void icc_start();
void icc_send(char _data);
void icc_ack(); 
void icc_stop();
void DAC(char _byte); 

void delay(char x);// delay function
	
void main()
{
	int num = 0;
	char flag = 0;
	
	while(1)
	{
    //DAC(num);//255--> 1111 1111
		DAC(0x0f); // u can put hex or just number(1-255)
		//we can use this and then connect port 
		//DA as positive
		//GROUND as NEG
		//TO CONTROLL ANY VOLTAGE BETWEEN 0-5V EG A 2V CHIP (0x0f) for half
		if(num>=255)
		{
			flag = 1;
		}
		if(num<=0)
		{
			flag = 0;
		}
		
		if(flag==1)
		{
			num--;
		}else
		{
			num++;
		}
		delay(10);
	}
}
void icc_start()
{
	Scl = 1;
	_nop_();
	Sda = 1;
	_nop_();
	Sda = 0;
}
void icc_send(char _data)
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
void icc_ack()
{
	Sda = 0;
	Scl = 0;
	_nop_();
	Scl = 1;
	_nop_();
	Scl = 0;
}
void icc_stop()
{
	Scl = 1;
	_nop_();
	Sda = 0;
	_nop_();
	Sda = 1;
}

void DAC(char _byte)
{
	icc_start();
	icc_send(0x90); // write to D/A convertor
	icc_ack();
	icc_send(0x40); //enable analog out
	icc_ack();
	icc_send(_byte); // send data
	icc_ack();
	icc_stop();
}	
	
void delay(char x)// delay function
{
	char y;
	while(x--)
		for(y =0; y<120; y++);
}