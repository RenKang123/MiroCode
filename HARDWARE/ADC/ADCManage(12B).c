//******************************************************************************/
// FileName  : ADCManage.c
// Project   : 
// Author    : 
//******************************************************************************/
#include	<sn8f5829.h>
#include "ADCManage(12B).h"

//******************************************************************************
//******************************************************************************
xdata unsigned  int  ADvalue1, ADvalue1Acc = 0; 
xdata unsigned  char ReadTimes;						//AD��������
xdata unsigned  int  ADvalueMax;					//18��AD���������ֵ
xdata unsigned  int  ADvalueMin;					//18��AD��������Сֵ

xdata signed 	 char  AirTemperature = 24;	//�¶�  


//********************************************************************
bit F_NTCERR;

//******************************************************************************


//******************************************************************************
const unsigned int code TempTable[ 125 ] = 
{
0     ,			//      		//ʵ���¶�	//������ţ�0
200	  ,		//0-200��·  	//					//1    
405   , 								//-20	      //2               
425   , 								//-19	      //3               
445   , 								//-18	      //4               
466   , 								//-17	      //5               
488   , 								//-16	      //6               
511   , 								//-15	      //7               
534   , 								//-14	      //8               
559   , 								//-13	      //9               
584   , 								//-12	      //������ţ�10         
610   , 								//-11	      //11              
637   , 								//-10	      //12              
665   , 								//-9	      //13              
694   , 								//-8	      //14              
723   , 								//-7	      //15              
754   , 								//-6	      //16              
786   , 								//-5	      //17              
819   , 								//-4	      //18            
853   , 								//-3	      //19            
887   , 								//-2	      //������ţ�20       
923   , 								//-1	      //21            
960   , 								//0		�¶�	//22            
998   , 								//1					//23            
1037  , 								//2					//24            
1077  , 								//3					//25            
1117  , 								//4					//26            
1158  , 								//5					//27            
1200  , 								//6					//28            
1242  , 								//7					//29            
1284  , 								//8					//������ţ�30       
1327  , 								//9					//31            
1371  , 								//10	�¶�	//32            
1415  , 								//11				//33            
1459  , 								//12				//34            
1504  , 								//13				//35            
1549  , 								//14				//36            
1594  , 								//15				//37            
1639  , 								//16				//38            
1684  , 								//17				//39            
1730  , 								//18				//������ţ�40       
1776  , 								//19				//41            
1821  , 								//20	�¶�	//42            
1867  , 								//21				//43            
1912  , 								//22				//44            
1958  , 								//23				//45            
2003  , 								//24				//46            
2048  , 								//25				//47            
2094  , 								//26				//48            
2139  , 								//27				//49            
2184  , 								//28				//������ţ�50       
2228  , 								//29				//51            
2272  , 								//30	�¶�	//52            
2316  , 								//31				//53            
2358  , 								//32				//54            
2401  , 								//33				//55            
2442  , 								//34				//56            
2483  , 								//35				//57            
2523  , 								//36				//58            
2563  , 								//37				//59            
2602  , 								//38				//������ţ�60       
2640  , 								//39				//61            
2678  , 								//40	�¶�	//62            
2715  , 								//41				//63            
2751  , 								//42				//64            
2787  , 								//43				//65            
2821  , 								//44				//66            
2855  , 								//45				//67            
2889  , 								//46				//68            
2921  , 								//47				//69            
2953  , 								//48				//������ţ�70       
2984  , 								//49				//71            
3014  , 								//50	�¶�	//72            
3044  , 								//51				//73            
3073  , 								//52				//74            
3101  , 								//53				//75            
3129  , 								//54				//76            
3156  , 								//55				//77            
3182  , 								//56				//78            
3207  , 								//57				//79            
3232  , 								//58				//������ţ�80       
3257  , 								//59				//81            
3280  , 								//60	�¶�	//82            
3303  , 								//61				//83            
3325  , 								//62				//84            
3347  , 								//63				//85            
3368  , 								//64				//86            
3389  , 								//65				//87            
3409  , 								//66				//88            
3428  , 								//67				//89            
3447  , 								//68				//������ţ�90       
3466  , 								//69				//91            
3484  , 								//70	�¶�	//92            
3501  , 								//71				//93            
3518  , 								//72				//94            
3534  , 								//73				//95            
3550  , 								//74				//96            
3566  , 								//75				//97            
3581  , 								//76				//98            
3595  , 								//77				//99            
3610  , 								//78				//������ţ�100      
3623  , 								//79				//101           	
3637  , 								//80	�¶�	//102           	
3650  , 								//81				//103             	
3662  , 								//82				//104             	
3674  , 								//83			  //105                	
3686  , 								//84				//106
3698  , 								//85				//107
3709  , 								//86				//108
3720  , 								//87				//109
3730  , 								//88				//������ţ�110
3741  , 								//89				//111
3751  , 								//90	�¶�	//112
3760  , 								//91				//113
3770  , 								//92				//114
3779  , 								//93				//115
3788  , 								//94				//116
3796  , 								//95				//117
3804  , 								//96				//118
3812  , 								//97				//119
3820  , 								//98				//������ţ�120
3828  , 								//99				//121
3835  , 								//100	�¶�	//122
3900 ,								  //����100�� //123
4096 ,								  //��·			//124     
};

