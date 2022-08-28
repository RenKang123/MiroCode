#ifndef	_MYUART_H_
#define	_MYUART_H_
#include <SN8F5829.h>
#include "Timer.h"
#include "HumCTL.h"
//**************************************************************************************
#define u8 unsigned char
#define u16 unsigned int
	


//typedef enum 
//{    
//  notReceived = 0x00U,      
//  Receiving   = 0x01U,    
//  Received    = 0x02U      
//}UartReceive_ProcessTypeDef;

//Timing_StatusTypeDef getTiming_Status();
//void SetDISP_Timing_Length(Timing_StatusTypeDef WIFI_TimingLength);
void setDISPhumiStrengthStatus(HumiStrength_StatusTypeDef setHumiStrength);
void setPowerStatus(bit F_Power);
bit getDispPowerStatus();
bit getDispHumiPowerStatus();
extern void txDataSet();

extern void UART0respond(void);
extern void init_rx0count();//
//中断发送函数
extern void UART0txData();
extern void UART0rxData();
void deCode();




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