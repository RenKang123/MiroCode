/**
 * Copyright ¨Ï 2019 MIRO Corp. All Rights Reserved.
 * 
 * DO NOT CHANGE THIS FILE!
 * THIS FILE IS GENERATED AUTOMATICALLY!
 */
/**
* @author	kbhong
* @date		2019-01-09
* @file		MR_protocol.h
* @brief	Header File 
* @detail	Header declaration to use in main file.
* 			Array declaration to use in MR_Compare_Key() func.
* 			struct & enum declaration * 			
* @details	Call Using Func. & include Header
*/

#ifndef _MR_PROTO_
#define _MR_PROTO_

#include "MR_def.h"
#include "MR_config.h"
#include "mr_lib.h"

void MR_Init();
int MR_Compare_Key(char Key[]);
char* MR_Get_KeyString(EMR_KeyType keyIdx);
int MR_RcvDataParsing(void);
int MR_UartTimeOut(void);
int MR_GetData(struct _MR_RcvData *p);
int MR_InputData(char SendData);
char* MR_MakeString(struct _MR_RcvData *p);
char* MR_MakeStringBuf(struct _MR_RcvData *p, char* pcBuf, int iSize);
void MR_IncreaseTimerTick();
void MR_ClearData(struct _MR_RcvData *p);

void MR_set_devicename(struct _MR_RcvData* p);
void MR_set_deviceversion(struct _MR_RcvData* p, const char* v);
void MR_set_command(struct _MR_RcvData* p, const char* category);

#endif
