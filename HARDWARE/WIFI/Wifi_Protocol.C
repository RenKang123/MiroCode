#include "Wifi_Protocol.h"
#include "DISP.h"
#include <stdio.h>
#include <string.h>
//**************************************************************************************
//extern xdata unsigned char Humidata;						//湿度
////**************************************************************************************
//Timing_StatusTypeDef TimingLength = zeroHour;
u8 code MyName[] = {"#NR10,001,S,1,IAM:NR10;"};
u8 code strCMD[] = {"S,"};
u8 code charCMD[] = {"C,"};


static bit F_tx2data = 0;
static bit F_rx2data = 0;
static bit txDataSetOK = 0;
static bit F_txWIFIdata = 0;
static bit F_rxdataok = 0;
static bit isHandshakeSuccess = 0;
//static u8 txData[];

//static u8 testStr1[] = {"abcd"};
//static u8 testStr2[] = {"bcdefgt"};
static u8* uart2Point = MyName;

static u8 tx2cLenth = 0;
static u8 tx2count = 0;
static xdata u8 tx2dataBuf[150];

static u8 rx2count = 0;
static xdata u8 rx2data[30];
static u8 dispState = 0;
static ResponseIOT_CommandTypeDef ResponseIOT_Command = ResponsePWR;
static IOT_keyTypeDef IOT_keyType = noKEY;
static bit F_IOT_Power = 0; 
Timing_StatusTypeDef WIFIsetDISP_TimingLength = zeroHour;
//static HumiStrength_StatusTypeDef HumiStrength = HumiOFF;

//xdata u8 HARU1;
//函数：isThatMe
//输入：字符串首地址
//返回：是否是 NR10,001
static bit isThatMe(u8* StrP)
{
	//u8 i;
	if(strncmp(StrP, MyName + 1,7)==0) 
		return 1;
	return 0;
//	for(i = 0;i < 7;i++)
//	{
//		if(StrP[i] != MyName[i + 1])
//  			return 0;
//	}
//	return 1;
}
/**
 * @fn		int MR_atoi(const char* c)
 * @brief	create atoi() func.
 * @author	yijang
 * @param	char 
 * @return	int.
 */

