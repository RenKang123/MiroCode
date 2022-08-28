#include "led.h"
#include "PWM.h"
//////////////////////////////////////////////////////////////////////////////////	 

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
static u16 PW20D_SetValue = 0;
static u16 PW40D_SetValue = 0; 
//LED IO初始化
void LED_Init(void)
{
	PWMinit();
//	codeLight_LED_PWM_OFF();
//	warmLight_LED_PWM_OFF();
//	codeLight_LED_PWM(5);
//	warmLight_LED_PWM(5);
}
void LED_Task()
{
	static u16 PW20D_Value = 0;
	static u16 PW40D_Value = 0; 
	if(PW20D_Value != PW20D_SetValue)
	{
		if(PW20D_Value < PW20D_SetValue)
		{
			if(PW20D_Value < (PW20D_SetValue - 10))//差距较大时加速
			{
					PW20D_Value += 10;
			}
			PW20D_Value++;
		}
		else
		{
			if(PW20D_Value > (PW20D_SetValue + 10))//差距较大时加速
			{
					PW20D_Value -= 10;
			}
			PW20D_Value--;
		}
	}
	if(PW40D_Value != PW40D_SetValue)
	{
		if(PW40D_Value < PW40D_SetValue)
		{
			if(PW40D_Value < (PW40D_SetValue - 10))//差距较大时加速
				PW40D_Value += 10;		
			PW40D_Value++;
		}
		else
		{
			if(PW40D_Value > (PW40D_SetValue + 10))//差距较大时加速减
			{
					PW40D_Value -= 10;			
			}
			PW40D_Value--;
		}
	}
	PW20DH = PW20D_Value>>8;																									
	PW20DL = PW20D_Value;	
	
	PW40DH = PW40D_Value>>8;																									
	PW40DL = PW40D_Value;	
}
void coolLight_LED_PWM_set(nightLight_StatusTypeDef brightness)
{
	switch(brightness)
	{
		case off:
			PW20D_SetValue = 0;
		break;
		case dark://25%
			PW20D_SetValue = 2765>>2;
		break;
		case mid:
			PW20D_SetValue = 2765>>1;
		break;
		case bright:
			PW20D_SetValue = 2765;
		break;
		default:
			break;
	}
}
void warmLight_LED_PWM_set(nightLight_StatusTypeDef brightness)
{
	switch(brightness)
	{
		case off:
			PW40D_SetValue = 0;
		break;
		case dark://25%
			PW40D_SetValue = 2765>>2;
		break;
		case mid:
			PW40D_SetValue = 2765>>1;
		break;
		case bright:
			PW40D_SetValue = 2765;
		break;
		default:
			break;
	}
}
//void codeLight_LED_PWM_set25()
//{
//	PW2M |= L_PWMN0_ENABLE;  
//	PW20DH = 0x00;																					//占空比25%				
//	PW20DL = 0x56;			
//}
//void codeLight_LED_PWM_set50()
//{
//	PW2M |= L_PWMN0_ENABLE;  
//	PW20DH = 0x00;																					//占空比50%				
//	PW20DL = 0xac;			
//}
//void codeLight_LED_PWM_set100()
//{
//	PW2M |= L_PWMN0_ENABLE;  
//	PW20DH = 0x01;																					//占空比100%				
//	PW20DL = 0x59;			
//}
//void warmLight_LED_PWM_set100()
//{
//	PW4M |= L_PWMN0_ENABLE; 
//	PW40DH = 2765>>8;																				//占空比100%	
//	PW40DL = 2765;
//}
//void warmLight_LED_PWM_set50()
//{
//	PW4M |= L_PWMN0_ENABLE; 
//	PW40DH = 2765>>9;																				//占空比50%	
//	PW40DL = 2765>>1;
//}
//void warmLight_LED_PWM_set25()
//{
//	PW4M |= L_PWMN0_ENABLE; 
//	PW40DH = 2765>>10;																				//占空比25%	
//	PW40DL = 2765>>2;
//}
//void codeLight_LED_PWM_OFF()
//{
//	PW2M |= L_PWMN0_ENABLE;  
//	PW20DH = 0;																					//占空比0%				
//	PW20DL = 0;
//	PW2M &= ~L_PWMN0_ENABLE;
//	P60 = 0;
//}
//void warmLight_LED_PWM_OFF()
//{
//	PW4M |= L_PWMN0_ENABLE; 
//	PW40DH = 0;																				//占空比0%	
//	PW40DL = 0;
//	PW4M &= ~L_PWMN0_ENABLE;
//	P34 = 0;
//}

