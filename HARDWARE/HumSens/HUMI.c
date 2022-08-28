//=============================================================================================================//

#include	<sn8f5829.h>
#include "HUMI.h"

// ********************************************************************************
//���³�ʪ�£�����ʹ��
#define HUMICLOSEDATA 		65300
#define HUMIOPENDATA  		32

// ********************************************************************************
extern idata unsigned char PULSE_TIME;
xdata unsigned char Humidata = 50;						//ʪ��
xdata unsigned char HUMITimes=0;					//AD��������
xdata unsigned int  HUMI_AD_Valve=0;			//16��ʪ��AD�ۼ�

extern xdata signed 	 char  AirTemperature;

// ********************************************************************************
bit F_HUM_AD;
bit F_10MSecond;
bit F_HUMI_Start;
bit F_Humierror;						//ʪ�ȳ���������Χ
bit F_1Second1;
bit F_First_HUMI = 1;

//******************************************************************************
//ʪ�����¶ȵ�AD��Ӧ��             ʪ�Ȱٷֱ�  20%  25%   30%   35%   40%   45%   50%   55%  60%   65%   70%   75%    80%  85%   90%	     			       
const unsigned int code HUMIDATA_5C[15] ={   45,  192,  621, 1505, 3536, 6891,11601,16471,25825,33480,40987,46669,52126,56003,58838};
const unsigned int code HUMIDATA_10C[15]={   85,  340,  986, 2129, 5021, 9140,15525,23334,31774,40002,46458,51336,55790,58669,60752};
const unsigned int code HUMIDATA_15C[15]={  159,  610, 1577, 3637, 7294,12996,21082,29335,38277,45972,51030,55200,58447,60395,61975};
const unsigned int code HUMIDATA_20C[15]={  284, 1011, 2617, 5631,10732,16471,26784,35404,44191,48891,54420,57681,60007,61603,62758};
const unsigned int code HUMIDATA_25C[15]={  517, 1668, 4157, 8876,15643,24253,33191,41624,48891,54038,57040,59348,61260,62351,63273};
const unsigned int code HUMIDATA_30C[15]={  881, 2942, 6596,12470,21752,31113,39489,46669,52833,56516,59007,60752,62100,62989,63613};
const unsigned int code HUMIDATA_35C[15]={ 1467, 4419, 9778,17402,28626,37563,45177,50494,55952,58669,60597,61726,62758,63377,63903};
const unsigned int code HUMIDATA_40C[15]={ 2403, 6891,14065,24253,34686,42780,49704,55003,57996,60159,61603,62478,63234,63639,64103};
const unsigned int code HUMIDATA_45C[15]={ 3914,10033,19013,29335,39898,47387,53097,57040,59508,61235,62313,62989,63561,63903,64263};


void HumiInit()
{
	P4M &= 0xfe;////0����  1��� NTC
	P4UR &= 0xfe;//1����  0��ֹ	
//#define IO_HumiPulse3				P50
//#define IO_HumiPulse2				P51
//#define IO_HumiPulse1				P52
//#define IO_HumiPulse0				P57
	P5M |= 0x87;////0����  1��� HUMI
	P5UR &= 0x78;//1����  0��ֹ
}
//const unsigned int code HUMIDATA_5C[15] ={   45,  192,  621, 1505, 3536, 6891,11601,16471,25825,33480,40987,46669,52126,56003,58838};	
//-----------------------------------------------------------------------------
//iΪ���     	
//-----------------------------------------------------------------------------
unsigned char Humical_1(unsigned char i,unsigned int HUMIData_ADD,unsigned int HUMIDATA_L,unsigned int HUMIDATA_H)
{//�����ض��¶��µ�ʪ��ֵ  iΪ������ţ���1��ʼ��HUMIData_ADDΪ����ֵ  HUMIDATA_H �� HUMIDATA_L ����
	//X=(HUMIData_ADD-HUMIDATA_L)*5/(HUMIDATA_H - HUMIDATA_L)
	unsigned char humi_temp;
	unsigned int  temp,temp1;
	temp = HUMIDATA_H - HUMIDATA_L;
	temp1 = temp/2;
	
	humi_temp = i*5+15;
	//����Ҫ��0.5
	humi_temp += ((HUMIData_ADD-HUMIDATA_L) * 5+temp1)/temp;
	return humi_temp;	
}

//-----------------------------------------------------------------------------
//		Humical_2(5,AirTemperature,Humidata1,Humidata2)
//-----------------------------------------------------------------------------
unsigned char Humical_2(unsigned char T_low,unsigned char T_now,unsigned char humi_1h,unsigned char humi_2l)
{//T_low Ϊ�¶���������  T_nowΪ��ǰ�¶�  humi_1hΪ�¶���T_lowʱ�������ʪ��ֵ  humi_2lΪ�¶���T_low+5ʱ�������ʪ��ֵ
//��ǰʪ��ֵhumi_temp 
//(humi_1h-humi_temp)/(humi_1h-humi_2l)=(T_now-T_low)/5
//humi_temp=humi_1h-(T_now-T_low)*(humi_1h-humi_2l)/5
//
	unsigned char humi_temp;
	humi_temp = humi_1h - (T_now - T_low) * (humi_1h - humi_2l) / 5;	
	return humi_temp;
}



