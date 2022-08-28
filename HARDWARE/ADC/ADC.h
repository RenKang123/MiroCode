#ifndef _ADC_h_
#define _ADC_h_
#include <SN8F5829.h>
//===========================================================================================================//
//						CONST
//===========================================================================================================//

#define		L_AD_CHANNEL1			0x01				//AIN1	P41								
#define		L_AD_CHANNEL2			0x02				//AIN2	P42
#define		L_AD_CHANNEL9			0x09			//AIN9	P51
#define		L_AD_CHANNEL3			0x10				//AIN16	�ڲ��ο���ѹ���ͨ��,���Է������VDD�Ĵ�С

#define 	L_AD_SPEEDDIV32		0x00				//fosc/32
#define 	L_AD_SPEEDDIV16		0x10				//fosc/16
#define 	L_AD_SPEEDDIV8		0x30				//fosc/8
#define 	L_AD_SPEEDDIV2		0x20				//fosc/2

#define		L_VREF_INT				0x00				//�ڲ��ο�,P40ΪGPIO
#define		L_VREF_EXT				0X80				//�ⲿ�ο�,FROM P40

#define		L_VERFH_2V				0x00				//VREFH = 2V
#define		L_VERFH_3V				0x01				//VREFH = 3V
#define		L_VERFH_4V				0x02				//VREFH = 4V
#define		L_VERFH_VDD				0x03				//VREFH = VDD
#define		L_VERFH_INT_2V		0x04				//VREFH = VDD and AIN16 = 2V
#define		L_VERFH_INT_3V		0x05				//VREFH = VDD and AIN16 = 3V
#define		L_VERFH_INT_4V		0x06				//VREFH = VDD and AIN16 = 4V

#define	L_AD_SAMPLE_MAX			8					//����8�Σ�����������øĶ�����ֹADֵ�ۼ�ƽ������
#define	L_AD_SHIFT					3					//����3��ƽ��
//===========================================================================================================//
void Systeminit(void);
void ADinit(void);
void ADSample(void);
uint16_t GetAD(uint8_t adchannel);
uint16_t GetADvalue(uint8_t	ad_channel);
uint16_t ADAverge(uint16_t *adarray);
//===========================================================================================================//
#endif