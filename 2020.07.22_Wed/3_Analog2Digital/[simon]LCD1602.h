#include<reg52.h>
#include<stdio.h>
#include<intrins.h>

sbit RS = P2^3;//Pin4
sbit RW = P2^4; //Pin5
sbit E  = P2^5;//Pin6


#define Data  P0    //���ݶ˿�

unsigned char TempData[8];

unsigned char  SecondLine[]="                ";
unsigned char  FirstLine[] ="                ";
/******************************************************************/
/*                    ��������                                    */
/******************************************************************/
void DelayUs(unsigned char us)//delay us
{
 unsigned char uscnt;
 uscnt=us>>1;/* Crystal frequency in 12MHz*/
 while(--uscnt);
}
/******************************************************************/
void DelayMs(unsigned char ms)//delay Ms
{
 while(--ms)
   {
     DelayUs(250);
     DelayUs(250);
	 DelayUs(250);
	 DelayUs(250);
   }
}
void WriteCommand(unsigned char c)
{
 DelayMs(5);//short delay before operation
 E=0;
 RS=0;
 RW=0;
 _nop_();
 E=1;
 Data=c;
 E=0;
}
/****************************************************************/
void WriteData(unsigned char c)
{
 DelayMs(5);   //short delay before operation
 E=0;
 RS=1;
 RW=0;
 _nop_();
 E=1;
 Data=c;
 E=0;
 RS=0;
}
/*********************************************************************/
void ShowChar(unsigned char pos,unsigned char c)
{
 unsigned char p;
 if (pos>=0x10)
    p=pos+0xb0; //�ǵڶ�������������4λΪ0xc
 else 
    p=pos+0x80; //�ǵڶ�������������4λΪ0x8
 WriteCommand (p);//write command
 WriteData (c);   //write data
}
/*************************************************************************/
void ShowString (unsigned char line,char *ptr)
{
 unsigned char l,i;
 l=line<<4;
 for (i=0;i<16;i++)
  ShowChar (l++,*(ptr+i));//ѭ����ʾ16���ַ�
}
/*********************************************************************/
void InitLcd()
{
 DelayMs(15);
 WriteCommand(0x38); //display mode
 WriteCommand(0x38); //display mode
 WriteCommand(0x38); //display mode
 WriteCommand(0x06); //��ʾ����ƶ�λ��
 WriteCommand(0x0c); //��ʾ�����������
 WriteCommand(0x01); //��ʾ����

}


/////////////////////////////////////////////////////////////////
void disp(void)

{


 FirstLine[2]='0'+TempData[0];
 FirstLine[4]='0'+TempData[1];
 FirstLine[3]='.';
 FirstLine[6]='V';

 FirstLine[9]='0'+TempData[2];
 FirstLine[11]='0'+TempData[3];
 FirstLine[10]='.';
 FirstLine[13]='V';



 
 SecondLine[2]='0'+TempData[4];
 SecondLine[4]='0'+TempData[5];
 SecondLine[3]='.';
 SecondLine[6]='V';

 SecondLine[9]='0'+TempData[6];
 SecondLine[11]='0'+TempData[7];
 SecondLine[10]='.';
 SecondLine[13]='V';

ShowString(0,FirstLine);

ShowString(1,SecondLine);



}