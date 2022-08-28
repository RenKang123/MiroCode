/**
 * Copyright ¨Ï 2019 MIRO Corp. All Rights Reserved.
 * 
 * DO NOT CHANGE THIS FILE!
 * THIS FILE IS GENERATED AUTOMATICALLY!
 */
/**
* @author	kbhong
* @date		2019-01-09
* @file		MR_config.h
* @brief	A file that defines all CMD values used by protocol
* @details	
*/

#ifndef _CONFIG_
#define _CONFIG_

#define MR_DEVICENAME		"SAMPLE"
#define MR_KEY_ERR			"ERR"
#define MR_KEY_PWR			"PWR"
#define MR_KEY_TMR			"TMR"
#define MR_KEY_REQ			"REQ"
#define MR_KEY_ALL			"ALL"
#define MR_KEY_WHO			"WHO"
#define MR_KEY_IAM			"IAM"
#define MR_KEY_A2F			"?"

typedef enum _EMR_KeyType {
	eMR_KEY_DEVICENAME,
	eMR_KEY_ERR,
	eMR_KEY_PWR,
	eMR_KEY_TMR,
	eMR_KEY_REQ,
	eMR_KEY_ALL,
	eMR_KEY_WHO,
	eMR_KEY_IAM,
	eMR_KEY_A2F,
	eMR_KEY_ENDOFKEY
}EMR_KeyType;

#endif
