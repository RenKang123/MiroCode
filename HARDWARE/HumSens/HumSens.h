#ifndef __HUMSENS_H
#define __HUMSENS_H	
//#include "sys.h" 
#include "ADC.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//LSENS(光敏传感器)驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////
  
#define LSENS_READ_TIMES	10		//定义光敏传感器读取次数,读这么多次,然后取平均值
#define LSENS_ADC_CHX		ADC_Channel_6		//定义光敏传感器所在的ADC通道编号
    
void HumSens_Init(void); 				//初始化光敏传感器
u8 HumSens_Get_Val(void);				//读取光敏传感器的值
#endif 





















