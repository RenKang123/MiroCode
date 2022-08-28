/**
 * Copyright ⓒ 2019 MIRO Corp. All Rights Reserved.
 * 
 * DO NOT CHANGE THIS FILE!
 * THIS FILE IS GENERATED AUTOMATICALLY!
 */
/**
* @author	kbhong
* @date		2019-01-09
* @file		MR_protocol.c
* @brief	Main File
* @details	Call Using Func. & include Header
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MR_Protocol.h"

enum MR_PROTOCOL_INDEX { STX, CATEGORY, VERSION, CMDTYPE, CMDLENGTH, CMD, DATA, ETX };

#define MAKESTRARRAYSIZE 4

#define ISDEVICE()    (strcmp(gMR_RcvData[gMR_Index_Head].Category,MR_DEVICENAME) == 0 || strcmp(gMR_RcvData[gMR_Index_Head].Category,"ANY") == 0) ? 1 : 0
#define ISRCVBUFFEMPTY (gMR_Head - gMR_Tail == 0 ? 1 : 0)
#define ISMRDATAEMPTY (gMR_Index_Head - gMR_Index_Tail == 0 ? 1 : 0) //데이터 분석이 되어 있는지 비어 있는지 확인할 구문 

extern char gMR_Key_Type[][MR_BUFF_SIZE];

int gMR_Head, gMR_Tail;
int gMR_Index_Head, gMR_Index_Tail;
char gMR_RcvBuff[MR_RCV_SIZE] = { '\0', };
char MR_UartTimeOutFlag;
unsigned int MR_Timeout;

struct _MR_RcvData gMR_RcvData[MR_RCVDATA_SIZE];
enum MR_PROTOCOL_INDEX MR_status = STX;

#ifdef USE_MR_STREXT
char gMR_MemoryBuf[MR_MEM_SIZE];
#endif // USE_MR_STREXT


void MR_Init()
{
	MR_Timeout = -1;
#ifdef USE_MR_STREXT
	MR_MEM_Init(gMR_MemoryBuf, MR_MEM_SIZE);
#endif // USE_MR_STREXT
}

/**
* @fn		void MR_set_devicename(struct _MR_RcvData* p)
* @brief	Copy the Device name to struct
* @return	void
*/
void MR_set_devicename(struct _MR_RcvData* p)
{
	MR_strcpy(p->Category, MR_DEVICENAME);
}

/**
* @fn		void MR_set_deviceversion(struct _MR_RcvData* p, const char* v)
* @brief	Copy the Device version to struct
* @return	void
*/
void MR_set_deviceversion(struct _MR_RcvData* p, const char* v)
{
	MR_strcpy(p->Version, v);
}

/**
* @fn		void MR_set_command(struct _MR_RcvData* p, const char* category)
* @brief	Copy the Command Type to struct
* @return	void
*/
void MR_set_command(struct _MR_RcvData* p, const char* category)
{
	MR_strcpy(p->CmdType, category);
}


/**
* @fn		int MR_UartTimeOut()
* @brief	UART MR_Timeout Func.
* @return	1	timeout occur \n
* 			0	pass
*/
int MR_UartTimeOut()
{
	if (MR_UartTimeOutFlag) /*!< Insert UART TIMEOUT Flag instead of 0 */
	{
		return 1; /*!< Time out */
	}
	return 0; 
}

/**
* @fn		int MR_Compare_Key(char Key[])
* @brief	replace key value with index value in defined array
* @param	key[]	key value
* @return	Substituted key value
*/
int MR_Compare_Key(char Key[])
{
	int i = 0;

	for (i = 0;i < eMR_KEY_ENDOFKEY;i++)
	{
		if (!(MR_strncmp(Key, MR_Get_KeyString(i), MR_BUFF_SIZE)))
		{
			return i;
		}
	}
	return -1;
}

/**
* @brief	return string from key index
* @param	keyIdx	key index value
* @return	string or null if index is not in boundary
*/
char* MR_Get_KeyString(EMR_KeyType keyIdx)
{
	if (keyIdx < 0 || keyIdx >= eMR_KEY_ENDOFKEY) {
		return 0;
	}
	return gMR_Key_Type[keyIdx];
}

/**
* @brief	store the data input by UART in gMR_RcvBuff array
* @param	SendData	data coming into UART
* @return	0
*/
int MR_InputData(char SendData)
{
	gMR_RcvBuff[gMR_Head++] = SendData;
	if (gMR_Head == MR_RCV_SIZE)
	{
		gMR_Head = 0;
	}

	return 0;
}

