#ifndef __HUMCTL_H
#define __HUMCTL_H	
#include <SN8F5829.H>
//#include "ADC.h"
//////////////////////////////////////////////////////////////////////////////////	 
								  
//////////////////////////////////////////////////////////////////////////////////
  
#define Ctl_JSA P24
#define Ctl_JSB P62

#define Ctl_JS24V P23   


#define TestWaterPort P22
#define noWater (TestWaterPort == 1)
#define numiValue1 40
#define numiValue2 60

#define JSOFF() (Ctl_JS24V = 1)  
#define JSON() (Ctl_JS24V = 0) 
#define JSStrength1() {Ctl_JSA = 1;Ctl_JSB = 1;}
#define JSStrength2() {Ctl_JSA = 1;Ctl_JSB = 0;}
#define JSStrength3() {Ctl_JSA = 0;Ctl_JSB = 0;}
typedef enum 
{    
  dry 		    	= 0x00U,      
  comfortable  	= 0x01U,    
  humid    			= 0x02U    
}humi_StatusTypeDef;
typedef enum 
{    
  HumiOFF 		    = 0x00U, 
	HumiAuto				= 0x01U,	
  HumiStrength1   = 0x02U,    
  HumiStrength2   = 0x03U,      
  HumiStrength3   = 0x04U,
	NONE						= 0x05U
}HumiStrength_StatusTypeDef;
void ClearVariable();
bit getNoWater_Status();

//10ms 
void HumiTestNoWater();
void HumCTL_Init(void); 				//初始化光敏传感器
void HumCTL(HumiStrength_StatusTypeDef HumiStrength);
void HumiAutoCtl();
//void JS1Gear(void);
//void JS2Gear(void);
//void JS3Gear(void);
#endif 





















