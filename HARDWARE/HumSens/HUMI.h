// ********************************************************************************
// File   :  ADCManage.h
// Author :  
//        :  Xiamen Chipsun
// ********************************************************************************
#ifndef _HUMI_H_
#define _HUMI_H_

//********************************************************************
#define	AD_CHANNEL0			0x00			//AIN0	P20								
#define	AD_CHANNEL1			0x01			//AIN1	P21								
#define	AD_CHANNEL2			0x02			//AIN2	P22
#define	AD_CHANNEL3			0x03			//AIN3	P23
#define	AD_CHANNEL4			0x04			//AIN4	P24
#define	AD_CHANNEL5			0x05			//AIN5	P25
#define	AD_CHANNEL6			0x06			//AIN6	P17
#define	AD_CHANNEL7			0x07			//AIN7	P16
#define	AD_CHANNEL8			0x08			//AIN8	P15
#define	AD_CHANNEL9			0x09			//AIN9	P14
#define	AD_CHANNEL10		0x0A			//AIN10	P13
#define	AD_CHANNEL11		0x0B			//AIN11	P13
#define	AD_CHANNEL12		0x0C			//AIN12	P13
#define	AD_CHANNEL13		0x0D			//AIN13	P13
#define	AD_CHANNEL14		0x0E			//AIN14	P13
#define	AD_CHANNEL15		0x0F			//AIN15	P13
//****************** 湿度相关 ****************************************
#define HUMICHANNEL					AD_CHANNEL0
//#define HUMIMON()						SETB0(P5M,2);							//0输入  1输出
//#define HUMIUR()						SETB0(P5UR,2);						//1上拉  0禁止

#define IO_HumiPulse3				P50
#define IO_HumiPulse2				P51
#define IO_HumiPulse1				P52
#define IO_HumiPulse0				P53


//typedef enum 
//{    
//  dry 		    	= 0x00U,      
//  comfortable  	= 0x01U,    
//  humid    			= 0x02U,    
//	humiAuto  		= 0x03U
//}humi_StatusTypeDef;

//typedef enum 
//{    
//  HumiOFF 		    = 0x00U,      
//  HumiStrength1   = 0x01U,    
//  HumiStrength2   = 0x02U,      
//  HumiStrength3   = 0x03U,
//	HumiAuto				= 0x04U
//}HumiStrength_StatusTypeDef;

// ********************************************************************************
//extern idata unsigned char  PULSE_TIME;
//extern xdata unsigned int   HUMI_AD_Valve;
//extern xdata unsigned char  Humidata;						//湿度



// ********************************************************************************
//extern bit F_HUM_AD;
//extern bit F_10MSecond;
//extern bit F_HUMI_Start;
//extern bit F_1Second1;
//extern bit F_First_HUMI;

// ********************************************************************************
void HumiInit();
void InitAD(void);
void get_HUMID(void);
void StarHUMIAD();
void HumiDriver();



#endif /* HUMI_H_ */