#include "Timer.h"
#include "HumCTL.h"
#include "DISP.h"
extern Timing_StatusTypeDef TimingLength;

static Timing_StatusTypeDef TimingLengthOld = zeroHour;

static u16 u16_100ms = 0;
static u8 u8_hour	  = 0;
static bit TimeCame	= 0;
void myTimer()
{
	if(getDispPowerStatus() && (TimingLength != zeroHour))
	{
		if(TimingLength == TimingLengthOld)
		{
			u16_100ms++;
			if(u16_100ms >= 36000)
		//	if(u16_100ms >= 360)
			{
				u16_100ms = 0;
				u8_hour++;
				if(u8_hour >= (u8)TimingLengthOld)
				{
					u8_hour = 0;
					TimeCame = 1;
				}
			}
		}
		else//定时时间更新
		{
			TimingLengthOld = TimingLength;
			u16_100ms = 0;
			u8_hour	  = 0;
			TimeCame = 0;
		}
	}
	else
	{
		u16_100ms = 0;
		u8_hour	  = 0;
		TimeCame = 0;
	}	
}
bit getTimeSwitchStatus()
{
	return TimeCame;
}


