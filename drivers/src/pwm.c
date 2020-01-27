#ifndef _PWM_C
#define _PWM_C

#include "config.h"
#include "pwm.h"

#endif

unsigned char pwm_state;
bit rgb_change=1;

void pwm3_config(unsigned int b_dc)
{	       
	PWM3T1=0X0000;	  //���η�ת
	PWM3T2=b_dc;

	PWM3CR=0X00;	  //����ܽ�2.1���ر�����pwm3�ж�ʹ��	       
}

void pwm4_config(unsigned int r_dc)
{
	PWM4T1=0X0000;	  //���η�ת
	PWM4T2=r_dc;

	PWM4CR=0X00;	  //����ܽ�2.2���ر�����pwm4�ж�ʹ��	       
}

void pwm5_config(unsigned int g_dc)
{
	PWM5T1=0X0000;	  //���η�ת
	PWM5T2=g_dc;

	PWM5CR=0X00;	  //����ܽ�2.3���ر�����pwm5�ж�ʹ��	       
}

void ini_pwm(unsigned char mode)
{
    P_SW2|=0X80;	   //������չRAM

    if(mode!=1)
	{
    	P2M1=0;
	
		PWMCFG=0X0e;       //ADC���ʼ��ƽ
    	PWMC=0x8000/mode;  //���� 
    	PWMCKS=mode;       //ʱ��16��Ƶ

    	PWMCR=0XCE;		   //PWM����������жϣ�ʹ��PWM3��4��5
	}

	else
	{
	    P2M1=0X0E;
	}
	
    P_SW2&=~0X80;	   //�����˶�
}