/**
* @brief	get the struct in gMR_RcvBuff array
* @param	struct pointer
* @return	0
*/
int MR_GetData(struct _MR_RcvData *p)
{	
	MR_MEM_Memcpy(p, &gMR_RcvData[gMR_Index_Tail], sizeof(struct _MR_RcvData));
	gMR_Index_Tail++;
	if (gMR_Index_Tail == MR_RCVDATA_SIZE) 
	{
		gMR_Index_Tail = 0;
	}
    if (gMR_Index_Head < gMR_Index_Tail)
	{
		gMR_Index_Tail--;
	}
	return 0;
}

/**
* @brief	translate struct to string array
* @param	struct to convert
* @return	converted array
*/
char* MR_MakeString(struct _MR_RcvData *p)
{
	static xdata char temp[150] = { '\0', }; 

	return MR_MakeStringBuf(p, temp, 150);
}

/**
* @brief	set the struct to clean
* @param	structure to clean
* @return	void
*/
void MR_ClearData(struct _MR_RcvData *p)
{
	int i;
	for (i = 0; i < MR_PAIR_BUFF_SIZE; ++i) {
#ifdef USE_MR_STREXT
		if (p->MR_Pair[i].Type == MR_TYPE_STREXT) {
			MR_MEM_Free((void*)p->MR_Pair[i].Value);
		}
#endif // USE_MR_STREXT
	}
	MR_MEM_Memset(p, 0, sizeof(struct _MR_RcvData));
}

/**
* @brief	
* @param	
* @return	
*/
static int _CopyCh(char s, char** ppd, int* piBufLen)
{
	if (*piBufLen <= 0)
	{
		return -1;
	}
	else
	{
		**ppd = s;
		*ppd += 1;
		*piBufLen -= 1;
	}
	return 1;
}

/**
* @brief	translate struct to string array
* @param	struct to convert
* @return	fail    : 0
			success : converted array
*/
char* MR_MakeStringBuf(struct _MR_RcvData *p, char* pcBuf, int iSize)
{
	int iRet;
	int i;
	int iCmdLen;
	char* pcPos = pcBuf;
    // define pointers
    char* parrPtrs[MAKESTRARRAYSIZE];
	parrPtrs[0] = p->Category;
	parrPtrs[1] = p->Version;
	parrPtrs[2] = p->CmdType;
	parrPtrs[3] = p->CmdLength;
    

	// Reduce 1 byte to store '\0' at the end of string
	//--iSize;
	// STX
	iRet = _CopyCh(STX_CHAR, &pcPos, &iSize);
	if (iRet < 0)
	{
		return 0;
	}

	// Copy header strings
	for (i = 0; i < MAKESTRARRAYSIZE; ++i)
	{
		iRet = MR_strcpy_s(&pcPos, parrPtrs[i], 0, &iSize);
		if (iRet < 0)
		{
			return 0;
		}
		iRet = _CopyCh(SEPERATOR_CHAR, &pcPos, &iSize);
		if (iRet < 0)
		{
			return 0;
		}
	}
	// Copy KVs
	iCmdLen = MR_atoi(p->CmdLength);
	for (i = 0; i < iCmdLen; ++i)
	{
		// copy key
		iRet = MR_strcpy_s(&pcPos, MR_Get_KeyString(p->MR_Pair[i].Key), 0, &iSize);
		if (iRet < 0)
		{
			return 0;
		}
		// copy separator
		iRet = _CopyCh(SEPERATOR_CMD_CHAR, &pcPos, &iSize);
		if (iRet < 0)
		{
			return 0;
		}
		// copy value
		if (p->MR_Pair[i].Type == MR_TYPE_INT)
		{
			iRet = MR_itoa_s(pcPos, p->MR_Pair[i].Value, iSize);
			if (iRet >= 0)
			{
				pcPos += iRet;
				iSize -= iRet;
			}
		}
		else if (p->MR_Pair[i].Type == MR_TYPE_STR)
		{
			iRet = MR_strcpy_s(&pcPos, MR_Get_KeyString(p->MR_Pair[i].Value), 0, &iSize);
		}
#ifdef USE_MR_STREXT
		else if (p->MR_Pair[i].Type == MR_TYPE_STREXT)
		{
			iRet = MR_strcpy_s(&pcPos, (char*)(p->MR_Pair[i].Value), 0, &iSize);
		}
#endif // USE_MR_STREXT
		if (iRet < 0)
		{
			return 0;
		}
		// copy comma
		if ((i + 1) != iCmdLen)
		{
			iRet = _CopyCh(SEPERATOR_CHAR, &pcPos, &iSize);
			if (iRet < 0)
			{
				return 0;
			}
		}
	}
	// ETX
	iRet = _CopyCh(ETX_CHAR, &pcPos, &iSize);
    iRet = _CopyCh(NULL_CHAR, &pcPos, &iSize);    
	if (iRet < 0)
	{
		return 0;
	}

	return pcBuf;
}