static char MR_atoi(const char* c) 
{
	char ret = 0;
	char pos = 1;

	if (*c == '-') 
	{
		pos = -1;
		c++;
	}
	while (*c >= '0' && *c <= '9') 
	{
		ret = (ret * 10) + ((*c) - '0');
		c++;
	}
	return ret * pos;
}
static IOT_keyTypeDef StrCovertToEnmu(const char* str)
{
	//IOT_keyTypeDef IOT_keyType = WHO;
//	if(strcmp(str, "REQ")==0) 
//		return REQ;
	switch(*str)
	{
		case 'W':
			str++;
			if(*str == 'H' && *(++str) == 'O')
				return WHO;
			break;
		case 'R':
			str++;
			if(*str == 'E' && *(++str) == 'Q')
				return REQ;
			break;
		case 'P':
			str++;
			if(*str == 'W' && *(++str) == 'R')
				return PWR;
			break;			
		case 'M':
			str++;
			if(*str == 'U')
				return MU;
			if(*str == 'O' && *(++str) == 'D')
				return MOD;
			break;
		case 'L':
			str++;
			if(*str == 'M')
				return LM;
			else if(*str == 'B')
				return LB;
			else if(*str == 'C')
				return LC;
			else if(*str == 'O' && *(++str) == 'C' && *(++str) == 'K')
				return LOCK;
			break;
		case 'H':
			str++;
			if(*str == 'C')
				return HC;
			if(str[0] == 'U' && str[1] == 'M' && str[2] == 'I')
				return HUMI;
			if(*str == 'A' && *(++str) == 'R' && *(++str) == 'U')
			{
				str++;
				if(*str == '1')
					return HARU1;
				if(*str == '2')
					return HARU2;
				if(*str == '3')
					return HARU3;
			}
			break;
		case 'T':
			str++;
			if(str[0] == 'E' && str[1] == 'M' && str[2] == 'P')
				return TEMP;
			if(*str == 'M' && *(++str) == 'R')
			{
				if(*(++str) == 'R'&& *(++str) == 'M')
					return TMRRM;
				return TMR;
			}
			break;
		case 'S':
			str++;
			if(str[0] == 'E' && str[1] == 'N' && str[2] == 'S')
				return SENS;
			break;
		case 'A':
			str++;
			if(str[0] == 'L' && str[1] == 'L')
				return ALL;
			break;
		default:
			return noKEY;
		break;
	}	
	return noKEY;	
}
static void AnalysisStrCommand(u8* StrP)
{
	char temp = 0;
	char j = 0;
	char CMD_Type;
	char NumOfCMD = 0;//命令个数
	char keyStr[5];// = {"00000"};
	CMD_Type = *StrP;
	StrP += 2;// point NumOfCommand
	NumOfCMD = MR_atoi(StrP);
 	while((*StrP != ';') && (*StrP != 0x00))//如果字符串中没有 ；，就会死机
	{
		if(*StrP == ',')//寻找下一个逗号
			break;
		StrP++;
	}
	StrP++;
	while((*StrP != ':') && (*StrP != 0x00))//如果字符串中没有 :，就会死机
	{
		keyStr[j] = *StrP;
		j++;
		StrP++;
	}
	StrP++;
	if(CMD_Type == 'S' )//字符串处理
	{
		IOT_keyType = StrCovertToEnmu(keyStr);
		if(IOT_keyType == REQ)
		{
			for(j = 0;j < 5;j++)
				keyStr[j] = 0;
			j = 0;
			while((*StrP != ';') && (*StrP != 0x00))//如果字符串中没有 ;就会死机
			{
				keyStr[j] = *StrP;
				j++;
				StrP++;
			}	
			if(strcmp(keyStr, "ALL")==0) 
			{
				ResponseIOT_Command = ResponseALL;
			}
			else if(strcmp(keyStr, "SENS")==0)
				ResponseIOT_Command = ResponseREQSENS;				
			else if(strcmp(keyStr, "TMRRM")==0)
				ResponseIOT_Command = ResponseTMRRM;
			else
			{
				ResponseIOT_Command = ERR801;//无效的命令字符串
				return;
			}
			j = 0;
		}
		else
		{
			ResponseIOT_Command = ERR801;//无效的命令字符串
			return;
		}
	}
	else if(CMD_Type == 'C')//数据处理
	{
		IOT_keyType = StrCovertToEnmu(keyStr);
		for(j = 0;j < 5;j++)
			keyStr[j] = 0;
		j = 0;
		if(NumOfCMD == 1)
		{
			switch(IOT_keyType)
			{
				case PWR:
					ResponseIOT_Command = ResponsePWR;
					//do pwr action
					if(*StrP == '1')
					{
						F_IOT_Power = 1;
						setPowerStatus(1);
					}
					else if(*StrP == '0')
					{
						F_IOT_Power = 0;
						setPowerStatus(0);
					}
					else
						ResponseIOT_Command = ERR801;//无效的命令字符串
					break;
				case HC:
					ResponseIOT_Command = ResponseHC;
					if(*StrP == '0')
					{
						setDISPhumiStrengthStatus(HumiOFF);
					}
					else if(*StrP == '1')
					{
						setDISPhumiStrengthStatus(HumiStrength1);
					}
					else if(*StrP == '2')
					{
						setDISPhumiStrengthStatus(HumiStrength2);
					}
					else if(*StrP == '3')
					{
						setDISPhumiStrengthStatus(HumiStrength3);
					}
					else
						ResponseIOT_Command = ERR801;//无效的命令字符串
					break;
				case TMR:	//TMR
					WIFIsetDISP_TimingLength = (Timing_StatusTypeDef)MR_atoi(StrP);
					break;
				case MOD:
					if(*StrP == '1')
					{
						setDISPhumiStrengthStatus(HumiAuto);						
					}
					else if(*StrP == '0')
					{
							//获得自动加湿挡 加湿挡位
					}
					else
						ResponseIOT_Command = ERR801;//无效的命令字符串				
					break;				
				default:break;
			}
		}
	}
	else		
	{
		ResponseIOT_Command = ERR801;//无效的命令字符串
		return;
	}
	j = 0;
	for(j = 0;j < 5;j++)
		keyStr[j] = 0;
	CMD_Type = 0;
	j = 0;
	//
}
void WIFItxDataSet()
{
	u8* PointTx2Buf =  tx2dataBuf;
	switch(ResponseIOT_Command)
	{
		case ResponseName:
		if(F_tx2data == 0)
		{
			F_tx2data = 1;
			uart2Point = MyName;
			S2BUF = uart2Point[0];	//uatr2 first data from there	
			ResponseIOT_Command = ResponseNone;
			isHandshakeSuccess = 1;
		}
		break;	
		case ResponsePWR:
			//if(F_IOT_Power == getDispPowerStatus())
			{
				memcpy(PointTx2Buf,MyName,10);
				PointTx2Buf += 10;
				memcpy(PointTx2Buf,strCMD,2);
				PointTx2Buf += 2;
				memcpy(PointTx2Buf,"6,PWR:",6);
				PointTx2Buf += 6;
				if(F_IOT_Power)
				{
					memcpy(PointTx2Buf,"1,MOD:1,HC:",6);
					PointTx2Buf += 6;
					//未完。。。。。
				}
				else
				{
					memcpy(PointTx2Buf,"0,MOD:0,HC:0,LM:0,LB:1,LC:13;",30);//先前HC:0,LM:0,LB:1,LC:13;状态不清除
					PointTx2Buf += 30;
				}					
			}
			break;
		default:break;
	}
}
void WIFIdeCode()
{
	char i = 0;
	if(F_rxdataok)
	{
		for(i = 0 ; i < 30;i++)
		{
			if(rx2data[i] == '#')
			{
				//if((rx2data[i + 1] == 'A') && (rx2data[i + 2] == 'N') && (rx2data[i + 3] == 'Y') &&(rx2data[i + 17] == '?'))//问我是谁
				if(strncmp(rx2data + i + 1, "ANY,000,S,1,WHO:?",17)==0) 
				{
					ResponseIOT_Command = ResponseName;
				}
				else if(isHandshakeSuccess)
				{
					if(isThatMe(rx2data + i + 1))//是给我发消息吗？
					{
						AnalysisStrCommand(rx2data + i + 10);
					//	ResponseIOT_Command = ResponseName;
					}
					else
					{
						ResponseIOT_Command = ERR801;//无效的命令字符串
					}
				}				
			}
		}
		F_rxdataok = 0;
	}
}
//send data
void UART2txData()
{
	if(F_tx2data)
	{
		tx2count++;			
		S2BUF = uart2Point[tx2count];				//??????????		
		if(uart2Point[tx2count] == ';')
		{
			F_tx2data = 0;
			tx2count = 0;
		}
	}
}
//波特率9600此函数建议1ms调用一次
void init_rx2count()
{
	static u8 count = 0;
	if(F_rx2data)
	{
		F_rx2data = 0;
		count = 0;
	}
	else
	{
		count++;
		if(count > 20)//超过20ms没有接收中断，强制清零rx0count 
		{
			count = 0;
			rx2count = 0;
		}
	}
}
//receive data
void UART2rxData()
{
//	PD3 = ~PD3;
	//F_rx2data = 1;
	F_rxdataok = 0;
	rx2data[rx2count] = S2BUF;
	rx2count++;
	if(S2BUF == ';')
	{
		rx2count = 0;
		F_rxdataok = 1;
#ifdef TRACEMODE
		if(F_tx2data == 0)
		{
			F_tx2data = 1;
			uart2Point = rx2data;
			S2BUF = uart2Point[0];	//uatr2 first data from there	
		}
#endif
	}
}
