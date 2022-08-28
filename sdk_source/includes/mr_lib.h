/**
 * Copyright ¨Ï 2019 MIRO Corp. All Rights Reserved.
 * 
 * DO NOT CHANGE THIS FILE!
 * THIS FILE IS GENERATED AUTOMATICALLY!
 */
/**
* @author	yijang
* @date		2019-01-09
* @file		mr_lib.c
* @brief	header file for using mr_lib.c 
* @details	Declarations for using MR_atoi(), MR_strncmp(), MR_strlen() Func..
*/

#ifndef _MR_LIB_H_
#define _MR_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

	int MR_atoi(const char* c);
	int MR_strncmp(const char* s1, const char* s2, unsigned int n);
	int MR_strlen(const char* s);
	char* MR_strcat(const char* Str1, const char* Str2);
	char* MR_strcat_s(const char* Str1, const char* Str2, char* buf, int size);
	char* MR_itoa(char *a, int i);
	int MR_itoa_s(char *a, int i, int iSize);
	char* MR_strcpy(char* d, const char* s);
	int MR_strcpy_s(char** ppd, char* s, int iStrSize, int* piBufLen);
#ifdef USE_MR_STREXT
	void MR_MEM_Init(void *heap, unsigned len);
	void MR_MEM_Free(void *ptr);
	void* MR_MEM_Alloc(unsigned size);
	void MR_MEM_Compact(void);
	void MR_MEM_Clear();
#endif //USE_MR_STREXT
	void* MR_MEM_Memcpy(void* dest, const void* src, unsigned n);
	void* MR_MEM_Memset(void* s, int c, unsigned n);
#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MR_LIB_H_