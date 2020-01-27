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
	P0M0=0;P0M1=0;P0=0;buzz=1;							   //IO初始化
	P2M0=0;P2M1=0;P2=0X00;	   	
	
	uart_config(115200);						   //串口初始化
	
	ini_alarm();								   //闹钟初始化

	tube_shutdown();							   //稳定显示

	timer_4_ini();								   //系统嘀嗒

	ini_vs();									   //红外初始化

	pwm_state=rom_byte_read(0x0200);			   //rgb初始化
	ini_pwm(pwm_state);
}
