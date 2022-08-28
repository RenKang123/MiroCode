
#include	<sn8f5829.h>
#include "Timer2.h" 

#define I0_TX2			P13


bit F_Time_10ms;

//==============================================================================================//
//  Timer2 init
//==============================================================================================//
void Timer2init(void)
{
	T2CH = L_T2CH_VALUE;            				// Initial values 定时2MS
  T2CL = L_T2CL_VALUE;						
	
	CPTCH = L_T2CH_VALUE;										//T2CH 重载值							
	CPTCL = L_T2CL_VALUE;										//T2CL 重载值				
	
	T2M = L_T2_FCKS_FOSC | L_T2_CLK_DIV64 | L_T2_TIMER_OVERFLOW;
	T2M |= L_T2_EN;
			
	CPTM = 0x00; 														//关闭测量功能
  IEN2 |= 0x10 ;      										//使能T2中断                                              
}

//==============================================================================================//
//  Timer2 ISR  T2CH,T2CL自动重载CPTCH,CPTCL的值
//==============================================================================================//
void Timer2ISR(void) interrupt ISRTimer2   
{ 
//	P24 = 1;
	F_Time_10ms = 1;
//	P24 = 0;
//	P23 = ~P23;
//	P24 = ~P24;
	
//	I0_TX2  ^= 0x01;
	

}		