/*********************************************************************
						CONST
*********************************************************************/


/*********************************************************************
						DATA
*********************************************************************/


//=======================================================================
//	AD ��ʼ��
//=======================================================================
void InitAD(void)
{	
//	AirTMON();
//	AirTUR();
//	HUMIMON();
//	HUMIUR();
//	GASTMON();
//	GASTUR();
	
//	P4M &= 0xfe;////0����  1��� NTC
//	P4UR &= 0xfe;//1����  0��ֹ	
	P5M &= 0xf7;////0����  1��� NTC
	P5UR &= 0xf7;//1����  0��ֹ	
	ADM = 0x80;											//ADC Enable
	ADM |= AirTCHANNEL;
	
	ADR = 0x40;											//AIN channel Enable
	ADR |= AD_SPEEDDIV16;
	
	VREFH = VREF_INT;
	VREFH |= VERFH_VDD;
//	P1CON |= 0x00;									//���ֹ��Ӧ��ʩ���ش�����
//	P2CON |= 0x01;
	P5CON = 0x0E;																				// AD��ʹ����򿪽�P1CON/P2CON/P3CON/P4CON����Ӧ��λ��1,����©��	   P57  P53
	P5CON |= 0x80;		
	P4CON |= 0x01;	
}

/*
AD ����
*/

unsigned int	Get_AD(unsigned char ADChannel)
{
	
	unsigned int AD_Buffer;
	unsigned char delay;
	
	ADM &= 0xe0;
	ADM |= ADChannel;	
	
//����ʱ��ע����Щ�����������Ż�ʱ�п��ܻ���ⲿ�ֳ����Ż����������������������ڶ���delayǰ�����volatile�ؼ��֣�
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

/*

NTC �źŲ�������
����16���ۼӺ��16

*/
//------------------------------------------------------------------------------
// Progress: Read AD value of all Channel
//------------------------------------------------------------------------------
unsigned  char  ReadTemp(unsigned int ADvalue)
{
    unsigned char ADindex;
    
    ADindex = 0;
//  while(ADvalue < TempTable[ADindex])		//NTC�ķ�ѹ����Ϊ��������	
    while(ADvalue > TempTable[ADindex])		//NTC�ķ�ѹ����Ϊ��������
    {
        ADindex++;
    }
    return(ADindex);       
}

// =============================================================================
//	��ȡAD
// =============================================================================
void ReadAirTempreture(void)
{ 
	signed 	 char WaterTemp;
	
  unsigned char WaterTemp1;  
	
  ADvalue1 = Get_AD(AirTCHANNEL);			//ȡ��ADCֵ
  ADvalue1Acc += ADvalue1;          	//ADCֵ�ۼ�
	
//------------ ���ֵ����Сֵ ---------		
	if(ReadTimes == 0)
	{	//��һ�Σ������СֵΪ��ǰֵ
		ADvalueMax=ADvalue1;
		ADvalueMin=ADvalue1;
	}
	else
	{
		if(ADvalueMax<ADvalue1)
		{	//���ֵС�ڵ�ǰֵ���򱻵�ǰֵȡ��
			ADvalueMax=ADvalue1;
		}
		else if(ADvalueMin>ADvalue1)
		{//��Сֵ���ڵ�ǰֵ���򱻵�ǰֵȡ��
			ADvalueMin=ADvalue1;
		}
	}

  ReadTimes++;                        //�ۼӴ����Լ�1
  if(ReadTimes >= 10)									//10��
  {
    ReadTimes = 0;
		//��ȥ�����Сֵ 
    ADvalue1Acc = ADvalue1Acc-ADvalueMax-ADvalueMin;
		//��ƽ��
		ADvalue1Acc=(ADvalue1Acc>>3);

//******************  �¶�   **********************************	
		WaterTemp1 = ReadTemp(ADvalue1Acc);		//WaterTemp1Ϊ����ϵ��
		
		if((WaterTemp1<=2)||(WaterTemp1==124))
		{ //��·���·
			F_NTCERR = 1;			
			WaterTemp =-20;			//�¶ȣ�������Ҫ�û����ж���
		}
		else 
		{
			F_NTCERR = 0;	
			WaterTemp = WaterTemp1-22;
//			if(ADvalue1Acc-TempTable[WaterTemp1-1]<TempTable[WaterTemp1]-ADvalue1Acc)
//			{ //AD�������µľͶ��1����֮��Ȼ
//				WaterTemp = WaterTemp1-27;
//			}
//			else
//			{
//				WaterTemp = WaterTemp1-26;
//			}
			
		}
					
//****************** ��ȡʵ���¶�  **********************************************
		if(WaterTemp>99)
		{
			WaterTemp = 99;
		}
		if(WaterTemp<0)
		{
			WaterTemp = 0;
		}
		AirTemperature = WaterTemp;				//��ȡ�¶�
		
		ADvalue1Acc = 0;		//��0
	}
}

