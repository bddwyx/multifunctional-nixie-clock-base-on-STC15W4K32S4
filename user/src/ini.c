#ifndef _INI_C
#define _INI_C

#include "config.h"
#include "alarm_set.h"
#include "DS1302.h"
#include "UART.h"
#include "overflow.h"
#include "uart_translate.h"
#include "74hc595.h"
#include "infrared.h"
#include "pwm.h"
#include "ISP_IAP.h"

#endif

void main_ini()
{
	P0M0=0;P0M1=0;P0=0;buzz=1;							   //IO��ʼ��
	P2M0=0;P2M1=0;P2=0X00;	   	
	
	uart_config(115200);						   //���ڳ�ʼ��
	
	ini_alarm();								   //���ӳ�ʼ��

	tube_shutdown();							   //�ȶ���ʾ

	timer_4_ini();								   //ϵͳ���

	ini_vs();									   //�����ʼ��

	pwm_state=rom_byte_read(0x0200);			   //rgb��ʼ��
	ini_pwm(pwm_state);
}
