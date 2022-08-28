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
//�жϷ��ͺ���
extern void UART0txData();
extern void UART0rxData();
void deCode();




//typedef struct
//{
//	uchar *p_tx;			//��������ָ��
//	uchar 	tx_len;   	//��Ҫ�������ݵĳ���
//	uchar 	tx_offset;	//�ѷ������ݵĳ���
//}UARTx;
//typedef struct
//{	
//	uchar *p_rx;			//��������ָ��
//	uchar 	rx_len;   	//����buf�ܳ�
//	uchar 	rx_offset;	//�ѽ������ݵĳ���
//}UARTx;
//**************************************************************************************

#endif