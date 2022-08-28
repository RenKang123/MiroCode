#include "DISP.h"
#include "led.h"


//**************************************************************************************
extern xdata unsigned char Humidata;						//湿度
extern Timing_StatusTypeDef WIFIsetDISP_TimingLength;
//**************************************************************************************
Timing_StatusTypeDef TimingLength = zeroHour;


static bit F_tx0data = 0;

//bit txDataSetOK = 0;
static bit F_rx0data = 0;
static bit F_rxdataok = 0;
//static u8 txData[];

//static u8 testStr1[] = {"abcd"};
//static u8 testStr2[] = {"bcdefgt"};


static u8 tx0cLenth = 0;
static u8 tx0count = 0;
static xdata u8 tx0data[4];

static u8* uart0Point = tx0data;

static u8 rx0count = 0;
static xdata u8 rx0data[4];
static u8 dispState = 0;

static nightLight_StatusTypeDef  brightness = off;
static HumiStrength_StatusTypeDef HumiStrength = HumiOFF;
static humi_StatusTypeDef humi_Status = comfortable;

static bit F_Power = 0;
static bit F_setDISP_PowerON = 0;
static bit F_setDISP_PowerOFF = 0;
static bit F_setDISP_HC_MOD = 0;
static HumiStrength_StatusTypeDef setDISP_HumiStrength = HumiOFF;
void txDataSet()
{
	//dispState = getDispState();
	//头码
	tx0data[0] = 0x55;
	//1\2位
	tx0data[1] = 0;//外部函数返回数据 1、2位 humi_Status 3位 无水检测 4位定时关机
	if(Humidata < 40)
		humi_Status = dry;
	else if(Humidata < 60)
		humi_Status = comfortable;
	else
		humi_Status = humid;
	tx0data[1] = (u8)humi_Status;
	if(getNoWater_Status())
		tx0data[1] |= 1<<2;
	else
		tx0data[1] &= ~(1<<2);
	if(getTimeSwitchStatus())
		tx0data[1] |= 1<<3;
	else
		tx0data[1] &= ~(1<<3);
	//5位设置DISP开 6位设置DISP关   还剩2位
	if(F_setDISP_PowerON)
	{
		if(F_Power)
		{
			F_setDISP_PowerON = 0;
			tx0data[1] &= ~(1<<4); 
		}
		else
			tx0data[1] |= (1<<4);
	}
	if(F_setDISP_PowerOFF)
	{
		if(!F_Power)
		{
			F_setDISP_PowerOFF = 0;
			tx0data[1] &= ~(1<<5); 
		}
		else		
			tx0data[1] |= (1<<5);		
	}	
	tx0data[2] = 0;//外部函数返回数据 1 2 3位 3 4 5定时
	tx0data[2] = WIFIsetDISP_TimingLength;
	tx0data[2] <<= 3;
	if(setDISP_HumiStrength == HumiStrength)
		setDISP_HumiStrength = NONE;//
	tx0data[2] |= (u8)setDISP_HumiStrength;
	
	//校验
	tx0data[3] = tx0data[0] ^ tx0data[1];
	tx0data[3] ^= tx0data[2];
	tx0data[3]++;
	//tx0cLenth = sizeof(testStr2);
	tx0cLenth = 4;
	uart0Point = tx0data;//发送指针指向发送数组
	if(F_tx0data == 0)
	{
		F_tx0data = 1;
		S0BUF = uart0Point[0];	//uatr0 first data from there	
	}
}
void deCode()
{
	u8 rx0dataCheck = 0;
	if(F_rxdataok)
	{
		F_rxdataok = 0;
		if(rx0data[0] == 0x55)//头码
		{
			rx0dataCheck = rx0data[0] ^ rx0data[1];
			rx0dataCheck ^= rx0data[2];
//模式 UV灯开关 1bit 小夜灯4种状态 2bit 电源开关 1bit 加湿模式5种状态 3bit 加湿强度触摸时工作 : 1 档 -> 2档 -> 3 档 -> Auto -> OFF -> 1档
			if(rx0dataCheck == rx0data[3])//校验成功
			{
				brightness = (rx0data[1]>>1) & 0x03;
				if(rx0data[2] & 0x20)
				{
					warmLight_LED_PWM_set(brightness);
					coolLight_LED_PWM_set(off);
				}
				else
				{
					warmLight_LED_PWM_set(off);
					coolLight_LED_PWM_set(brightness);					
				}
				if(rx0data[1] & 0x08)
					F_Power = 1;
				else
					F_Power = 0; 					
				HumiStrength = (rx0data[1]>>4) & 0x07;
				TimingLength = (Timing_StatusTypeDef)(rx0data[2] & 0x07);
				HumCTL(HumiStrength);
			}
		}
	}
}
//void SetDISP_Timing_Length(Timing_StatusTypeDef WIFI_TimingLength)
//{
//	if(WIFI_TimingLength != TimingLength)
//	{
//		setDISP_TimingLength = WIFI_TimingLength; 
//	}
//}
void setPowerStatus(bit F_Power)
{
	if(F_Power)
	{
		F_setDISP_PowerON = 1;
		F_setDISP_PowerOFF = 0;
	}
	else
	{
		F_setDISP_PowerON = 0;
		F_setDISP_PowerOFF = 1;
	}
}
void setDISPhumiStrengthStatus(HumiStrength_StatusTypeDef setHumiStrength)
{
	if(setHumiStrength != HumiStrength)
	{
		setDISP_HumiStrength = setHumiStrength; 
	}
	else
		setHumiStrength = NONE;
}
bit getDispPowerStatus()
{
	return F_Power;
}
bit getDispHumiPowerStatus()
{
	return  (HumiStrength != HumiOFF);
}
//send data
void UART0txData()
{
	if(F_tx0data)
	{
		tx0count++;			
		if(tx0count < tx0cLenth)
		{	
			S0BUF = uart0Point[tx0count];				//??????????
		}
		else
		{
			F_tx0data = 0;
			tx0count = 0;
		}
	}
}
//波特率9600此函数建议1ms调用一次
void init_rx0count()
{
	static u8 count = 0;
	if(F_rx0data)
	{
		F_rx0data = 0;
		count = 0;
	}
	else
	{
		count++;
		if(count > 5)//超过5ms没有接收中断，强制清零rx0count
		{
			count = 0;
			rx0count = 0;
		}
	}
}
//receive data
void UART0rxData()
{
//	PD3 = ~PD3;
	F_rx0data = 1;
	rx0data[rx0count] = S0BUF;
	rx0count++;
	if(rx0count > 3)
	{
		rx0count = 0;
		F_rxdataok = 1;
	}
}
