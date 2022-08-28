#ifndef	_WIFI_PROTOCOL_H_
#define	_WIFI_PROTOCOL_H_
#include <SN8F5829.h>
#include "Timer.h"
//**************************************************************************************
#define u8 unsigned char
#define u16 unsigned int
	
//#define TRACEMODE 

//typedef enum 
//{    
//  notReceived = 0x00U,      
//  Receiving   = 0x01U,    
//  Received    = 0x02U      
//}UartReceive_ProcessTypeDef;

//Timing_StatusTypeDef getTiming_Status();

void WIFItxDataSet();

void UART2respond(void);
void init_rx2count();//
//中断发送函数
void WIFItxDataSet();
void WIFIdeCode();
void WIFIdeCode();
void UART2txData();
void UART2rxData();

typedef enum 
{    
  ResponseNone = 0x00U,      
  ResponseName = 0x01U,    
  ResponseREQSENS = 0x02U,	
	ResponseTMRRM= 0x03U,
	ResponsePWR  = 0x04U,
	ResponseHC   = 0x05U,
	ResponseMOD  = 0x06U,
	ResponseMU   = 0x07U,
	ResponseLOCK = 0x08U,
	ResponseLM   = 0x09U,
	ResponseLB   = 0x0aU,
	ResponseLC   = 0x0bU,	
	SetSensValue  = 0x0cU,
	ResponseSensValue = 0x0dU,	
	ResponseHARU1= 0x0eU,	
	ResponseHARU2= 0x0fU,	
	ResponseHARU3= 0x10U,	
	ResponseHARUALL  = 0x11U,
	EventPWR_ON  = 0x12U,
	EventPWR_OFF = 0x13U,
	EventHC  		 = 0x14U,
	EventMOD  	 = 0x15U,
	EventTMR  	 = 0x16U,
	EventTMREND  = 0x17U,
	EventMU  		 = 0x18U,
	EventLOCK    = 0x19U,
	EventLM      = 0x1aU,
	EventLC  		 = 0x1bU,
	EventUV  		 = 0x1cU,//预留
	EventNoWatter= 0x1dU,//
	ResponseERR  = 0x1eU,
	ERR801       = 0x1fU,
	ResponseALL = 0x20U
}ResponseIOT_CommandTypeDef;

typedef enum 
{    
  WHO = 0x00U, //usingless     
  REQ = 0x01U,    
  MOD = 0x02U,	
	PWR	= 0x03U,
	TMR  = 0x04U,
	ALL   = 0x05U,//Value
	HC  = 0x06U,
	MU   = 0x07U,
	LOCK = 0x08U,
	LM   = 0x09U,
	LB   = 0x0aU,
	LC   = 0x0bU,
	SENS   = 0x0cU,//1/2Value
	HUMI   = 0x0dU,
	TMRRM   = 0x0eU,//Value
	TEMP   = 0x0fU,
	HARU1   = 0x10U,
	HARU2   = 0x11U,
	HARU3   = 0x12U,
	noKEY   = 0x13U
}IOT_keyTypeDef;

//typedef struct
//{
//	uchar *p_tx;			//发送数据指针
//	uchar 	tx_len;   	//需要发送数据的长度
//	uchar 	tx_offset;	//已发送数据的长度
//}UARTx;
//typedef struct
//{	
//	uchar *p_rx;			//接收数据指针
//	uchar 	rx_len;   	//接收buf总长
//	uchar 	rx_offset;	//已接收数据的长度
//}UARTx;
//**************************************************************************************

#endif