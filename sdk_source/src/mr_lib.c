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
* @brief	main file 
* @details	A file containing the contents of the MR_atoi(), MR_strncmp(), MR_strlen() Func..
*/

#include "mr_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @fn		int MR_atoi(const char* c)
 * @brief	create atoi() func.
 * @author	yijang
 * @param	char 
 * @return	int.
 */

int MR_atoi(const char* c) {
	int ret = 0;
	char pos = 1;

	if (*c == '-') pos = -1;

	while (*c >= '0' && *c <= '9') {
		ret = (ret * 10) + ((*c) - '0');
		c++;
	}
	return ret * pos;
}

/**
 * @fn	int MR_strncmp(const char* s1, const char* s2, unsigned int n)
 * @author	yijang
 * @brief	create strncmp() func.
 * @param	s1	The first char.
 * @param	s2	The second char.
 * @param	n 	An int to process.
 * @returns	An int.
 */
int MR_strncmp(const char* s1, const char* s2, unsigned int n) {
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n; 
	}
	if (n == 0)
		return 0;
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * @fn	int MR_strlen(const char* s) 
 * @author	yijang
 * @brief	create strlen() func
 * @param	s	A char to process. *
 * @returns	An int.
 */
int MR_strlen(const char* s) {
	int len = 0;
	while (*s) {
		len++;
		s++;
	}
	return len;
}

/**
* @brief	create strcat() func
* @param	two array 
* @return	run MR_strcat_s func
*/
char* MR_strcat(const char* Str1, const char* Str2)
{
	static char temp[64] = { '\0', };
	return MR_strcat_s(Str1, Str2, temp, 64);
}

/**
* @brief	create strncat() func
* @param	two array
* @return	added array
*/
char* MR_strcat_s(const char* Str1, const char* Str2, char* buf, int size)
{
	int i = 0;
	int l1, l2;

	l1 = MR_strlen(Str1);
	l2 = MR_strlen(Str2);
	if ((l1 + l2) >= size) {
		return 0;
	}
	for (i = 0; i < l1; i++)
	{
		buf[i] = Str1[i];
	}
	for (i = 0; i < l2; i++)
	{
		buf[MR_strlen(Str1) + i] = Str2[i];
	}
	return buf;
}

/**
* @brief	create itoa() func
* @param	array to be stored, int to be converted
* @return	run MR_itoa_s func
*/
char* MR_itoa(char *a, int i)
{
	if (MR_itoa_s(a, i, 16) >= 0)
	{
		return a;
	}
	else
	{
		return 0;
	}
}

/**
* @brief	create itoa() func
* @param	array to be stored, int to be converted and size
* @return	buff size or -1
*/
int MR_itoa_s(char *a, int i, int iSize)
{
	int sign = 0;
	char buf[16];
	char *ptr;
	int l = 0;

	ptr = buf;

	/* zero then return */
	if (i)
	{
		/* make string in reverse form */
		if (i < 0)
		{
			i = ~i + 1; sign++;
		}
		while (i)
		{
			*ptr++ = (i % 10) + '0'; i = i / 10;
		}
		if (sign)
			*ptr++ = '-';
		*ptr = '\0';

		l = MR_strlen(buf);
		if (l >= iSize) {
			return -1;
		}
		/* copy reverse order */
		for (i = 0; i < l; i++)
			*a++ = buf[l - i - 1];
		*a = '\0';
	}
	else
	{
		*a++ = '0';
		*a = '\0';
		l = 1;
	}

	return l;
}

/**
* @brief	create strcpy() func
* @param	array to be copied, array to be origin
* @return	copied array
*/
char* MR_strcpy(char* d, const char* s)
{
	int i = 0;
	while ((d[i] = s[i]) != '\0') {
		d[i] = s[i];
		++i;
	}
	return d;
}

/**
* @brief	create strncpy() func
* @param	array to be copied, array to be origin, size and buf length
* @return	copied length
*/
static int _MR_strcpy_s(char* d, char* s, int iStrSize, int iBufLen)
{
	int i = 0;
	if (iStrSize <= 0)
	{
		iStrSize = 999999;
	}
	while ((*d = *s) != '\0' && iStrSize > 0 && iBufLen > 0)
	{
		++i;
		++d;
		++s;
		--iBufLen;
		--iStrSize;
	}
	if (*s && iBufLen <= 0)
	{
		return -1;
	}
	return i;
}

/**
* @brief	create strncpy() func
* @param	array to be copied, array to be origin, size and buf length
* @return	the resulting value of Run the _MR_strcpy_s function
*/
//int MR_strcpy_s(char** ppd, char* s, int iStrSize, int* piBufLen)
//{
//	int iRet = _MR_strcpy_s(*ppd, s, iStrSize, *piBufLen); // skip check of iRet
//	*piBufLen -= iRet;
//	*ppd += iRet;
//	return iRet;
//}

