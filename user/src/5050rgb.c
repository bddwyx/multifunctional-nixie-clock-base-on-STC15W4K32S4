#ifndef _5050RGB_C
#define _5050RGB_C

#include "config.h"
#include "5050rgb.h"
#include "pwm.h"

#endif

unsigned char rgb_dc[3];

void configpwm(unsigned int dcr,unsigned int dcg,unsigned int dcb)
{
    P_SW2|=0X80;      //访问拓展RAM

    pwm3_config(dcb);
	pwm4_config(dcr);
	pwm5_config(dcg);

	P_SW2&=~0X80;	  //做个了断
}

void pwm_inter() interrupt 22
{
    static char dir=0;
	static int  val=0;

	if(PWMIF&0x40)
	{
	    PWMIF&=~0X40;  //软件置零

/*
		configpwm(val,0x7ff,0x800-val);

		P_SW2|=0X80;
		PWM4T2=val;
		PWM3T2=0X800-val;
		PWM5T2=0X7FF;
		P_SW2&=~0X80; 				  */
		
		switch(dir)
		{
		    case 0:configpwm(0x7ffL-val,val+1,1);break;
			case 1:configpwm(1,0x7ffL-val,val+1);break;
			case 2:configpwm(val+1,1,0x7ffL-val);break;
		}								  

		if(val>=0x7feL) 
		{
		    val=0;

			if(dir==2) dir=0;
			else dir++;
		}

		else if(rgb_change) val++;		  
	}	  
}
