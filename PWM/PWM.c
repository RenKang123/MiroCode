#include "PWM.h"
		
//===============================================================================================================//
//PWM init PWM初始化需先设置周期,在使能PWM,否则PWM无效
//===============================================================================================================//
void PWMinit(void)
{
////PWM1初始化 PWM1 rate is Fosc/32  f_pwm1 = (32M/32)/1000 = 1KHz 
////====================================================================================//	
//	PW1YL = 0xe8;	
//	PW1YH = 0x03;													

//	PW10DL = PW1YL;																					//占空比100%			
//	PW10DH = PW1YH;																														
//	
//	PW11DL = 0xf4;																					//占空比50%
//	PW11DH = 0x01;																					
//													
//	PW12DL = 0x2c;																					//占空比30%
//	PW12DH = 0x01;																			
//														
//	PW13DL = 0x00;																					//占空比0%
//	PW13DH = 0x00;																				

//	PW1M |= L_PWM_CLOCK_32MDIV32 | L_PWMN3_ENABLE | L_PWMN2_ENABLE | L_PWMN1_ENABLE | L_PWMN0_ENABLE;               
//	PW1M |= L_ENABLE_PWMN;	

//	IEN2 &= 0xfd; 
	
	
//PWM2初始化 PWM2 rate is Fosc/8  f_pwm2 = (11.0592M/1)/2764.8 = 4KHz 
//====================================================================================//       
	PW2YH = 2765>>8;														
	PW2YL = 2765;
//4K
	PW20DL = 0x00;
	PW20DH = 0x00;																				//占空0%		
	
//	PW21DH = 0x00;																					//占空比50%			
//	PW21DL = 0xc8;																									

//	PW22DH = 0x00;																					//占空比30%		
//	PW22DL = 0x78;																														

//	PW23DH = 0x00;																					//占空比0%	
//	PW23DL = 0x00;																																

	PW2M |= L_PWM_CLOCK_32MDIV1 | L_PWMN0_ENABLE;     
	PW2M |= L_ENABLE_PWMN; 	
	
	IEN2 &= 0xf7;
	
////PWM3初始化 PWM3 rate is Fhosc/2  f_pwm3 = (32M/2)/160 = 100KHz 
////====================================================================================//	
//	PW3YL = 0xa0;	
//	PW3YH = 0x00;		

//	PW30DL = PW3YL;
//	PW30DH = PW3YL;																				//占空比100%								

//	PW31DL = 0x50;
//	PW31DH = 0x00;																				//占空比50%																	

//	PW32DL = 0x30;	
//	PW32DH = 0x00;																				//占空比30%																

//	PW33DL = 0x00;		
//	PW33DH = 0x00;																				//占空比0%
//	
//	PW3M |= L_PWM_CLOCK_32MDIV2 | L_PWMN3_ENABLE | L_PWMN2_ENABLE | L_PWMN1_ENABLE | L_PWMN0_ENABLE;   	
//	PW3M |= L_ENABLE_PWMN;	
//	IRCON &= 0xef;	

//PWM4初始化 PWM4 rate is Fhosc/1  f_pwm1 = (11.0592M/1)/2764.8 = 4KHz 
//====================================================================================//		         
	PW4YH = 2765>>8;														
	PW4YL = 2765;
//4K
	PW40DL = 0x00;
	PW40DH = 0x00;																				//占空比50%								

//	PW41DL = 0x50;
//	PW41DH = 0x00;																				//占空比50%																	

//	PW42DL = 0x30;	
//	PW42DH = 0x00;																				//占空比30%																

//	PW43DL = 0x00;		
//	PW43DH = 0x00;																				//占空比0%																
	
	PW4M |= L_PWM_CLOCK_32MDIV1| L_PWMN0_ENABLE;   
	PW4M |= L_ENABLE_PWMN;
	
	IRCON &= 0xdf;
}
//void PWM20(u8 duty)
//{
//	u16 PW2Y = 345;//max 345
//	if(duty > 100)
//		duty = 100;
//	PW2Y = PW2Y * duty / 100 ;
//	PW20DH = (PW2Y >> 8);
//	PW20DL = PW2Y;
//}
//void PWM40(u8 duty)
//{
//	u16 PW4Y = 2765;
//	if(duty > 20)
//		duty = 20;
//	PW4Y = PW4Y * duty / 20 ;
//	PW20DH = (PW4Y >> 8);
//	PW20DL = PW4Y;
//}
