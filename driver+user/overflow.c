#ifndef _OVERFLOW_C
#define _OVERFLOW_C

#include "config.h"
#include "overflow.h"
#include "UART.h"
#include "74hc595.h"
#include "infrared.h"

#endif

bit T4_flag=0,T4_flag2=0;

void timer_4_ini()									//25ms
{
    T4L=0X4C;
	T4H=0X80;
	
	T4T3M&=0X0F;
	T4T3M|=0X80;
	IE2|=0X40;
}

void timer_4() interrupt 20
{
    static unsigned char cnt=0;

	if(cnt==2)
	{
	    cnt=0;
		T4_flag2=1;
	}
	cnt++;

    T4_flag=1;

	uart_monitor();

	tube_monitor();

	

}		 

