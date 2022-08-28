#ifndef __MANAGEMENT_H
#define __MANAGEMENT_H 
#include <SN8F5829.H>
#include "HumCTL.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���������8301�����ӳ���ģ��  
//��������:2020/06/04
//�汾��V1.0	
//����һ ; �����Լ�
//////////////////////////////////////////////////////////////////////////////////


typedef enum 
{    
  zeroHour 		    = 0x00U,      
  twoHour   			= 0x01U,    
  fourHour  			= 0x02U,      
  sixHour  		 		= 0x03U,
	eightHour 			= 0x04U,
	tenHour   			= 0x05U,
	twelveHour   		= 0x06U,
	sixteenHour   	= 0x07U
}Timing_StatusTypeDef;
void management(void); 
u8 getDispState();
nightLight_StatusTypeDef getNightLight_Status();
HumiStrength_StatusTypeDef getHumiStrength_Status();
Timing_StatusTypeDef getTiming_Status();
#endif















