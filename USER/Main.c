//Program Size: data=9.0 xdata=52 code=152
//HexConvertVer = V22
//CheckSum = 0x4BA7
//2018.08.30_V1.0

#define __XRAM_SFR_H__	
#include	<sn8f5829.h>
#include	"Main.h"
#include "Wifi_Protocol.h"
extern bit F_Time_10ms;
u8 Counter_MS = 0;
void myTimer();
void Delay1ms(unsigned int a)		//����aΪ��ʽ����;�ڵ��ñ�����ʱ�ṩ��������,��:delay30ms(5)��ʾҪ��ʱ30ms*5=150ms	[ϵͳƵ�ʱ�����޸ĵ�λ��]
{
	unsigned int i;

	while(a)				//while( )ѭ���ṹ;����a>0�Ž���ѭ����;��a=0ʱ����������,��ִ�����,��ʱ����	
	{
		for(i=0;i<300;i++)
		{
			WDTR = 0x5A; 		//������Ź�������,��û������λ�Ļ�,˵�����Ź��ļ�ʱʱ�䳬�����ϵ���ʱ30ms
			
		}
		a--;				//�ݼ�
		
	}
}
//=============================================================================================================//
//main loop
//=============================================================================================================//
void main(void)
{ 
	u16 i = 0;
	Delay1ms(200);

	Systeminit();	
	Timer0init();
	Timer2init();
	UART0init();
	UART2init();
	InitAD();
	HumiInit();
	LED_Init();
	HumCTL_Init();
	EAL = 1;  										// Golbal Interrupt enable
	WIFItxDataSet();
  while(1) 
	{
    WDTR = 0x5A;                // clear watchdog if watchdog enable
		if(F_Time_10ms == 1)
		{
			i++;
			F_Time_10ms = 0;		
			ReadAirTempreture();
			StarHUMIAD();		
			LED_Task();
			HumiTestNoWater();
			if(i % 10 == 0)//100ms
			{
				deCode();
				myTimer();
				txDataSet();
				WIFItxDataSet();
				WIFIdeCode();
			}
			if(i >= 100)//1s
			{
				i = 0;				
				myTimer();
			}
		}
	//	P24 = 1;
		get_HUMID();
	//	P24 = 0;
  }
}

//==============================================================================================//
//  Systeminit
//==============================================================================================//
void Systeminit(void)
{
//ϵͳʱ�ӼĴ���,From�����16M
//====================================================================================//	
	CLKSEL = 0x87;		//flosc=internal 16khz RC(ILRC)//fcpu=fosc/1 = 32Mhz			11.0592M
	CLKCMD = 0x69;
	CKCON = 0x10;			//IROM fetching cycle = fcpu/(PWSC[2:0]+1) = 16Mhz				11.0592M/2

//�忴�Ź�
//====================================================================================//	
	WDTR = 0x5A;                   									 // clear watchdog 
	
//GPIO��ʼ��,	P30,P31���Զ�ʱʱ��
//====================================================================================//	
	P0 = 0;
	P0M = 0;
	P0M |= 0x20;// 0 ���� 1���
	P0M |= 0x40;
	P0UR = 0x00;

	P1 = 0;																															
	P1M = 0xff;
	P1UR = 0x00;

	P2 = 0;
	P2M = 0;
	P2M |= 0x08;
	P2M |= 0x10;
	P2UR = 0xff;

	P3 = 0;																					//P30,P31��ⶨʱʱ��
	P3M = 0x03;
	P3UR = 0xfc;
				
	P4 = 0;
	P4M = 0;						
	P4UR = 0xff;		
	
	P5UR = 0xF1;
	P5 = 0x00;
	P5M = 0x00;
	
	P6 = 0;
	P6M = 0x00;																	
	P6UR = 0xff;	
	
	P7 = 0;
	P7M = 0;							
	P7UR = 0xff;			
}
