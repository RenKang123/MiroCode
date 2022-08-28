#ifndef _PWM_h_
#define _PWM_h_

#include <SN8F5829.h>
//================================================================================================//
#define		L_ENABLE_PWMN							0x80											//使能PWM
#define		L_PWM_CLOCK_32MDIV128			0x00											//PWM1 timer Clock source
#define		L_PWM_CLOCK_32MDIV64			0x10
#define		L_PWM_CLOCK_32MDIV32			0x20
#define		L_PWM_CLOCK_32MDIV16			0x30
#define		L_PWM_CLOCK_32MDIV8				0x40
#define		L_PWM_CLOCK_32MDIV4				0x50
#define		L_PWM_CLOCK_32MDIV2				0x60
#define		L_PWM_CLOCK_32MDIV1				0x70

#define		L_PWMN3_ENABLE						0x08											//PWMN3CH使能
#define		L_PWMN2_ENABLE						0x04											//PWMN2CH使能
#define		L_PWMN1_ENABLE						0x02											//PWMN1CH使能
#define		L_PWMN0_ENABLE						0x01											//PWMN0CH使能												

//================================================================================================//
void PWM20(u8 duty);
void PWM40(u8 duty);
void Systeminit(void);
void PWMinit(void);
//================================================================================================//
#endif