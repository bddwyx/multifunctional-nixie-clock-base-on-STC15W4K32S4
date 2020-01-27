#ifndef _PWM_C
#define _PWM_C

#include "config.h"
#include "pwm.h"

#endif

unsigned char pwm_state;
bit rgb_change=1;

void pwm3_config(unsigned int b_dc)
{	       
	PWM3T1=0X0000;	  //两次翻转
	PWM3T2=b_dc;

	PWM3CR=0X00;	  //输出管脚2.1，关闭所有pwm3中断使能	       
}

void pwm4_config(unsigned int r_dc)
{
	PWM4T1=0X0000;	  //两次翻转
	PWM4T2=r_dc;

	PWM4CR=0X00;	  //输出管脚2.2，关闭所有pwm4中断使能	       
}

void pwm5_config(unsigned int g_dc)
{
	PWM5T1=0X0000;	  //两次翻转
	PWM5T2=g_dc;

	PWM5CR=0X00;	  //输出管脚2.3，关闭所有pwm5中断使能	       
}

void ini_pwm(unsigned char mode)
{
    P_SW2|=0X80;	   //访问拓展RAM

    if(mode!=1)
	{
    	P2M1=0;
	
		PWMCFG=0X0e;       //ADC与初始电平
    	PWMC=0x8000/mode;  //周期 
    	PWMCKS=mode;       //时钟16分频

    	PWMCR=0XCE;		   //PWM输出，归零中断，使能PWM3、4、5
	}

	else
	{
	    P2M1=0X0E;
	}
	
    P_SW2&=~0X80;	   //做个了断
}
