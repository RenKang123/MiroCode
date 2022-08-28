#include "ADC.h"
#define	VERFH_VDD				0x03			//VDD
#define	VREF_INT				0x00			//内部参考,P54为GPIO
#define AirTCHANNEL			L_AD_CHANNEL9			//AIN9	 根据实际的硬件去变更	
#define AD_SPEEDDIV16		0x00			//fosc/16
#define SETB0(a,b) a&=~(1<<b)	
#define AirTMON()				SETB0(P5M,1);							//0输入  1输出
#define AirTUR()				SETB0(P5UR,1);						//1上拉  0禁止
//=============================================================================================================//
//						DATA
//=============================================================================================================//
idata uint16_t r_ad_value1 = 0;                           //滤波之后的AD值
idata uint16_t r_ad_value2 = 0;													
idata uint16_t r_ad_value3 = 0;

idata	uint8_t	r_ad1_cnt = 0;															//滑动滤波寄存器													
idata	uint8_t	r_ad2_cnt = 0;
idata	uint8_t	r_ad3_cnt = 0;

idata	uint16_t r_ad1_fifo[L_AD_SAMPLE_MAX] = 0;					 //AD的fifo值
idata	uint16_t r_ad2_fifo[L_AD_SAMPLE_MAX] = 0;
idata	uint16_t r_ad3_fifo[L_AD_SAMPLE_MAX] = 0;

//=============================================================================================================//
//	AD 初始化
//=============================================================================================================//
void ADinit(void)
{	
	AirTMON();
	AirTUR();
//	HUMIMON();
//	HUMIUR();
//	GASTMON();
//	GASTUR();
	
	ADM = 0x80;											//ADC Enable
	ADM |= AirTCHANNEL;
	
	ADR = 0x40;											//AIN channel Enable
	ADR |= AD_SPEEDDIV16;
	
	VREFH = VREF_INT;
	VREFH |= VERFH_VDD;
//	P1CON |= 0x00;									//需禁止相应的施密特触发。
//	P2CON |= 0x01;
	P5CON = 0x0E;																				// AD口使用需打开将P1CON/P2CON/P3CON/P4CON的相应的位置1,否则漏电	   P57  P53
	
}
//void ADinit(void)
//{
//	P5M &= 0xfd;////0输入  1输出
//	P5UR &= 0xfd;//1上拉  0禁止
//	
//	ADM |= 0x80;																			 //ADC Enable
//	ADM |= L_AD_CHANNEL9;
//	
//	ADR = 0x40;																					//AIN channel Enable
//	ADR |= L_AD_SPEEDDIV16;
//	
//	VREFH = L_VREF_INT;							
//	VREFH |= L_VERFH_VDD;
//	P5CON = 0x0E;																						// AD口使用需打开将P1CON/P2CON/P3CON/P4CON的相应的位置1,否则漏电
//	
//}
//=======================================================================
//	得到AD
//=======================================================================
unsigned int	Get_AD(unsigned char ADChannel)
{
	
	unsigned int AD_Buffer;
	unsigned char delay;
	
	ADM &= 0xe0;
	ADM |= ADChannel;	
	
//做延时（注意有些编译器在做优化时有可能会把这部分程序优化掉，如果有这种现象可以在定义delay前面加上volatile关键字）
//	
	
	delay = 100;
	while(delay!=0)
		delay--;

	ADM |= 0x40;													//Start ADC
	while((ADM & 0x20) != 0x20);					//EOC
	ADM &= 0xdf;
	
	AD_Buffer = ADB;
	AD_Buffer = (AD_Buffer << 4) + (ADR & 0x0F);	
	
	return AD_Buffer;
	
}
//uint16_t GetADvalue(uint8_t	ad_channel)
//{ 	
//	uint16_t temp_ad_buf = 0;
//	unsigned char delay = 100;
//	
//	ADM = (ADM&0XE0)|ad_channel;
//	
//	delay = 100;
//	while(delay!=0)
//		delay--;
//	
//	ADM |= 0x40;													//Start ADC
//	while((ADM & 0x20) != 0X20);					//EOC   				
//	ADM &= 0xdf;
//		
//	temp_ad_buf = ADB;
//	temp_ad_buf = (temp_ad_buf << 4) + (ADR & 0X0F);
//						
//	return	temp_ad_buf;
//}

//=============================================================================================================//
//	AD 滑动滤波
//=============================================================================================================//
void	ADSample(void)
{
	static u16 i = 0;
	u16 ADtemp = 0;
	i++;
	if(i > 10000)
	{
		ADtemp = Get_AD(L_AD_CHANNEL9);
		i = 0;
	}

}

//=============================================================================================================//
//	AD 滑动平均算法
//=============================================================================================================//
uint16_t ADAverge(uint16_t *ad_array)
{
	uint8_t i = 0;
	uint16_t temp_sum = 0;
	
	for(i = 0;i < L_AD_SAMPLE_MAX;i++)
	{
		temp_sum += *(ad_array+i);
	}
	temp_sum = temp_sum >> L_AD_SHIFT;
	
	return temp_sum;
}
//=======================================================================
//	AD 去极值平均
//=======================================================================
uint16_t GetAD(uint8_t	ad_channel)
{ 	
	uint8_t i = 0;
	uint16_t j = 0;
	uint16_t temp_ad_max = 0;
	uint16_t temp_ad_min = 0xffff;
	uint16_t temp_ad_buf = 0;
	uint16_t temp_ad_data = 0;
	
	ADM = (ADM&0XE0)|ad_channel;
	
	for(i = 0; i < L_AD_SAMPLE_MAX + 2; i++)				
	{
		ADM |= 0x40;													//Start ADC
		while((ADM & 0x20) != 0X20);					//EOC   				
		ADM &= 0xdf;
		
		temp_ad_buf = ADB;
		temp_ad_buf = (temp_ad_buf << 4) + (ADR & 0X0F);
		temp_ad_data += temp_ad_buf; 
		
		if(temp_ad_buf < temp_ad_min)
		{
			temp_ad_min = temp_ad_buf;
		}
		if(temp_ad_buf > temp_ad_max)
		{
			temp_ad_max = temp_ad_buf;
		}	
	}
	
	temp_ad_data = (temp_ad_data - temp_ad_min - temp_ad_max) >> L_AD_SHIFT;					
	return	temp_ad_data;
}

