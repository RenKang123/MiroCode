#include "HumCTL.h"
#include "DISP.h"
//#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 

//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
// #define Ctl_JSA P23
//#define Ctl_JSB P24
extern xdata unsigned char Humidata;						//湿度
/* Private variables ---------------------------------------------------------*/
//static HumiStrength_StatusTypeDef autoHumiStrength = HumiStrength2;
static u8_10msCount = 0;//关机时清零
static bit F_noWater = 0;
static humi_StatusTypeDef humi_Status = comfortable;
//#define Ctl_JS24V P62  
//初始化传感器
void HumCTL_Init(void)
{
//#define Ctl_JSA P23
//#define Ctl_JSB P24
	P2M |= 0x18;////0输入  1输出 
	P2UR &= ~0x18;//1上拉  0禁止
	//JSA\JSB
	P6M |= 0x04;////0输入  1输出 
	P6UR &= ~0x04;//1上拉  0禁止
//	Ctl_JS24V ;
	//P22
	P2M &= ~0x04;////0输入  1输出 
	P2UR |= 0x04;//1上拉  0禁止
}
//void ClearVariable()
//{
//	u8_10msCount = 0;
//}
bit getNoWater_Status()
{
	return F_noWater;
}
//10ms 
void HumiTestNoWater()
{
	if(getDispHumiPowerStatus())
	{
		if(u8_10msCount >= 100)
		{
			if(noWater)
			{
				u8_10msCount++;
				if(u8_10msCount > 160)//消抖60ms
				{
					u8_10msCount = 170;
					F_noWater = 1;
//					F_noWater = 0;
				}
			}
			else
			{//have water
				F_noWater = 0;
				u8_10msCount = 100;
			}
		}
		else//开机前延时1s
			u8_10msCount++;//关机时清零
	}
	else
	{
		F_noWater = 0;
		u8_10msCount = 0;
	}
}
void HumCTL(HumiStrength_StatusTypeDef HumiStrength)
{
	//湿度等级判定
	if(humi_Status == dry)
	{
		if(Humidata > 40)
			humi_Status = comfortable;
	}
	if(humi_Status == comfortable)
	{			
		if(Humidata < 40)
			humi_Status = dry;
		if(Humidata > 60)
			humi_Status = humid;
	}
	if(humi_Status == humid)
	{
		if(Humidata < 60)
			humi_Status = comfortable;
	}
	switch(HumiStrength)
	{
		case HumiAuto:
			if(humi_Status == dry)
			{
				JSON();
				Ctl_JSA = 0;
				Ctl_JSB = 0;
				break;
			}
			if(humi_Status == comfortable)
			{
				JSON();
				Ctl_JSA = 1;
				Ctl_JSB = 0;
				break;
			}
			if(humi_Status == humid)
			{
				JSON();
				Ctl_JSA = 1;
				Ctl_JSB = 1;
				break;
			}	
		break;
		case HumiStrength1:	
		JSON();
		Ctl_JSA = 1;
		Ctl_JSB = 1;
		break;
		case HumiStrength2:
		JSON();
		Ctl_JSA = 1;
		Ctl_JSB = 0;
		break;
		case HumiStrength3:	
		JSON();
		Ctl_JSA = 0;
		Ctl_JSB = 0;
		break;
		case HumiOFF:
		default:
			JSOFF();
		break;
	}
}

//void HumiAutoCtl()
//{
//	switch(autoHumiStrength)
//	{
//		case HumiStrength1:
//			if(Humidata > numiValue1 + 2)
//				autoHumiStrength = HumiStrength2;		
//			break;
//		case HumiStrength2:	
//			if(Humidata < numiValue1 - 2)
//				autoHumiStrength = HumiStrength1;
//			if(Humidata > numiValue2 + 2)
//				autoHumiStrength = HumiStrength3;
//			break;
//		case HumiStrength3:
//			if(Humidata < numiValue2 - 2)
//				autoHumiStrength = HumiStrength2;
//		default:
//			break;
//	}
//}
//void JS1Gear(void)
//{
//	Ctl_JS24V = 1;
//	Ctl_JSA = 0;
//	Ctl_JSB = 0;
//}
//void JS2Gear(void)
//{
//	Ctl_JS24V = 1;
//	Ctl_JSA = 0;
//	Ctl_JSB = 1;	
//}
//void JS3Gear(void)
//{
//	Ctl_JS24V = 1;
//	Ctl_JSA = 1;
//	Ctl_JSB = 1;	
//}