//-----------------------------------------------------------------------------
//��ȡʪ�ȣ�������ת�����жϣ�����Ҫ��������ʱ��ѯ���
//��������ת����ʱ��ڵ�Ϊ10ms,�����⴦������
//-----------------------------------------------------------------------------
void get_HUMID()
{
	unsigned int  AD_Buffer;
	unsigned char i,Humidata1,Humidata2;


	if(F_HUMI_Start)
	{ //ÿ��AD���ִֻ��һ��
		F_HUMI_Start = 0;	
		while((ADM & 0x20) != 0x20);
	
		ADM &= 0xdf;
		AD_Buffer = ADB;
		AD_Buffer = (AD_Buffer << 4) + (ADR & 0x0F);
			
		HUMI_AD_Valve +=	AD_Buffer;
		HUMITimes++;

		if(F_First_HUMI)
		{
			F_First_HUMI = 0;
			HUMITimes = 16;
			HUMI_AD_Valve =(HUMI_AD_Valve<<4);
		}

		if(HUMITimes>15)
		{ //16�ν���һ�Σ�����ʪ��
		//	HUMITimes = 0;
//debug				
	//		AirTemperature =5;
			
			if(HUMI_AD_Valve>HUMICLOSEDATA)
			{ //����������Χ
//				F_Humierror = 1;
				Humidata=91;
			}
			else if(HUMI_AD_Valve<HUMIOPENDATA)
			{ //����������Χ
//				F_Humierror = 1;
				Humidata=19;
			}
			else
			{
				F_Humierror = 0;		
//-----------------------------------------------------------------------------
//ʪ�Ȳ��ͼ���
				if(AirTemperature<5)
				{				
					if(HUMI_AD_Valve<HUMIDATA_5C[0]-10)
					{
						Humidata=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_5C[0])
					{
						Humidata=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_5C[14]+200)
					{
						Humidata=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_5C[14])
					{
						Humidata=90;
					}					
					else
					{
//const unsigned int code HUMIDATA_5C[15] ={   45,  192,  621, 1505, 3536, 6891,11601,16471,25825,33480,40987,46669,52126,56003,58838};			
					
						
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_5C[i])
								continue;
							else
							{
								Humidata = Humical_1(i,HUMI_AD_Valve,HUMIDATA_5C[i-1],HUMIDATA_5C[i]);								
								break;
							}						
						}
					}				
				}
				else if(AirTemperature<10)
				{//5�ȵ�10��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_5C[0]-10)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_5C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_5C[14]+200)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_5C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_5C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_5C[i-1],HUMIDATA_5C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_10C[15]={   85,  340,  986, 2129, 5021, 9140,15525,23334,31774,40002,46458,51336,55790,58669,60752};				
					if(HUMI_AD_Valve<HUMIDATA_10C[0]-20)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_10C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_10C[14]+200)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_10C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_10C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_10C[i-1],HUMIDATA_10C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(5,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<15)
				{//10�ȵ�15��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_10C[0]-20)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_10C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_10C[14]+200)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_10C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_10C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_10C[i-1],HUMIDATA_10C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_15C[15]={  159,  610, 1577, 3637, 7294,12996,21082,29335,38277,45972,51030,55200,58447,60395,61975};				
					if(HUMI_AD_Valve<HUMIDATA_15C[0]-30)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_15C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_15C[14]+150)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_15C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_15C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_15C[i-1],HUMIDATA_15C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(10,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<20)
				{//15�ȵ�20��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_15C[0]-30)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_15C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_15C[14]+150)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_15C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_15C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_15C[i-1],HUMIDATA_15C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_20C[15]={  284, 1011, 2617, 5631,10732,16471,26784,35404,44191,48891,54420,57681,60007,61603,62758};			
					if(HUMI_AD_Valve<HUMIDATA_20C[0]-40)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_20C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_20C[14]+100)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_20C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_20C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_20C[i-1],HUMIDATA_20C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(15,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<25)
				{//25�ȵ�20��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_20C[0]-40)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_20C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_20C[14]+100)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_20C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_20C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_20C[i-1],HUMIDATA_20C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_25C[15]={  517, 1668, 4157, 8876,15643,24253,33191,41624,48891,54038,57040,59348,61260,62351,63273};		
					if(HUMI_AD_Valve<HUMIDATA_25C[0]-50)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_25C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_25C[14]+80)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_25C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_25C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_25C[i-1],HUMIDATA_25C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(20,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<30)
				{//25�ȵ�30��֮��
//const unsigned int code HUMIDATA_25C[15]={  517, 1668, 4157, 8876,15643,24253,33191,41624,48891,54038,57040,59348,61260,62351,63273};					
					if(HUMI_AD_Valve<HUMIDATA_25C[0]-50)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_25C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_25C[14]+80)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_25C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_25C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_25C[i-1],HUMIDATA_25C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_30C[15]={  881, 2942, 6596,12470,21752,31113,39489,46669,52833,56516,59007,60752,62100,62989,63613};		
					if(HUMI_AD_Valve<HUMIDATA_30C[0]-80)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_30C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_30C[14]+50)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_30C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_30C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_30C[i-1],HUMIDATA_30C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(25,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<35)
				{//35�ȵ�30��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_30C[0]-80)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_30C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_30C[14]+50)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_30C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_30C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_30C[i-1],HUMIDATA_30C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_35C[15]={ 1467, 4419, 9778,17402,28626,37563,45177,50494,55952,58669,60597,61726,62758,63377,63903};	
					if(HUMI_AD_Valve<HUMIDATA_35C[0]-100)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_35C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_35C[14]+30)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_35C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_35C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_35C[i-1],HUMIDATA_35C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(30,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<40)
				{//35�ȵ�40��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_35C[0]-100)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_35C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_35C[14]+30)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_35C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_35C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_35C[i-1],HUMIDATA_35C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_40C[15]={ 2403, 6891,14065,24253,34686,42780,49704,55003,57996,60159,61603,62478,63234,63639,64103};	
					if(HUMI_AD_Valve<HUMIDATA_40C[0]-200)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_40C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_40C[14]+20)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_40C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_40C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_40C[i-1],HUMIDATA_40C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(35,AirTemperature,Humidata1,Humidata2);				
				
				}
				else if(AirTemperature<45)
				{//45�ȵ�40��֮��
					
					if(HUMI_AD_Valve<HUMIDATA_40C[0]-200)
					{
						Humidata1=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_40C[0])
					{
						Humidata1=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_40C[14]+20)
					{
						Humidata1=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_40C[14])
					{
						Humidata1=90;
					}					
					else
					{
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_40C[i])
								continue;
							else
							{
								Humidata1 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_40C[i-1],HUMIDATA_40C[i]);								
								break;
							}						
						}
					}			
