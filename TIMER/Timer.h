#ifndef _Timer_h_
#define _Timer_h_
#include <SN8F5829.H>
#include "Timer.h"

typedef enum 
{    
  zeroHour 		    = 0x00U,      
  oneHour   			= 0x01U,    
  twoHour  				= 0x02U,      
  threeHour  		 	= 0x03U,
	fourHour 				= 0x04U,
	fiveHour   			= 0x05U,
	sixHour   			= 0x06U,
	sevenHour   		= 0x07U
}Timing_StatusTypeDef;

void myTimer();
bit getTimeSwitchStatus();
#endif