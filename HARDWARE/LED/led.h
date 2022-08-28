#ifndef __LED_H
#define __LED_H	 
#include <SN8F5829.H>
//////////////////////////////////////////////////////////////////////////////////	 

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define codeLight_LED_PWM(x) PWM20(x)// 
#define warmLight_LED_PWM(x) PWM40(x)//

typedef enum 
{    
  off 		    = 0x00U,      
  dark        = 0x01U,    
  mid    			= 0x02U,      
  bright      = 0x03U
}nightLight_StatusTypeDef;

void LED_Init(void);//≥ı ºªØ
void LED_Task();
void coolLight_LED_PWM_set(nightLight_StatusTypeDef brightness);
void warmLight_LED_PWM_set(nightLight_StatusTypeDef brightness);
//void codeLight_LED_PWM_set25();

//void codeLight_LED_PWM_set50();
//void codeLight_LED_PWM_set100();

//void warmLight_LED_PWM_set100();
//void warmLight_LED_PWM_set50();
//void warmLight_LED_PWM_set25();
//void codeLight_LED_PWM_OFF();

//void warmLight_LED_PWM_OFF(); 				    
#endif