/**
* @brief	for error case, reset current status and return error code
* @param	pPair_Index		pairing index number
*			err				error code number
* @return	error code number
*/
static int _errHandling(int* pPair_Index, int err)
{
	MR_status = STX;
	if (err != MR_RETURN_AllPairSuccess) {
		MR_ClearData(&(gMR_RcvData[gMR_Index_Head]));
	}
	gMR_Index_Head++;
	*pPair_Index = 0;
	MR_UartTimeOutFlag = 0;
	MR_Timeout = 0;
	return err;
}

/**
* @brief	user must create
* @return*	-6  Error : Not defined Device name
			-5  Error : UART Timeout
			-4  Error : Not defined Key name
			-3	Error : Length and Pair count are not equal 	\n
*			-2	Error : Too many key value pair
*			-1	Error : Empty buffer	\n
*			0	Not yet Processed	\n
*			1	One pair of key&value processed  	\n
*			2	All pair of key&value processed 	\n
*/
int MR_RcvDataParsing(void)
{
	static int index = 0;
	int ret = MR_RETURN_NotYet;
	static int MR_Pair_Index = 0;
	static char MR_Key_Buf[MR_BUFF_SIZE];
#ifdef USE_MR_STREXT
	// If STREXT feature is enabled
	// Value buffer is increased from MR_BUFF_SIZE to MR_VALUE_SIZE (7 -> 32)
	// to support longer string values
	static char MR_Value_Buf[MR_VALUE_SIZE];
	static int value_buf_size = MR_VALUE_SIZE;
#else
	static char MR_Value_Buf[MR_BUFF_SIZE];
	static int value_buf_size = MR_BUFF_SIZE;
#endif // USE_MR_STREXT
	
	if (MR_UartTimeOut())	//* syntax for checking the timeout of UART	*/
	{
		ret = _errHandling(&MR_Pair_Index, MR_RETURN_UARTTIMEOUT);
        return ret;
	}

	//*!	syntax for checking the empty of buffer !*/
	if (ISRCVBUFFEMPTY)
	{       
		ret = MR_RETURN_EmptyBuffer;
		return ret;
	}
	
	switch (MR_status)
	{
	case STX:
		if (gMR_RcvBuff[gMR_Tail] == STX_CHAR) {
			index = 0;
			MR_status = CATEGORY;
            MR_UartTimeOutFlag = 0;
            MR_Timeout = 1;            
		}
		break;
	case CATEGORY:
		if (gMR_RcvBuff[gMR_Tail] != SEPERATOR_CHAR) {
			gMR_RcvData[gMR_Index_Head].Category[index++] = gMR_RcvBuff[gMR_Tail];
		}
		else
		{
			if(ISDEVICE())
            {
                gMR_RcvData[gMR_Index_Head].Category[index] = '\0';
			    index = 0;
			    MR_status = VERSION;
            }
            else
            {
				ret = _errHandling(&MR_Pair_Index, MR_RETURN_NoDeviceName);
            }            
            
		}
		if (index >= MR_BUFF_SIZE) {
			MR_status = STX;
		}
		break;
	case VERSION:
		if (gMR_RcvBuff[gMR_Tail] != SEPERATOR_CHAR) {
			gMR_RcvData[gMR_Index_Head].Version[index++] = gMR_RcvBuff[gMR_Tail];
		}
		else
		{
			gMR_RcvData[gMR_Index_Head].Version[index] = '\0';
			index = 0;
			MR_status = CMDTYPE;
		}
		if (index >= MR_BUFF_SIZE) {
			MR_status = STX;
		}
		break;
	case CMDTYPE:
		if (gMR_RcvBuff[gMR_Tail] != SEPERATOR_CHAR) {
			gMR_RcvData[gMR_Index_Head].CmdType[index++] = gMR_RcvBuff[gMR_Tail];
		}
		else {
			gMR_RcvData[gMR_Index_Head].CmdType[index] = '\0';
			index = 0;
			MR_status = CMDLENGTH;
		}

		if (index >= MR_BUFF_SIZE) {
			MR_status = STX;
		}
		break;
	case CMDLENGTH:
		if (gMR_RcvBuff[gMR_Tail] != SEPERATOR_CHAR) {
			gMR_RcvData[gMR_Index_Head].CmdLength[index++] = gMR_RcvBuff[gMR_Tail];
		}
		else {
			gMR_RcvData[gMR_Index_Head].CmdLength[index] = '\0';
			index = 0;
			MR_status = CMD;
		}

		if (index >= MR_BUFF_SIZE) {
			MR_status = STX;
		}
		break;
	case CMD:
		if (gMR_RcvBuff[gMR_Tail] != SEPERATOR_CMD_CHAR) {
			if (index >= MR_BUFF_SIZE) {
				ret = _errHandling(&MR_Pair_Index, MR_RETURN_TooLongValue);
				break;
			}
			MR_Key_Buf[index++] = gMR_RcvBuff[gMR_Tail];
		}
		else {
			MR_Key_Buf[index] = '\0';
			gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Key = MR_Compare_Key(MR_Key_Buf);            
			index = 0;
			MR_status = DATA;
            if(gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Key == -1)
            {
				ret = _errHandling(&MR_Pair_Index, MR_RETURN_NotDefineKey);
				break;
            }
		}

		if (index > MR_BUFF_SIZE) {
			MR_status = STX;
		}
		break;
	case DATA:
		if (gMR_RcvBuff[gMR_Tail] == SEPERATOR_CMD_CHAR) {
			ret = _errHandling(&MR_Pair_Index, MR_RETURN_NotEqualPair);
			break;
		}
		else if (gMR_RcvBuff[gMR_Tail] != SEPERATOR_CHAR && gMR_RcvBuff[gMR_Tail] != ETX_CHAR) {
			MR_Value_Buf[index++] = gMR_RcvBuff[gMR_Tail];
			if (index >= value_buf_size) {
				ret = _errHandling(&MR_Pair_Index, MR_RETURN_TooLongValue);
				break;
			}
		}
		else {
			MR_Value_Buf[index] = '\0';
			if (MR_Value_Buf[0] >= '0' && MR_Value_Buf[0] <= '9')
			{
				gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Type = MR_TYPE_INT;
				gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Value = MR_atoi(MR_Value_Buf);
			}
			else
			{
				int eType = MR_Compare_Key(MR_Value_Buf);
				if (eType >= 0) {
					gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Type = MR_TYPE_STR;
					gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Value = eType;
				}
#ifdef USE_MR_STREXT
				else {
					char* buf = MR_MEM_Alloc(index + 1);
					if (buf == 0) {
						ret = _errHandling(&MR_Pair_Index, MR_RETURN_OutOfMemory);
						MR_MEM_Clear();
						break;
					}
					MR_MEM_Memcpy(buf, MR_Value_Buf, index);
					buf[index] = '\0';
					gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Type = MR_TYPE_STREXT;
					gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Value = (int)buf;
				}
#else
				else {
					ret = _errHandling(&MR_Pair_Index, MR_RETURN_NotDefineKey);
					break;
				}
#endif // USE_MR_STREXT
			}
			index = 0;
			/*
			else if(MR_Value_Buf[0] == '?')                                    
			{
				gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Type = MR_TYPE_STR;
				gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Value = MR_Value_Buf[0];
			}
            else                                    
			{
				gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Type = 1;
                gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Value = MR_Compare_Key(MR_Key_Buf);
				//gMR_RcvData[gMR_Index_Head].MR_Pair[MR_Pair_Index].Value = MR_Value_Buf[0];
			}
			*/

			if (gMR_RcvBuff[gMR_Tail] == ETX_CHAR)
			{
				if ((MR_atoi(gMR_RcvData[gMR_Index_Head].CmdLength)) == (MR_Pair_Index+1))
				{
					ret = _errHandling(&MR_Pair_Index, MR_RETURN_AllPairSuccess);
				}
				else
				{
					ret = _errHandling(&MR_Pair_Index, MR_RETURN_NotEqualPair);
				}
			}
			else
			{
				MR_Pair_Index++;
				if (MR_Pair_Index > MR_PAIR_BUFF_SIZE)
				{
					ret = _errHandling(&MR_Pair_Index, MR_RETURN_TooManyPair);
				}
				else
				{
					MR_status = CMD;
					ret = MR_RETURN_OnePairSuccess;
				}
			}
		}
		break;
	default:	
		gMR_Tail--;
        MR_UartTimeOutFlag =0;
        MR_Timeout = 0;
		ret = MR_RETURN_NotYet;
		break;
	}
	gMR_Tail++;
	if (gMR_Tail == MR_RCV_SIZE)
		gMR_Tail = 0;
	if (gMR_Index_Head == MR_RCVDATA_SIZE)
		gMR_Index_Head = 0;
	return ret;
}

void MR_IncreaseTimerTick()
{
	if (MR_Timeout > 0)
		MR_Timeout++;
	if (MR_Timeout >= 1000)
	{
		MR_UartTimeOutFlag = 1;
		MR_Timeout = 0;
	}
}