#ifdef USE_MR_STREXT

#ifdef USE_MR_CUSTOM_MEMORY
#define MR_USED 1

typedef struct {
	unsigned size;
} UNIT;

typedef struct {
	UNIT* free;
	UNIT* heap;
} MR_MEM;

static MR_MEM mrmem;

static UNIT* compact(UNIT *p, unsigned nsize)
{
	unsigned bsize, psize;
	UNIT *best;

	best = p;
	bsize = 0;

	while (psize = p->size, psize)
	{
		if (psize & MR_USED)
		{
			if (bsize != 0)
			{
				best->size = bsize;
				if (bsize >= nsize)
				{
					return best;
				}
			}
			bsize = 0;
			best = p = (UNIT *)((unsigned)p + (psize & ~MR_USED));
		}
		else
		{
			bsize += psize;
			p = (UNIT *)((unsigned)p + psize);
		}
	}

	if (bsize != 0)
	{
		best->size = bsize;
		if (bsize >= nsize)
		{
			return best;
		}
	}

	return 0;
}

void MR_MEM_Free(void* ptr)
{
	if (ptr)
	{
		UNIT *p;

		p = (UNIT *)((unsigned)ptr - sizeof(UNIT));
		p->size &= ~MR_USED;
	}
}

void* MR_MEM_Alloc(unsigned size)
{
	unsigned fsize;
	UNIT *p;

	if (size == 0) return 0;

	size += 3 + sizeof(UNIT);
	size >>= 2;
	size <<= 2;

	if (mrmem.free == 0 || size > mrmem.free->size)
	{
		mrmem.free = compact(mrmem.heap, size);
		if (mrmem.free == 0) return 0;
	}

	p = mrmem.free;
	fsize = mrmem.free->size;

	if (fsize >= size + sizeof(UNIT))
	{
		mrmem.free = (UNIT *)((unsigned)p + size);
		mrmem.free->size = fsize - size;
	}
	else
	{
		mrmem.free = 0;
		size = fsize;
	}

	p->size = size | MR_USED;

	return (void* )((unsigned)p + sizeof(UNIT));
}

void* MR_MEM_Realloc(void* ptr, unsigned size)
{
	if (ptr && size > 0)
	{
		void* pNew;
		UNIT *p;

		p = (UNIT *)((unsigned)ptr - sizeof(UNIT));
		pNew = MR_MEM_Alloc(size);
		if (pNew)
		{
			unsigned tsize = p->size > size ? size : p->size;
			MR_MEM_Memcpy(pNew, ptr, tsize);
			return pNew;
		}
		else {
			return 0;
		}
	}
	else if (ptr && size <= 0) {
		MR_MEM_Free(ptr);
		return 0;
	}
	else {
		return MR_MEM_Alloc(size);
	}
}

void MR_MEM_Init(void* heap, unsigned len)
{
	MR_MEM_Memset(heap, 0, len);
	len += 3;
	len >>= 2;
	len <<= 2;
	mrmem.free = mrmem.heap = (UNIT *)heap;
	mrmem.free->size = mrmem.heap->size = len - sizeof(UNIT);
	*(unsigned *)((char *)heap + len - 4) = 0;
}

void MR_MEM_Compact(void)
{
	mrmem.free = compact(mrmem.heap, 0x7FFFFFFF);
}

void MR_MEM_Clear()
{
	void* heap = mrmem.heap;
	unsigned len = mrmem.heap->size;
	MR_MEM_Init(heap, len);
}


#else // USE_MR_CUSTOM_MEMORY
#include <stdlib.h>
void MR_MEM_Free(void* ptr)
{
	free(ptr);
}

void* MR_MEM_Alloc(unsigned size)
{
	return malloc(size);
}

void* MR_MEM_Realloc(void* ptr, unsigned size)
{
	return realloc(ptr, size);
}

void MR_MEM_Compact(void)
{
	// do nothing
}
void MR_MEM_Init(void* heap, unsigned len)
{
	// do nothing
}

void MR_MEM_Clear()
{
	// do nothing
}

#endif // USE_MR_CUSTOM_MEMORY

#endif //USE_MR_STREXT

void* MR_MEM_Memcpy(void* dest, const void* src, unsigned n)
{
	unsigned i;
	for (i = 0; i < n; ++i) {
		((char*)dest)[i] = ((char*)src)[i];
	}
	return dest;
}

void* MR_MEM_Memset(void* s, int c, unsigned n)
{
	unsigned i;
	for (i = 0; i < n; ++i) {
		((char*)s)[i] = (char)c;
	}
	return s;
}

#ifdef __cplusplus
} // extern "C"
#endif
