//  The program is an example of Timer0 to implement it.
//  you can select mode0~3 by "#define MODE Mode0~3" 
//  Timer 0 function List:
//      1. Mode 0 : 13-bit timer
//      2. Mode 1 : 16-bit timer
//      3. Mode 2 : 8 -bit auto-reload Timer
//      4. Mode 3 : Timer 0 acts as two independent 8 bit Timers  TL0, TH0. Timer0 and Timer1

#include	<sn8f5829.h>
//#include <SN8F5829.H>
#include "HUMI.h"
#include "DISP.h"
#include "Wifi_Protocol.h"
//=============================================================================
#define 		L_MODEL0  	 0       				// 13-bit timer
#define 		L_MODEL1  	 1       				// 16-bit timer
#define 		L_MODEL2   	 2       				// 8 -bit auto-reload Timer
#define 		L_MODEL3   	 3       				// Timer 0 acts as two independent 8 bit Timers
#define 		L_MODE    	 L_MODEL1   		// select mode of timer0
//=============================================================================
										
#if		L_MODE == L_MODEL0
#define			L_TMOD_VALUE     0x04					//MODE0 13BIT-TIME,Fhosc						
#define			L_TCON0_VALUE		 0x00					//T0:Fclk = Fhosc/128 = 32M/128
#define			L_TH0_VALUE			 0xf8					//L_T0_VALUE = 8192(0x2000) - Fclk * T = 8192 - 32M/128 * 1MS = 7942(0x1806)  高三位需置1	 
#define			L_TL0_VALUE			 0x06					

#elif	L_MODE == L_MODEL1
#define			L_TMOD_VALUE     0x05					//MODE1 16BIT-TIME,Fhosc	
#define			L_TCON0_VALUE		 0x50				  //T0:Fclk = Fhosc/4 = 11.0592M/4			外部晶振11.0592M
#define			L_TH0_VALUE			 0xFD					//L_T0_VALUE = 65536-64874=662   8000HZ=125us
#define			L_TL0_VALUE			 0x6A					

#elif	L_MODE == L_MODEL2			
#define			L_TMOD_VALUE     0x06					//MODE2 8BIT-TIME,Fhosc Auto-reload 
#define			L_TCON0_VALUE		 0x00         //T0:Fclk = Fhosc/128 = 32M/128					
#define			L_TH0_VALUE			 0x06					//L_T0_VALUE = 256(0x100) - Fclk * T = 256 - 32M/128 * 1MS = 6(0x06)
#define			L_TL0_VALUE			 0x06					

#elif	L_MODE == L_MODEL3
#define			L_TMOD_VALUE     0x07					//MODE3,TWO 8BIT-TIME
#define			L_TCON0_VALUE		 0x00    			//T0:Fclk = Fcpu/12 = 16M/12, T0:Fclk = Fhosc/128 = 32M/128	
#define			L_TH0_VALUE			 0x38					//L_TH0_VALUE =L_TL0_VALUE = 256(0x100) - Fclk * T = 256 - 32M/128 * 150US = 56(0x38) 
#define			L_TL0_VALUE			 0x06         //L_TL0_VALUE = 256(0x100) - Fclk * T = 256 - 32M/128 * 1MS = 6(0x06)

#endif



//==============================================================================================//
//xdata unsigned char PULSE_TIME;
#define I0_TX0				P02

idata unsigned char PULSE_TIME = 0;
extern bit F_HUM_AD;
extern bit F_HUMI_Start;
//==============================================================================================//
//  Timer0 init
//==============================================================================================//
void Timer0init(void)
{
  TMOD = L_TMOD_VALUE;          // Mode of Timer 0 
	TCON0 = L_TCON0_VALUE;        // T0EXT = Fhosc.
  TH0 = L_TH0_VALUE;            // Initial values
  TL0 = L_TL0_VALUE;						// T0RATE is Fhosc/128 = 250K	
	TR0 = 1;										  // Timer 0 enable
  ET0 = 1;  
#if	 L_MODE == L_MODEL3					//TWO 8BIT-TIME
	ET1 = 1; 											// Timer 1 isr enable
	TR1 = 1;											// enable Timer 1 Run control
#endif                                                   
}

//==============================================================================================//
//  Timer0 ISR   250US  4K
//==============================================================================================//
void Timer0ISR(void) interrupt ISRTimer0   // Vector @  0x0B
{
#if	  L_MODE == L_MODEL3 				// if Timer0 is Mode 3,The timer TL0 is controlled by T0		
	  TL0 = L_TL0_VALUE;	
#elif L_MODE != L_MODEL2				// if Timer0 is Mode 2, the TL0 will auto reload  
	  TH0 = L_TH0_VALUE;          
		TL0 = L_TL0_VALUE;
#endif	
//==============================================================================================//	
//debug	
//	I0_TX0  ^= 0x01;


//	P23 = 1;
	PULSE_TIME++;
	if(PULSE_TIME>3) 
	{ //1MS
		PULSE_TIME = 0;
	//	Get_Dust_PWM();
		init_rx0count();
		init_rx2count();
	}

	
	if(PULSE_TIME<2) 		
	{
		IO_HumiPulse1=0;	//脉冲0-->4 500us
		IO_HumiPulse0=1;
	}			
	else if(PULSE_TIME<=3) 
	{
		IO_HumiPulse1=1;	//脉冲4-->8,8变为0 500us
		IO_HumiPulse0=0;
	}
//	else
//		PULSE_TIME = 0;
	if(F_HUM_AD)
	{
		if(PULSE_TIME==1)		//1/2--2/3处采样
		{	
			F_HUM_AD = 0;
			F_HUMI_Start =1;
			ADM |= 0x40;

		}
	}	
//	P23 = 0;
}

//==============================================================================================//
//  Timer1 ISR
//==============================================================================================//
#if L_MODE == L_MODEL3
void Timer1ISR(void) interrupt ISRTimer1   // Vector @  0x1B
{ 
    TH0 = L_TH0_VALUE;          // timer1 used

}
#endif
