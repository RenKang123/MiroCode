// ********************************************************************************
// File   :  ADCManage.h
// Author :  Chen Jia Sheng
//        :  Xiamen Chipsun
// ********************************************************************************
#ifndef ADCManage_H_
#define ADCManage_H_

//********************************************************************
#define NTCOPENDATA		40				//开路
#define NTCSHORTDATA	4000			//短路 4000

//******************************************************************************
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

//********************************************************************
#define AirTCHANNEL			AD_CHANNEL11			//AIN11	 根据实际的硬件去变更	

#define AirTMON()				SETB0(P5M,1);							//0输入  1输出
#define AirTUR()				SETB0(P5UR,1);						//1上拉  0禁止
//#define AirTCHANNEL			AD_CHANNEL13			//AIN9	 根据实际的硬件去变更	

//#define AirTMON()				SETB0(P5M,5);							//0输入  1输出
//#define AirTUR()				SETB0(P5UR,5);						//1上拉  0禁止

#define AD_SPEEDDIV16		0x00			//fosc/16
#define AD_SPEEDDIV8		0x10			//fosc/8
#define AD_SPEEDDIV1		0x20			//fosc/1
#define AD_SPEEDDIV2		0x30			//fosc/2

#define	VREF_INT				0x00			//内部参考,P54为GPIO
#define	VREF_EXT				0X80			//外部参考,FROM P54

#define	VERFH_2V				0x00			//2V
#define	VERFH_3V				0x01			//3V
#define	VERFH_4V				0x02			//4V
#define	VERFH_VDD				0x03			//VDD
//#define	VERFH_INTVDD		0x04			//内部vdd输入检测				
#define	VERFH_INTVDD		0x07			//内部vdd输入检测				


// ********************************************************************************
extern xdata signed 	 char  AirTemperature;


// ********************************************************************************
extern bit F_NTCOpen;			//开路	
extern bit F_NTCERR;


// ********************************************************************************
void InitAD(void);
void ReadAirTempreture(void);
unsigned int Get_AD(unsigned char ADChannel);


#endif /* ADCManage_H_ */