//const unsigned int code HUMIDATA_45C[15]={ 3914,10033,19013,29335,39898,47387,53097,57040,59508,61235,62313,62989,63561,63903,64263};	
					if(HUMI_AD_Valve<HUMIDATA_45C[0]-300)
					{
						Humidata2=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_45C[0])
					{
						Humidata2=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_45C[14]+10)
					{
						Humidata2=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_45C[14])
					{
						Humidata2=90;
					}					
					else
					{

						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_45C[i])
								continue;
							else
							{
								Humidata2 = Humical_1(i,HUMI_AD_Valve,HUMIDATA_45C[i-1],HUMIDATA_45C[i]);								
								break;
							}						
						}
					}		
						
					Humidata = Humical_2(40,AirTemperature,Humidata1,Humidata2);				
				
				}
				else
				{ //45������
					if(HUMI_AD_Valve<HUMIDATA_45C[0]-300)
					{
						Humidata=19;
					}
					else if(HUMI_AD_Valve<=HUMIDATA_45C[0])
					{
						Humidata=20;
					}
					else if(HUMI_AD_Valve>HUMIDATA_45C[14]+10)
					{
						Humidata=91;
					}
					else if(HUMI_AD_Valve>=HUMIDATA_45C[14])
					{
						Humidata=90;
					}					
					else
					{
//const unsigned int code HUMIDATA_45C[15]={ 3914,10033,19013,29335,39898,47387,53097,57040,59508,61235,62313,62989,63561,63903,64263};			
					
						
						for(i=1;i<15;i++)
						{
							if(HUMI_AD_Valve>HUMIDATA_45C[i])
								continue;
							else
							{
								Humidata = Humical_1(i,HUMI_AD_Valve,HUMIDATA_45C[i-1],HUMIDATA_45C[i]);								
								break;
							}						
						}
					}									
				}
				HUMI_AD_Valve = 0;		
			}
			HUMITimes = 0;
		}		
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void StarHUMIAD()
{
//�����е�����˵�����AD�Ѿ��������,10ms�ڲ����ٴ�����AD		
//��ѡ��ͨ�����ǲ�����ת��������ȷ��ʱ��ڵ��������жϴ�������ʱ����Ͻ�ֹ����AD����		
	static u8 time10mscount = 0;
	if(time10mscount++ >= 100)
	{
		time10mscount = 0;
//		P23 = ~P23;
	//	P24 = ~P24;
		ADM &= 0xe0;
		ADM |= HUMICHANNEL;	

		F_HUM_AD=1;
	
		PULSE_TIME=0;
	}
}


