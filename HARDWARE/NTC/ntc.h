#ifndef __NTC_H
#define __NTC_H	
//#include "sys.h" 
#include "ADC.h"
//////////////////////////////////////////////////////////////////////////////////	 

//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////
  
#define LSENS_READ_TIMES	10		//���������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
#define LSENS_ADC_CHX		ADC_Channel_6		//����������������ڵ�ADCͨ�����
    
void NTC_Init(void); 				//��ʼ������������
u8 NTC_Get_Val(void);				//��ȡ������������ֵ
#endif 





















