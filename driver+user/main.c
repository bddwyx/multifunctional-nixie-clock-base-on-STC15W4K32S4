#ifndef _MAIN_C
#define _MAIN_C

#include "config.h"
#include "main.h"
//#include "UART.h"
#include "overflow.h"
#include "uart_translate.h"
#include "ini.h"
#include "DS1302.h"
#include "alarm_set.h"
#include "infrared.h"
#include "74hc595.h"

#endif

void main()
{
	main_ini();

	while(1)
	{
	    if(T4_flag)
		{
		    T4_flag=0;
			vs_detect();
		}

		if(T4_flag2)
		{
		    T4_flag2=0;
		    time_get();
	    	alarm_detect();
		    uart_process();
		}

	}

	  
}		



