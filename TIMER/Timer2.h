#ifndef _Timer2_h_
#define _Timer2_h_
//***************************************************************************************

#define			L_T2_EN								0x80																		//T2使能
#define			L_T2_CLK_DIV128				0x00																		//T2时钟分频						
#define			L_T2_CLK_DIV64				0x10
#define			L_T2_CLK_DIV32				0x20
#define			L_T2_CLK_DIV16				0x30
#define			L_T2_CLK_DIV8					0x40
#define			L_T2_CLK_DIV4					0x50
#define			L_T2_CLK_DIV2					0x60
#define			L_T2_CLK_DIV1					0x70

#define			L_T2_FCKS_FOSC				0x08																	//T2时钟来源
#define			L_T2_FCKS_FCPU				0x00

#define			L_T2_TIMER_OVERFLOW		0x02																	//使能T2 定时器溢出标志
#define			L_T2_CAPYURE_OVERFLOW	0x01																	//使能T2 捕获计数器溢出标志


//#define 		L_T2CH_VALUE 		0xF6																				//10MS = 2500 *128/Fclk = 2500 * 128/32M  2500 = 65536(0x10000) - 63036(0xF63C) 		
//#define 		L_T2CL_VALUE 		0x3C		
#define 		L_T2CH_VALUE 		0xF9																				//10MS = 1728 *64/Fclk = 1728 * 64/11059200M  1728 = 65536(0x10000) - 63808(0xF940) 		
#define 		L_T2CL_VALUE 		0x40	
//#define 		L_T2CH_VALUE 		0xf8																				//0.5MS = 691 *8/Fclk = 691 * 32/11.0592M  2000 = 65536(0x10000) - 63536(0xf830) 		
//#define 		L_T2CL_VALUE 		0x30																			//65536 - 32/11.0592 * 20000 = 36601 = 0x8ef9

//***************************************************************************************
void Timer2init(void);


#endif