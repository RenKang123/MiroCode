/**
 * Copyright ¨Ï 2019 MIRO Corp. All Rights Reserved.
 * 
 * DO NOT CHANGE THIS FILE!
 * THIS FILE IS GENERATED AUTOMATICALLY!
 */
 /**
 * @author	kbhong
 * @date		2019-01-09
 * @file		MR_def.h
 * @brief	declaration Define,Struct,Global variable,function
 * @details
 */

#ifndef _DEF_
#define _DEF_


/*<! Fixed value */
#define MR_RCV_SIZE				255		/*<! UART Buffer Size */
#define MR_BUFF_SIZE			8		// Buffer size of element in main structure
#define MR_PAIR_BUFF_SIZE		16		// Number of KVs in main structure 
#define MR_RCVDATA_SIZE			10		// Number of main structure
#define MR_TYPE_INT				0
#define MR_TYPE_STR				1
#ifdef USE_MR_STREXT
#define MR_TYPE_STREXT			2
#endif // USE_MR_STREXT

#define STX_CHAR	'#'
#define ETX_CHAR	';'
#define SEPERATOR_CHAR	','
#define SEPERATOR_CMD_CHAR ':'
#define NULL_CHAR   '\0'

#ifdef USE_MR_STREXT
#define MR_MEM_SIZE				1024
#define MR_VALUE_SIZE			32
#endif // USE_MR_STREXT

#define MR_RETURN_TooLongValue	-8
#define MR_RETURN_OutOfMemory	-7
#define MR_RETURN_NoDeviceName  -6
#define MR_RETURN_UARTTIMEOUT   -5
#define MR_RETURN_NotDefineKey  -4
#define MR_RETURN_NotEqualPair	-3
#define MR_RETURN_TooManyPair	-2
#define MR_RETURN_EmptyBuffer	-1
#define MR_RETURN_NotYet		0
#define MR_RETURN_OnePairSuccess	1
#define MR_RETURN_AllPairSuccess	2

#define MR_Return_Success	1
#define MR_Return_Error		0


// struct of Key Value 
typedef struct _MR_KV {
	char Key;
	char Type;
	int Value;
}MR_KV;

// struct of main
typedef struct _MR_RcvData {
	char Category[MR_BUFF_SIZE];
	char Version[MR_BUFF_SIZE];
	char CmdType[MR_BUFF_SIZE];
	char CmdLength[MR_BUFF_SIZE];
	MR_KV MR_Pair[MR_PAIR_BUFF_SIZE];
}MR_RcvData;

#endif
