#ifndef _TIMER_INIT_C
#define _TIMER_INIT_C

#include "config.h"
#include "timer_init.h"
#include "5050rgb.h"
#include "DS1302.h"
#include "pwm.h"

#endif

bit should_get_time_flag=0;

           //pwmÉèÖÃ
{
    static bit dir=1;
	static int val=0;

	if(PWMIF&0x40)
	{
	    PWMIF&=~0X40;  //Èí¼þÖÃÁã

		if(dir)
		{
		    val++;
			if(val>=CYCLE) dir=0;
		}
		else
		{
		    val--;
			if(val<=1) dir=1;
		}

		P_SW2|=0X80;
		PWM7T2=val;
		P_SW2&=~0X80;
	}
}


