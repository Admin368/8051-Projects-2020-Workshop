
 #include<reg52.h>    //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
 #include <intrins.h> //����NOP��ָ���_nop_();
 #include<LCD1602.h>

 #define AddWr 0x90   //д���ݵ�ַ 
 #define AddRd 0x91   //�����ݵ�ַ

 sbit RST=P2^4;   //ʱ�� ���Ϻ���Թص�DS1302оƬ���
 sbit Sda=P2^0;       //�����������Ӷ˿�
 sbit Scl=P2^1;
 sbit dula=P2^6;
 sbit wela=P2^7;

 bit ADFlag;          //����AD������־λ
unsigned char code Datatab[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//7����������ܶ����
data unsigned char  Display[8];//������ʱ����������ֵ
/*------------------------------------------------
                    ��ʱ����
------------------------------------------------*/
 void mDelay(unsigned char j)
 {
  unsigned int i;
  for(;j>0;j--)
     {
	  for(i=0;i<125;i++)
	     {;}
	  }
  }
/*------------------------------------------------
                    ��ʼ����ʱ��1
------------------------------------------------*/
void Init_Timer1(void)
{
 TMOD |= 0x10;			     
 TH1=0xff;	              	/* Init value */
 TL1=0x00;
 //PT1=1;                   /* ���ȼ�    */
 EA=1;                      /* interupt enable */
 ET1=1;                     /* enable timer1 interrupt */
 TR1=1;  
}
/*------------------------------------------------
                    ����IIC����
------------------------------------------------*/
  void Start(void)
  {
   Sda=1;
   _nop_();
   Scl=1;
   _nop_();
   Sda=0;
   _nop_();
   Scl=0;
  }


/*------------------------------------------------
                    ֹͣIIC����
------------------------------------------------*/
  void Stop(void)
  {
   Sda=0;
   _nop_();
   Scl=1;
   _nop_();
   Sda=1;
   _nop_();
   Scl=0;
   }


/*------------------------------------------------
                   Ӧ��IIC����
------------------------------------------------*/
   void Ack(void)
   {
    Sda=0;
	_nop_();
	Scl=1;
	_nop_();
	Scl=0;
	_nop_();
	}


/*------------------------------------------------
                 ��Ӧ��IIC����
------------------------------------------------*/
	void NoAck(void)
	{
	 Sda=1;
	 _nop_();
	 Scl=1;
	 _nop_();
	 Scl=0;
	 _nop_();
	 }


/*------------------------------------------------
              ����һ���ֽ�
------------------------------------------------*/
	 void Send(unsigned char Data)
	 { 
	  unsigned char BitCounter=8;
	  unsigned char temp;

	  do
	    {
		 temp=Data;
		 Scl=0;
		 _nop_();
		 if((temp&0x80)==0x80)
		    Sda=1;
		 else
		    Sda=0;

			Scl=1;
			temp=Data<<1;
			Data=temp;
			BitCounter--;
		  }
	  while(BitCounter);
	      Scl=0;
	  }


/*------------------------------------------------
               ����һ���ֽڲ�����
------------------------------------------------*/
unsigned char _Read(void)
{
	   unsigned char temp=0;
	   unsigned char temp1=0;
	   unsigned char BitCounter=8;

	   Sda=1;
	   do
	     {
		  Scl=0;
          _nop_();
		  Scl=1;
		  _nop_();
		  if(Sda)
		     temp=temp|0x01;
		  else
		     temp=temp&0xfe;

		  if(BitCounter-1)
		     {
			  temp1=temp<<1;
			  temp=temp1;
			  }
			  BitCounter--;
			 }
		while(BitCounter);
		return(temp);
	  }
char Read()
{
	char read=0;
	char check = 0x80;
	char bitCount = 8;
	
	while(bitCount)
	{
		Scl = 0;
		_nop_();
		Scl = 1;
		_nop_();
		if(Sda==1)
		{
			read = read|check;
		}
		check = check>>1;
		bitCount--;
	}
	return read;
}
 
/*------------------------------------------------
                    д��DA��ģת��ֵ
------------------------------------------------*/
	  void DAC(unsigned char Data)
	  {
		   Start();
		   Send(AddWr); //д��оƬ��ַ
		   Ack();
		   Send(0x40);  //д�����λ��ʹ��DAC���
		   Ack();
		   Send(Data);  //д����
		   Ack();
		   Stop();
		 
	   }

/*------------------------------------------------
                 ��ȡADģ��ת����ֵ���з���ֵ
------------------------------------------------*/
	  unsigned char ReadADC(unsigned char Chl)
	  {
       unsigned char Data;
		   Start();        //д��оƬ��ַ
		   Send(AddWr);
		   Ack();
 		   Send(0x40|Chl);//д��ѡ���ͨ����������ֻ�õ������룬��ֲ�����Ҫ�������
		                  //Chl��ֵ�ֱ�Ϊ0��1��2��3���ֱ����1-4ͨ��
		   Ack();
		   Start();
		   Send(AddRd);    //�����ַ
		   Ack();
		   Data=Read();    //������
		   Scl=0;
		   NoAck();
		   Stop();
		   return Data;   //����ֵ
	  }

void cmg(void)//��������溯��		   ��ʱ��DS1302
{
dula=1;
P0=0x00;
dula=0;
wela=1;
P0=0x00;
wela=0;
RST=0;		//		��ʱ��DS1302
}


/*------------------------------------------------
                   ������
------------------------------------------------*/
	void main()
	{

 
	 unsigned char num;                   //DA��ģ�������
	 unsigned char ADtemp;                //�����м����
	 InitLcd();
     mDelay(20);
     Init_Timer1();
	 cmg();                                //���������
	 while(1)
	      { 
           DAC(num);       //DA�����������LEDģ���ѹ�仯
		   num=255;		   //DA��ʱ�����ã���λ255��DA ����ߵ�ƽ������LED_AD������
//		   num++;          //�ۼӣ���256�������Ϊ0������ѭ������ʾ��LED�������𽥱仯
		   mDelay(20);     //��ʱ�������������仯
		   if(ADFlag)      //��ʱ�ɼ�����ģ����
           {
   		ADFlag=0;

   		ADtemp=ReadADC(0);		  //��Ӧ�������ϵ�AD1
		TempData[0]=(ReadADC(0))/50;//����0ͨ����ѹ��ʾ
  		TempData[1]=((ReadADC(0))%50)/10;
 /* 	
        ADtemp=ReadADC(1);		  //��Ӧ�������ϵ�AD2
		TempData[2]=(ReadADC(1))/50;//����1ͨ����ѹ��ʾ ��ͨ����ʱ���Σ������������
  		TempData[3]=((ReadADC(1))%50)/10;
  		
        ADtemp=ReadADC(2);		 //��Ӧ�������ϵ�AD3
		TempData[4]=(ReadADC(2))/50;//����2ͨ����ѹ��ʾ ��ͨ����ʱ���Σ������������
  		TempData[5]=((ReadADC(2))%50)/10;
  		
        ADtemp=ReadADC(3);		 //��Ӧ�������ϵ�AD4
		TempData[6]=(ReadADC(3))/50;//����3ͨ����ѹ��ʾ ��ͨ����ʱ���Σ������������
  		TempData[7]=((ReadADC(4))%50)/10;
*/  		
        disp();
		   }
	   }
	}

/*------------------------------------------------
                   ��ʱ���жϳ���
------------------------------------------------*/
void Timer1_isr(void) interrupt 3 using 1//��ʱ��1ִ������ܶ�̬ɨ��
{

 static unsigned int j;
 TH1=0xfb;		//���¸�ֵ
 TL1=0x00;
 j++;
 if(j==200) 
    {j=0;ADFlag=1;} //��ʱ��λAD������־λ
	 
   // P0=Display[count];//���ڶ�̬ɨ�������
   // P2=count;
   // count++;
  // if(count==8)     //��ʾɨ��8�������
   //   count=0;

 
}
